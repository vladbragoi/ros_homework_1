/**
 * Version 1.1
 * 
 * This file contains the implementation for visualizer node, part of ros_homework_1
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
#include "std_msgs/String.h"
#include "ros_homework_1/Message.h"

ros_homework_1::Message message;

// callback for "message" topic.
void message_callback(const ros_homework_1::Message msg) {
    message = msg;
}

// callback for "kill" topic: shutdown the node safely
void stop_callback(const std_msgs::String::ConstPtr& msg) {
    std::string tmp = msg->data.c_str();
    if (tmp.compare("kill") == 0)
        ros::shutdown();
}

using namespace std;
// callback for "command" topic.  Just print values received, 
// based on the command from "command" topic
void command_callback(const std_msgs::String::ConstPtr& msg) {
    string cmd = msg->data;
    stringstream ss;

    // ROS_INFO("Command | %s", cmd.c_str());

    if (cmd == "a")
        ss << "\nName: " << message.name << endl 
            << "Age: " << message.age << endl
            << "Degree: " << message.degree << endl;
    else if (cmd == "n")
        ss << "Name: " << message.name << endl;
    else if (cmd == "e")
        ss << "Age: " << message.age << endl;
    else if (cmd == "c")
        ss << "Degree: " << message.degree << endl;
    
    ss << "-------------------------" << endl;

    // ROS_INFO("Message | %s", ss.str().c_str());
    cout << ss.str();
}

int main(int argc, char **argv) {
    
    // initialize
    ros::init(argc, argv, "visualizer");
    ros::NodeHandle n;

    // subscribe to listen on "message" topic
    ros::Subscriber message = n.subscribe("message", 100, message_callback);

    // subscribe to listen on "command" topic
    ros::Subscriber command = n.subscribe("command", 100, command_callback);

    // subscribe to publish on "kill" topic
    ros::Subscriber kill = n.subscribe("kill", 100, stop_callback);

    // process of incoming messages
    ros::spin();

    return 0;
}