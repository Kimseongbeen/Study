#include <ros/ros.h>
#include <std_msgs/String.h>

/**
 * @brief 
 * 
 * @param msg 
 */
void msgCallback(const std_msgs::String::ConsPtr& msg)
{
    ROS_INFO("New message Received: %s", msg->data.c_str());
}

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

int main(int argc, char **argv)
{
    ros::init(argc, argv, "simple_subscriber_cpp");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("smileb",10,msgCallback);
    ros::spin();

    return 0;
}