/**
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

// callback for "visualize" topic. Just print values received
void visualize_callback(const std_msgs::String::ConstPtr& msg) {
    ROS_INFO("Message | %s", msg->data.c_str());
}

// callback for "kill" topic: shutdown the node safely
void stop_callback(const std_msgs::String::ConstPtr& msg) {
    std::string tmp = msg->data.c_str();
    if (tmp.compare("kill") == 0)
        ros::shutdown();
}

int main(int argc, char **argv) {
    
    // initialize
    ros::init(argc, argv, "visualizer");
    ros::NodeHandle n;

    // subscribe to listen on "visualize" topic
    ros::Subscriber sub = n.subscribe("visualize", 100, visualize_callback);

    // subscribe to publish on "kill" topic
    ros::Subscriber kill = n.subscribe("kill", 100, stop_callback);

    // process of incoming messages
    ros::spin();

    return 0;
}