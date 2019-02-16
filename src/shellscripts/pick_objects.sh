#! /bin/sh

catkin_dir=/home/robond/catkin_ws_hstrial
catkin_src_dir=$catkin_dir/src

# Launch turtlebot in created world

xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$catkin_src_dir/world/MyWorld.world" &

sleep 5

# Launch AMCL demo

xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$catkin_src_dir/world/myMap.yaml" &

sleep 2

# Launch pick objects functionality

xterm -e "rosrun pick_objects pick_objects_node" &

sleep 3

# Launch RViz window

xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch"
