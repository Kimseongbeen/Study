#ifndef BUMPERBOT_CONTROLLER__SIMPLE_CONTROLLER_HPP_
#define BUMPERBOT_CONTROLLER__SIMPLE_CONTROLLER_HPP_

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <tf2_ros/transform_broadcaster.h>
#include <Eigen/Dense>

class SimpleController : public rclcpp::Node
{
public:
  SimpleController(const std::string& name);

private:
  void velCallback(const geometry_msgs::msg::TwistStamped& msg);
  void updateOdometry();

  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr wheel_cmd_pub_;
  rclcpp::Subscription<geometry_msgs::msg::TwistStamped>::SharedPtr vel_sub_;
  rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_pub_;
  rclcpp::TimerBase::SharedPtr timer_;

  std::unique_ptr<tf2_ros::TransformBroadcaster> transform_broadcaster_;

  double wheel_radius_;
  double wheel_separation_;
  Eigen::Matrix2d speed_conversion_;

  double x_;
  double y_;
  double theta_;

  double current_linear_vel_;
  double current_angular_vel_;

  rclcpp::Time prev_time_;
  nav_msgs::msg::Odometry odom_msg_;
  geometry_msgs::msg::TransformStamped transform_stamped_;
};

#endif  // BUMPERBOT_CONTROLLER__SIMPLE_CONTROLLER_HPP_