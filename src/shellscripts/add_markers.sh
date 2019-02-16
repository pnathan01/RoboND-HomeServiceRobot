#! /bin/sh

catkin_dir=/home/robond/catkin_ws_hstrial
catkin_src_dir=$catkin_dir/src

# Launch turtlebot in created world

xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$catkin_src_dir/world/MyWorld.world" &

sleep 5

# Launch AMCL demo

xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$catkin_src_dir/world/myMap.yaml" &

sleep 2

# Launch RViz window

xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &

sleep 3

# Launch add marker functionality

xterm -e "rosrun add_markers add_markers_node"
