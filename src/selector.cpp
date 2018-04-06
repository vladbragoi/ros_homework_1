#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ros_homework_1/Message.h"
#include <sstream>

const std::string menu = "- Digita 'a' per stampare tutto il messaggio\n"
                    "- Digita 'n' per mostrare il nome\n"
                    "- Digita 'e' per mostrare l'età\n"
                    "- Digita 'c' per mostrare il corso di laurea\n"
                    "- Digita 'q' per uscire\n";

void select_callback(const ros_homework_1::Message msg) {
    std::string input;

    std::cout << menu << "> ";
    std::cin >> input;
    if (input == "a")
        ;
    else if (input == "n")
        ;
    else if (input == "e")
        ;
    else if (input == "c")
        ;
    else if (input == "q")
        ros::shutdown();
    else
        std::cout << "Errore. Ripetere la scelta.";
    
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "selector");

    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("message", 1000, select_callback);

    ros::spin();

    return 0;
}