/**
 * @file bag_file_utils.hpp
 * @brief Utility for handling bag files in ROS2.
 *
 * This file contains the declaration of the BagFileHandler class, which provides methods for creating,
 * writing, and reading bag files using rosbag2 in ROS2.
 */

#ifndef BAG_FILE_UTILS_HPP
#define BAG_FILE_UTILS_HPP

#include <rosbag2_cpp/writer.hpp>
#include <rosbag2_cpp/reader.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/serialization.hpp>
#include <geometry_msgs/msg/pose_array.hpp>
#include <cartesian_control_msgs/action/follow_cartesian_trajectory.hpp>
#include <memory>
#include <vector>
#include <string>

namespace bag_file_utils {

/**
 * @class BagFileHandler
 * @brief Handler for manipulating bag files in ROS2.
 *
 * The BagFileHandler class provides functions to create new bag files, write feedback and trajectories
 * to bag files, and read data from bag files.
 */
class BagFileHandler {
public:
    /**
     * @brief Constructor for the BagFileHandler class.
     * @param base_filename The base name of the bag file to be used for recording.
     */
    BagFileHandler(const std::string& base_filename);

    /**
     * @brief Creates topics in the bag file for recording.
     * @param topics A vector of topic names to create in the bag file.
     * @param action_type The type of action associated with the topics (e.g., message type for the action).
     */
    void create_bag_topics(const std::vector<std::string>& topics, const std::string& action_type);

    /**
     * @brief Writes feedback to a topic in the bag file.
     * @param feedback The feedback to write.
     * @param topic The name of the topic to write the feedback to.
     * @param action_type The type of action associated with the feedback.
     * @param timestamp The timestamp at the time of recording the feedback.
     */
    void write_feedback(const std::shared_ptr<const cartesian_control_msgs::action::FollowCartesianTrajectory::Feedback>& feedback, const std::string& topic, const std::string& action_type, rclcpp::Time timestamp);

    /**
     * @brief Writes a serialized trajectory message to a topic in the bag file.
     * @param serialized_msg The serialized message to write.
     * @param topic The name of the topic to write the message to.
     * @param type The type of message.
     * @param timestamp The timestamp at the time of recording the message.
     */
    void write_trajectory(const rclcpp::SerializedMessage& serialized_msg, const std::string& topic, const std::string& type, rclcpp::Time timestamp);

    /**
     * @brief Gets the name of the currently used bag file.
     * @return The name of the bag file.
     */
    std::string get_filename() const;
    
    /**
     * @brief Reads a path from the bag file.
     * @param logger The logger for recording debug/info messages.
     * @param bag_filename The name of the bag file to read from.
     * @param topic_name The name of the topic to read data from.
     * @return A shared pointer to a PoseArray containing the read path.
     */
    std::shared_ptr<geometry_msgs::msg::PoseArray> bag_file_path(const rclcpp::Logger &logger, const std::string& bag_filename, const std::string& topic_name);

private:
    /**
     * @brief Sets the file name with a timestamp.
     * @param base_filename The base name of the file to use.
     */
    void set_filename_with_timestamp(const std::string& base_filename);

    std::unique_ptr<rosbag2_cpp::Writer> writer_; ///< Writer for handling bag files.
    std::string stored_trajectory_file_name_; ///< Name of the stored trajectory file.
};

} // namespace bag_file_utils

#endif // BAG_FILE_UTILS_HPP
