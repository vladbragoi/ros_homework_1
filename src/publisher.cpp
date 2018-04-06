/**
 * This file contains the implementation for publisher node, part of ros_homework_1
 * package. It is distributed under the terms of MIT license.
 * For more informations about the ros_homework_1 package please visit my git repository
 * at https://github.com/vladbragoi/ros_homework_1.
 * 
 * If you find errors please report them by using the repository (github issues panel).
 * For suggestions/comments/bugs you can contact me at vlad.bragoi@gmail.com
 * 
 * 
 * MIT License
 * 
 * Copyright (c) 2018 Vladislav Bragoi
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "ros/ros.h"
#include "ros_homework_1/Message.h"
#include "std_msgs/String.h"

// matrix of values
std::string matrix[4][3];

// callback for "kill" topic: shutdown the node safely
void stop_callback(const std_msgs::String::ConstPtr& msg) {
    std::string tmp = msg->data.c_str();
    if (tmp.compare("kill") == 0)
        ros::shutdown();
}

int main(int argc, char **argv) {

    // initialization
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

    // subscribe to publish on "message" topic
    ros::Publisher message = n.advertise<ros_homework_1::Message>("message", 100);

    // subscribe to listen on "kill" topic for kill message
    ros::Subscriber kill = n.subscribe("kill", 100, stop_callback);

    // send messages at 1Hz
    ros::Rate rate(1);;

    int count = 1;
    while (ros::ok()) {
        ros_homework_1::Message msg;
        
        row = (count + 4) % 4;
        msg.name = matrix[row][0];
        msg.age = std::atoi(matrix[row][1].c_str());
        msg.degree = matrix[row][2];
        
        ROS_INFO("Name: %s Age: %i Degree: %s\n", msg.name.c_str(), 
                (int)msg.age, msg.degree.c_str());

        // publishing messages on "message" topic
        message.publish(msg);

        ros::spinOnce();

        // suspend process for a second in order to publish at 1Hz on the "message" topic. 
        // If a kill message arrives, it would be handled by the stop callback  and processed 
        // after ~1 sec.
        rate.sleep();
        count++;
    }

    return 0;
}