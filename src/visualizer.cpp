#include "ros/ros.h"
#include "std_msgs/String.h"

void visualize_callback(const std_msgs::String::ConstPtr& msg) {
    ROS_INFO("Message | %s", msg->data.c_str());
}

int main(int argc, char **argv) {
    
    ros::init(argc, argv, "visualizer");

    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("visualize", 1000, visualize_callback);

    ros::spin();

    return 0;
}