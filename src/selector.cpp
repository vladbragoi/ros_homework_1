/**
 * Version 1.1
 * 
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

const std::string menu = "- Digita 'a' per stampare tutto il messaggio\n"
                    "- Digita 'n' per mostrare il nome\n"
                    "- Digita 'e' per mostrare l'età\n"
                    "- Digita 'c' per mostrare il corso di laurea\n"
                    "- Digita 'q' per uscire\n";


int main(int argc, char **argv) {
    std_msgs::String tmp;
    std::string choice;
    std::string options = "acne";

    // initialization
    ros::init(argc, argv, "selector");
    ros::NodeHandle n;

    // subscribe to publish on "command" topic
    ros::Publisher cmd = n.advertise<std_msgs::String>("command", 100);

    // subscribe to publish on "kill" topic
    ros::Publisher kill = n.advertise<std_msgs::String>("kill", 100);

    // print menu options
    std::cout << menu;

    while (ros::ok()) {
        std::cout << "> ";
        std::cin >> choice;

        // check the input choice from the user as specified
        if (choice == "q") {
            // send kill message in order to stop other nodes safely subscribed 
            // to the "kill" topic
            tmp.data = "kill";
            kill.publish(tmp);
            // shutdown the node
            ros::shutdown();
        } else if (options.find(choice) == std::string::npos) {
            std::cout << "Errore. Ripetere la scelta.\n";
            continue;
        }
            
        // send message to the "command" topic
        tmp.data = choice;
        cmd.publish(tmp);

        ros::spinOnce();
    }

    return 0;
}