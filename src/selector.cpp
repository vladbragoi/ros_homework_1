/**
 * This file contains the implementation for selector node, part of ros_homework_1
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

const std::string menu = "- Digita 'a' per stampare tutto il messaggio\n"
                    "- Digita 'n' per mostrare il nome\n"
                    "- Digita 'e' per mostrare l'età\n"
                    "- Digita 'c' per mostrare il corso di laurea\n"
                    "- Digita 'q' per uscire\n";

ros_homework_1::Message output;

// callback for "message" topic
void select_callback(const ros_homework_1::Message msg) {
    output = msg;
}

int main(int argc, char **argv) {

    // initialization
    ros::init(argc, argv, "selector");
    ros::NodeHandle n;

    // subscribe to listen messages from "message" topic
    ros::Subscriber sub = n.subscribe("message", 100, select_callback);

    // subscribe to publish on "visualize" topic
    ros::Publisher pub = n.advertise<std_msgs::String>("visualize", 100);

    // subscribe to publish on "kill" topic
    ros::Publisher kill = n.advertise<std_msgs::String>("kill", 100);

    while (ros::ok()) {
        std_msgs::String tmp;
        std::stringstream ss;
        std::string choice;
        
        ros::spinOnce();

        // just for skip cycles that does not contains relevant values in output variable
        if (output.name != "" || output.age != 0 || output.degree != "") {
            std::cout << menu << "> ";
            std::cin >> choice;
            
            // check the input choice from the user as specified
            if (choice == "a")
                ss << "\n---------- Name: " << output.name << "\n" 
                    << "---------- Age: " << output.age << "\n"
                    << "---------- Degree: " << output.degree;
            else if (choice == "n")
                ss << "Name: " << output.name;
            else if (choice == "e")
                ss << "Age: " << output.age;
            else if (choice == "c")
                ss << "Degree: " << output.degree;
            else if (choice == "q") {
                // send kill message in order to stop other nodes safely subscribed 
                // to the "kill" topic
                ss << "kill";
                tmp.data = ss.str();
                kill.publish(tmp);
                
                // shutdown the node
                ros::shutdown();
            } else {
                std::cout << "Errore. Ripetere la scelta.\n";
                continue;
            }
            
            // send message to the "visualize" topic
            tmp.data = ss.str();
            pub.publish(tmp);
        }
    }

    return 0;
}