#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ros_homework_1/Message.h"
#include <sstream>

const std::string menu = "- Digita 'a' per stampare tutto il messaggio\n"
                    "- Digita 'n' per mostrare il nome\n"
                    "- Digita 'e' per mostrare l'età\n"
                    "- Digita 'c' per mostrare il corso di laurea\n"
                    "- Digita 'q' per uscire\n";

ros_homework_1::Message output;

void select_callback(const ros_homework_1::Message msg) {
    output = msg;
}

int main(int argc, char **argv) {

    // initialization
    ros::init(argc, argv, "selector");
    ros::NodeHandle n;

    // subscribe to listen messages from "message" topic
    ros::Subscriber sub = n.subscribe("message", 100, select_callback);

    // subscribe to publish on "ouput" topic
    ros::Publisher pub = n.advertise<std_msgs::String>("visualize", 100);
    

    while (ros::ok()) {
        std_msgs::String visualize;
        std::stringstream ss;
        std::string choice;
        
        ros::spinOnce();

        if (output.name != "" || output.age != 0 || output.degree != "") {
            std::cout << menu << "> ";
            std::cin >> choice;
            
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
            else if (choice == "q")
                ros::shutdown();
            else {
                std::cout << "Errore. Ripetere la scelta.\n";
                continue;
            }
            
            visualize.data = ss.str();
            pub.publish(visualize);
        }
    }

    return 0;
}