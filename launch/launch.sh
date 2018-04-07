roscore &
sleep 1
gnome-terminal -x sh -c "rosrun ros_homework_1 publisher"
gnome-terminal -x sh -c "rosrun ros_homework_1 visualizer"
gnome-terminal -x sh -c "rosrun ros_homework_1 selector"
