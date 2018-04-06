#include "ros/ros.h"
#include "ros_homework_1/Message.h"

std::string matrix[4][3];

int main(int argc, char **argv) {
    ros::init(argc, argv, "publisher");
    ros::NodeHandle n;
    int row;

    matrix[0][0] = "Mario";
    matrix[0][1] = "22";
    matrix[0][2] = "L. in Informatica";
    matrix[1][0] = "Luigi";
    matrix[1][1] = "25";
    matrix[1][2] = "LM. in Matematica";
    matrix[2][0] = "Cristina";
    matrix[2][1] = "20";
    matrix[2][2] = "L. in Medicina";
    matrix[3][0] = "Laura";
    matrix[3][1] = "24";
    matrix[3][2] = "L. in Lingue";

    ros::Publisher message = n.advertise<ros_homework_1::Message>("message", 1000);

    ros::Rate loop_rate(1);;

    int count = 1;
    while (ros::ok()) {
        ros_homework_1::Message msg;
        
        row = (count + 4) % 4;
        msg.name = matrix[row][0];
        msg.age = std::atoi(matrix[row][1].c_str());
        msg.degree = matrix[row][2];
        
        ROS_INFO("Name: %s Age: %i Degree: %s\n", msg.name.c_str(), (int)msg.age, msg.degree.c_str());

        message.publish(msg);

        ros::spinOnce();

        loop_rate.sleep();
        count++;
    }

    return 0;
}