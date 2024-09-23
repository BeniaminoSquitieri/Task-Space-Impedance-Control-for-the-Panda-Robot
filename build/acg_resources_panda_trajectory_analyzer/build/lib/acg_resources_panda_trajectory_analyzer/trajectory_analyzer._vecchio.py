import rosbag2_py as rosbag  
import matplotlib.pyplot as plt  
import argparse  
from rclpy.serialization import deserialize_message
from rosidl_runtime_py.utilities import get_message
import control_msgs  
import rclpy  
from scipy.spatial.transform import Rotation as R  
import numpy as np  
import matplotlib.colors as mcolors
import matplotlib.cm as cm
import control_msgs.action._follow_joint_trajectory
import matplotlib.pyplot as plt
from scipy.spatial.transform import Rotation as R

# Function to read messages from a ROS2 bag file
def read_messages(input_bag: str, topic_filter: str = None):
    reader = rosbag.SequentialReader()
    reader.open(
        rosbag.StorageOptions(uri=input_bag, storage_id="sqlite3"),
        rosbag.ConverterOptions(
            input_serialization_format="cdr", output_serialization_format="cdr"
        ),
    )

    topic_types = reader.get_all_topics_and_types()
    
    # Stampa i tipi di topic disponibili per debugging
    print("Available topics in bag file:")
    for topic_type in topic_types:
        print(f" - {topic_type.name} ({topic_type.type})")

    def type_help(topic_name):
        for topic_type in topic_types:
            if topic_type.name == topic_name:
                if not topic_type.type:
                    print(f"Skipping topic {topic_name} due to missing type.")
                    return None
                return topic_type.type
        raise ValueError(f"Topic {topic_name} not in bag")

    while reader.has_next():
        topic, data, timestamp = reader.read_next()
        if topic_filter and topic != topic_filter:
            continue  # Filtra per topic specifico se fornito
        try:
            message_type = type_help(topic)
            if message_type is None:
                continue
            message_deserialized = deserialize_message(data, get_message(message_type))
            yield topic, message_deserialized, timestamp
        except Exception as e:
            print(f"Failed to process topic {topic}: {e}")
            raise

    del reader


# Function to plot a 3D trajectory
# Funzione per tracciare una traiettoria 3D
def plot_3d_trajectory(planned_trajectory, executed_trajectory, logger):
    # Liste per memorizzare le coordinate desiderate ed eseguite
    x__des = []
    y__des = []
    z__des = []
    x_exec = []
    y_exec = []
    z_exec = []

    # Estrae le posizioni desiderate dalla traiettoria pianificata
    for sub_point_planned in planned_trajectory.points:
        # Assicurati che il sub_point_planned abbia la struttura attesa
        x__des.append(sub_point_planned.point.pose.position.x)
        y__des.append(sub_point_planned.point.pose.position.y)
        z__des.append(sub_point_planned.point.pose.position.z)
        print(f"Planned position x: {sub_point_planned.point.pose.position.x}, y: {sub_point_planned.point.pose.position.y}, z: {sub_point_planned.point.pose.position.z}")

    # Estrae le posizioni eseguite dalla traiettoria
    # for point_executed in executed_trajectory:
    #     x_exec.append(point_executed.feedback.actual.point.pose.position.x)
    #     y_exec.append(point_executed.feedback.actual.point.pose.position.y)
    #     z_exec.append(point_executed.feedback.actual.point.pose.position.z)
    #     print(f"Executed position x: {point_executed.feedback.actual.point.pose.position.x}, y: {point_executed.feedback.actual.point.pose.position.y}, z: {point_executed.feedback.actual.point.pose.position.z}")

    # Verifica che le liste non siano vuote
    if not x__des or not y__des or not z__des:
        logger.error('Planned trajectory data is missing or incomplete.')
        return

    # Crea una figura e un grafico 3D per visualizzare le traiettorie
    figure = plt.figure(figsize=[10, 8])
    ax = figure.add_subplot(111, projection='3d')

    # Traccia le traiettorie desiderate ed eseguite sul grafico
    ax.plot(x__des, y__des, z__des, label='Planned', color='blue')
    ax.plot(x_exec, y_exec, z_exec, label='Executed', color='orange')
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    # Imposta i limiti del grafico per una visualizzazione chiara
    mid_x = (max(x__des + x_exec) + min(x__des + x_exec)) / 2
    mid_y = (max(y__des + y_exec) + min(y__des + y_exec)) / 2
    mid_z = (max(z__des + z_exec) + min(z__des + z_exec)) / 2
    max_range = max(max(x__des + x_exec) - min(x__des + x_exec), max(y__des + y_exec) - min(y__des + y_exec), max(z__des + z_exec) - min(z__des + z_exec))

    ax.set_xlim([mid_x - max_range / 2, mid_x + max_range / 2])
    ax.set_ylim([mid_y - max_range / 2, mid_y + max_range / 2])
    ax.set_zlim([mid_z - max_range / 2, mid_z + max_range / 2])

    plt.legend()
    
    logger.info('3D Trajectories plotted')




# Function to analyze the trajectory in task-space
def analyze_task_space_trajectory(planned_trajectory_message, executed_trajectory, logger):
    # Definizione dei colori per le traiettorie pianificate ed eseguite
    planned_color = 'red'  
    executed_color = 'blue'  
    fig_positions = plt.figure(figsize=[10, 8])
    fig_velocities = plt.figure(figsize=[10, 8])
    
    # Crea una griglia per i grafici delle posizioni e delle velocità
    grid1 = fig_positions.add_gridspec(6, 1, hspace=0.6)
    grid2 = fig_velocities.add_gridspec(6, 1, hspace=0.6)

    # Nomi per gli assi dei grafici
    name = ['Position x', 'Position y', 'Position z', 'Orientation x', 'Orientation y', 'Orientation z']
    name_velocity = ['Linear velocity x', 'Linear velocity y', 'Linear velocity z', 'Angular velocity x', 'Angular velocity y', 'Angular velocity z']

    # Inizializza le liste per memorizzare posizioni e velocità pianificate ed eseguite
    planned_poses = [[], [], [], [], [], []]    
    executed_poses = [[], [], [], [], [], []]  
    planned_velocities = [[], [], [], [], [], []]  
    executed_velocities = [[], [], [], [], [], []] 

    timestamps = []
    sums = []  # Somme per il calcolo del MSE
    mse = []  # Lista per il MSE finale

    k = 0  # Indice per la riga dei grafici
    j = 0  # Indice per la colonna dei grafici

    # Calcola il tempo iniziale per il calcolo dei timestamp relativi
    initial_time = executed_trajectory[0].feedback.header.stamp.sec + executed_trajectory[0].feedback.header.stamp.nanosec * pow(10, -9)

    # Crea una nuova griglia per i grafici delle posizioni e delle velocità
    grid1 = fig_positions.add_gridspec(3, 2, hspace=0.6, wspace=0.25)
    grid2 = fig_velocities.add_gridspec(3, 2, hspace=0.6, wspace=0.25)

    # Inizializza i sommatori per il calcolo del MSE
    for i in range(0, 6):
        sums.append(0)

    # Processa ogni punto della traiettoria
    for sub_point_planned, point_executed in zip(planned_trajectory_message.points, executed_trajectory):
        # Stampa di debug per verificare i dati letti
        print(f"Planned position x: {sub_point_planned.point.pose.position.x}, y: {sub_point_planned.point.pose.position.y}, z: {sub_point_planned.point.pose.position.z}")
        print(f"Executed position x: {point_executed.feedback.actual.point.pose.position.x}, y: {point_executed.feedback.actual.point.pose.position.y}, z: {point_executed.feedback.actual.point.pose.position.z}")

        # Aggiunge le posizioni pianificate
        planned_poses[0].append(sub_point_planned.point.pose.position.x)
        planned_poses[1].append(sub_point_planned.point.pose.position.y)
        planned_poses[2].append(sub_point_planned.point.pose.position.z)

        # Calcola l'orientamento desiderato in Euler
        if sub_point_planned.point.pose.orientation.w < 0:
            r = R.from_quat([-sub_point_planned.point.pose.orientation.x, -sub_point_planned.point.pose.orientation.y, -sub_point_planned.point.pose.orientation.z, -sub_point_planned.point.pose.orientation.w])
        else:
            r = R.from_quat([sub_point_planned.point.pose.orientation.x, sub_point_planned.point.pose.orientation.y, sub_point_planned.point.pose.orientation.z, sub_point_planned.point.pose.orientation.w])

        [z, y, x] = r.as_euler('zyx', degrees=True)
        planned_poses[3].append(x)
        planned_poses[4].append(y)
        planned_poses[5].append(z)

        # Aggiunge le posizioni effettivamente eseguite
        executed_poses[0].append(point_executed.feedback.actual.point.pose.position.x)
        executed_poses[1].append(point_executed.feedback.actual.point.pose.position.y)
        executed_poses[2].append(point_executed.feedback.actual.point.pose.position.z)

        # Calcola l'orientamento eseguito in Euler
        if point_executed.feedback.actual.point.pose.orientation.w < 0:
            r = R.from_quat([-point_executed.feedback.actual.point.pose.orientation.x, -point_executed.feedback.actual.point.pose.orientation.y, -point_executed.feedback.actual.point.pose.orientation.z, -point_executed.feedback.actual.point.pose.orientation.w])
        else:
            r = R.from_quat([point_executed.feedback.actual.point.pose.orientation.x, point_executed.feedback.actual.point.pose.orientation.y, point_executed.feedback.actual.point.pose.orientation.z, point_executed.feedback.actual.point.pose.orientation.w])
        
        [z, y, x] = r.as_euler('zyx', degrees=True)
        executed_poses[3].append(x)
        executed_poses[4].append(y)
        executed_poses[5].append(z)

        # Aggiunge le velocità pianificate ed eseguite
        planned_velocities[0].append(0.0)  # Assume no velocity data in planned trajectory
        planned_velocities[1].append(0.0)
        planned_velocities[2].append(0.0)
        planned_velocities[3].append(0.0)
        planned_velocities[4].append(0.0)
        planned_velocities[5].append(0.0)

        executed_velocities[0].append(point_executed.feedback.actual.point.velocity.linear.x)
        executed_velocities[1].append(point_executed.feedback.actual.point.velocity.linear.y)
        executed_velocities[2].append(point_executed.feedback.actual.point.velocity.linear.z)
        executed_velocities[3].append(point_executed.feedback.actual.point.velocity.angular.x)
        executed_velocities[4].append(point_executed.feedback.actual.point.velocity.angular.y)
        executed_velocities[5].append(point_executed.feedback.actual.point.velocity.angular.z)

        # Aggiunge i timestamp relativi al tempo iniziale
        timestamps.append(point_executed.feedback.header.stamp.sec + point_executed.feedback.header.stamp.nanosec * pow(10, -9) - initial_time)

        # Calcola l'errore di orientamento in Euler
        r = R.from_quat([point_executed.feedback.error.point.pose.orientation.x, point_executed.feedback.error.point.pose.orientation.y, point_executed.feedback.error.point.pose.orientation.z, point_executed.feedback.error.point.pose.orientation.w])
        [z, y, x] = r.as_euler('zyx', degrees=True)
        
        # Calcola la somma degli errori quadrati per il MSE
        sums[0] += point_executed.feedback.error.point.pose.position.x ** 2
        sums[1] += point_executed.feedback.error.point.pose.position.y ** 2
        sums[2] += point_executed.feedback.error.point.pose.position.z ** 2
        sums[3] += x ** 2
        sums[4] += y ** 2
        sums[5] += z ** 2
    
    for i in range(0, 6):
        mse.append(sums[i] / len(executed_trajectory))
    print("mse:  ", mse)    
    
    for i in range(0, 6):
        axis0 = fig_positions.add_subplot(grid1[k, j])
        axis0.plot(timestamps, planned_poses[i], color=planned_color, label='Planned')  
        axis0.plot(timestamps, executed_poses[i], color=executed_color, label='Executed')  
        axis0.set_title(name[i] + ' - mse: ' + str(round(mse[i], 8)))
        if i < 3:
            axis0.set_ylabel('Position (m)')
        else:
            axis0.set_ylabel('Orientation (deg)')
        axis0.set_xlabel('Time (s)')
        axis0.grid(True)
        axis0.legend(['Planned', 'Executed'])

        axis1 = fig_velocities.add_subplot(grid2[k, j])
        axis1.plot(timestamps, planned_velocities[i], color=planned_color, label='Planned')  
        axis1.plot(timestamps, executed_velocities[i], color=executed_color, label='Executed')  
        axis1.set_title(name_velocity[i])
        if i < 3:
            axis1.set_ylabel('Velocity (m/s)')
        else:
            axis1.set_ylabel('Velocity (deg/s)')
        axis1.set_xlabel('Time (s)')
        axis1.grid(True)
        axis1.legend(['Planned', 'Executed'])

        if j == 1:
            j = 0
            k += 1
        else:
            j += 1
    
    fig_positions.subplots_adjust(left=0.075, right=0.925, bottom=0.06, top=0.95) 
    fig_velocities.subplots_adjust(left=0.075, right=0.925, bottom=0.06, top=0.95)
    logger.info('Trajectories plotted')
    logger.info('Velocities plotted')

# Main function that runs the program
def main():
    rclpy.init()  # Initialize ROS2
    node = rclpy.create_node('trajectory_analyzer')  # Create a ROS2 node   
    logger = node.get_logger()
    logger.info('Starting trajectory analyzer')

    parser = argparse.ArgumentParser(description='Plot trajectories from two bag files.')  # Create a command-line argument parser
    parser.add_argument('PlannedBagFile', metavar='planned_bagfile', type=str, help='The bag file that contains the planned trajectory')
    parser.add_argument('ExecutedBagFile', metavar='executed_bagfile', type=str, help='The bag file that contains the executed trajectory')
    parser.add_argument('--topic', type=str, default='/point_to_point', help='The topic of the messages containing the executed trajectory to plot')

    args = parser.parse_args()

    planned_bag_file = args.PlannedBagFile
    executed_bag_file = args.ExecutedBagFile
    trajectory_topic = args.topic
    
    planned_trajectory = []
    executed_trajectory = []

    # Read messages from the planned bag file
    for topic, message_deserialized, timestamp in read_messages(planned_bag_file, '/planned_point_to_point'):
        planned_trajectory.append(message_deserialized)
        # # Print the points in the planned trajectory for debugging
        if hasattr(message_deserialized, 'points'):
            for point in message_deserialized.points:
                print(f"Planned Trajectory Point - Position: x={point.point.pose.position.x}, y={point.point.pose.position.y}, z={point.point.pose.position.z}")

    print(f"Read planned trajectory message from {topic} at {timestamp}.")

    # Read messages from the executed bag file
    for topic, message_deserialized, timestamp in read_messages(executed_bag_file, trajectory_topic):
        executed_trajectory.append(message_deserialized)
        # # Print the points in the executed trajectory for debugging
        # if hasattr(message_deserialized, 'feedback'):
        #     feedback = message_deserialized.feedback
        #     print(f"Executed Trajectory Feedback - Position: x={feedback.actual.point.pose.position.x}, y={feedback.actual.point.pose.position.y}, z={feedback.actual.point.pose.position.z}")

    logger.info('Trajectories read')

    # Ensure that planned_trajectory is not empty and contains the expected message type
    if planned_trajectory:
        # Get the first (and possibly only) CartesianTrajectory message
        planned_trajectory_message = planned_trajectory[0]
        
        # Ensure that the message has the expected attribute
        if hasattr(planned_trajectory, 'points'):
            # Analyze the trajectory in task-space using the deserialized message
            analyze_task_space_trajectory(planned_trajectory, executed_trajectory, logger)
            # Plot the 3D trajectory using the deserialized message
            plot_3d_trajectory(planned_trajectory, executed_trajectory, logger)
        else:
            logger.error('Planned trajectory does not contain the expected attribute `points`.')
    else:
        logger.error('No planned trajectory data available.')

    plt.show()  # Display the graphs

if __name__ == "__main__":
    main()  # Run the main function

