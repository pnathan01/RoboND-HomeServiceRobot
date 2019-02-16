#! /bin/sh

catkin_dir=/home/robond/catkin_ws_hstrial
catkin_src_dir=$catkin_dir/src

# Launch turtlebot in created world

xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$catkin_src_dir/world/MyWorld.world" &

sleep 5

# Launch gmapping demo

xterm -e "roslaunch turtlebot_gazebo gmapping_demo.launch custom_gmapping_launch_file:=$catkin_src_dir/turtlebot_simulator/turtlebot_gazebo/launch/gmapping.launch" &

sleep 2

# Launch turtlebot teleop

xterm -e "roslaunch turtlebot_teleop keyboard_teleop.launch" &

sleep 3

# Launch RViz window

xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch"
