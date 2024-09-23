#include "bag_file_utils.hpp"
#include <rosbag2_storage/topic_metadata.hpp>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <rcpputils/filesystem_helper.hpp>

namespace bag_file_utils {

/**
 * @brief Constructor for the BagFileHandler class.
 * 
 * Initializes a writer for writing bag files with a filename that includes a timestamp.
 * 
 * @param base_filename Base name for the bag file.
 */
BagFileHandler::BagFileHandler(const std::string& base_filename) {
    writer_ = std::make_unique<rosbag2_cpp::Writer>();
    set_filename_with_timestamp(base_filename); // Creates the bag file where recorded trajectories will be saved

    rosbag2_storage::StorageOptions storage_options;
    storage_options.uri = stored_trajectory_file_name_;
    storage_options.max_bagfile_size = 0;
    writer_->open(storage_options);

    RCLCPP_INFO(rclcpp::get_logger("bag_file_utils"), "Opened database '%s' for writing.", stored_trajectory_file_name_.c_str());
}

/**
 * @brief Creates topics in the bag file using provided topic names and metadata.
 * 
 * @param topics Vector of topic names to create.
 * @param action_type Type of action associated with the topics.
 */
void BagFileHandler::create_bag_topics(const std::vector<std::string>& topics, const std::string& action_type) {
    rosbag2_storage::TopicMetadata topic_metadata;
    topic_metadata.serialization_format = "cdr";
    topic_metadata.offered_qos_profiles = "";

    RCLCPP_INFO(rclcpp::get_logger("bag_file_utils"), "Creating topics with the following metadata:");

    for (const auto& topic : topics) {
        topic_metadata.name = topic;
        topic_metadata.type = action_type; 
        writer_->create_topic(topic_metadata);

        // Print metadata for each topic
        RCLCPP_INFO(rclcpp::get_logger("bag_file_utils"),
                    "Topic Name: %s, Type: %s, Serialization Format: %s, QoS Profiles: %s",
                    topic_metadata.name.c_str(),
                    topic_metadata.type.c_str(),
                    topic_metadata.serialization_format.c_str(),
                    topic_metadata.offered_qos_profiles.c_str());
    }

    // Print general information about the bag file
    RCLCPP_INFO(rclcpp::get_logger("bag_file_utils"), "Bag file '%s' created with %lu topics.", stored_trajectory_file_name_.c_str(), topics.size());
}

/**
 * @brief Writes feedback data to the bag file under a specified topic, action type, and timestamp.
 * 
 * @param feedback Feedback to write to the bag file.
 * @param topic Name of the topic to write to.
 * @param action_type Type of action associated with the feedback.
 * @param timestamp Timestamp of the message.
 */
void BagFileHandler::write_feedback(const std::shared_ptr<const cartesian_control_msgs::action::FollowCartesianTrajectory::Feedback>& feedback, const std::string& topic, const std::string& action_type, rclcpp::Time timestamp) {
    auto msg = std::make_shared<cartesian_control_msgs::action::FollowCartesianTrajectory_FeedbackMessage>();
    msg->feedback = *feedback;

    auto serialized_feedback = std::make_shared<rclcpp::SerializedMessage>();
    rclcpp::Serialization<cartesian_control_msgs::action::FollowCartesianTrajectory_FeedbackMessage> serialization_;
    serialization_.serialize_message(msg.get(), serialized_feedback.get());

    writer_->write(serialized_feedback, topic, action_type, timestamp);
}

/**
 * @brief Sets the bag file name using the base name and a current timestamp.
 * 
 * @param base_filename Base name to use for the bag file.
 */
void BagFileHandler::set_filename_with_timestamp(const std::string& base_filename) {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(now, "%Y_%m_%d_%H_%M_%S");
    std::string date_string = oss.str();

    stored_trajectory_file_name_ = base_filename + "_" + date_string + ".bag";

    if (rcpputils::fs::exists(stored_trajectory_file_name_)) {
        rcpputils::fs::remove_all(stored_trajectory_file_name_);
    }
}

/**
 * @brief Gets the name of the created bag file.
 * 
 * @return std::string Name of the bag file.
 */
std::string BagFileHandler::get_filename() const {
    return stored_trajectory_file_name_;
}

/**
 * @brief Writes a serialized trajectory to the bag file.
 * 
 * @param serialized_msg Serialized message to write.
 * @param topic Name of the topic to write to.
 * @param type Type of message.
 * @param timestamp Timestamp of the message.
 */
void BagFileHandler::write_trajectory(const rclcpp::SerializedMessage& serialized_msg, const std::string& topic, const std::string& type, rclcpp::Time timestamp) {
    writer_->write(std::make_shared<rclcpp::SerializedMessage>(serialized_msg), topic, type, timestamp);
}

/**
 * @brief Reads the path from a specified bag file and returns a sequence of poses.
 * 
 * @param logger ROS2 logger for printing information.
 * @param bag_filename Name of the bag file to read from.
 * @param topic_name Name of the topic from which to extract data.
 * @return std::shared_ptr<geometry_msgs::msg::PoseArray> Sequence of poses read from the bag file.
 */
std::shared_ptr<geometry_msgs::msg::PoseArray> BagFileHandler::bag_file_path(const rclcpp::Logger &logger, const std::string& bag_filename, const std::string& topic_name) {
    rosbag2_cpp::Reader reader_; 
    rclcpp::Serialization<geometry_msgs::msg::PoseArray> serialization_;
    auto ros_msg = std::make_shared<geometry_msgs::msg::PoseArray>(); 

    reader_.open(bag_filename); 

    while (reader_.has_next()) { 
        auto msg = reader_.read_next(); 

        RCLCPP_INFO(logger, "Current message topic: %s", msg->topic_name.c_str());

        if (msg->topic_name.compare(topic_name) == 0) { 
            continue; 
        }

        rclcpp::SerializedMessage serialized_msg(*msg->serialized_data); 
        serialization_.deserialize_message(&serialized_msg, ros_msg.get()); 

        RCLCPP_INFO(logger, "Got the path from the bag file.");

    }

    return ros_msg; 
}

} // namespace bag_file_utils
