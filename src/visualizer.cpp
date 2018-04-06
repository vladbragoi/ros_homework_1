#include "ros/ros.h"
#include "std_msgs/String.h"

void visualize_callback(const std_msgs::String::ConstPtr& msg) {
    ROS_INFO("Message | %s", msg->data.c_str());
}

void stop_callback(const std_msgs::String::ConstPtr& msg) {
    std::string tmp = msg->data.c_str();
    if (tmp.compare("kill") == 0)
        ros::shutdown();
}

int main(int argc, char **argv) {
    
    ros::init(argc, argv, "visualizer");

    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("visualize", 100, visualize_callback);

    ros::Subscriber kill = n.subscribe("kill", 100, stop_callback);

    ros::spin();

    return 0;
}