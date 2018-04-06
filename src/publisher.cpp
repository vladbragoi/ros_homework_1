#include "ros/ros.h"
#include "ros_homework_1/Message.h"

int main(int argc, char **argv) {

    ros::init(argc, argv, "publisher");

    ros::NodeHandle n;

    ros::Publisher message = n.advertise<ros_homework_1::Message>("message", 1000);

    ros::Rate loop_rate(1);;

    while (ros::ok()) {
        ros_homework_1::Message msg;
        
        msg.name = "Mario";
        msg.age = 22;
        msg.degree = "L. in Informatica";
        
        ROS_INFO("Name: %s Age: %i Degree: %s\n", msg.name.c_str(), (int)msg.age, msg.degree.c_str());

        message.publish(msg);

        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}