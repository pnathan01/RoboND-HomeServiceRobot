#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/UInt8.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "simple_navigation_goals");
  ros::NodeHandle n;

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

 //set up publisher to broadcast if robot is at pick up location
  ros::Publisher location_pub = n.advertise<std_msgs::UInt8>("/destination_reached", 1);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal pick_goal;
  move_base_msgs::MoveBaseGoal drop_goal;


  // set up the frame parameters
  pick_goal.target_pose.header.frame_id = "map";
  pick_goal.target_pose.header.stamp = ros::Time::now();
  drop_goal.target_pose.header.frame_id = "map";
  drop_goal.target_pose.header.stamp = ros::Time::now();

  // set up the frame parameters
  pick_goal.target_pose.header.frame_id = "map";
  pick_goal.target_pose.header.stamp = ros::Time::now();
  drop_goal.target_pose.header.frame_id = "map";
  drop_goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  pick_goal.target_pose.pose.position.x = 4.0;
  pick_goal.target_pose.pose.position.y = 2.0;
  pick_goal.target_pose.pose.orientation.w = 1.0;
  drop_goal.target_pose.pose.position.x = -3.5;
  drop_goal.target_pose.pose.position.y = 3.0;
  drop_goal.target_pose.pose.orientation.w = 1.0;

   // Send the pick up goal position and orientation for the robot to reach
  ROS_INFO("Sending pick-up goal");
  ac.sendGoal(pick_goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    ROS_INFO("Reached pick up goal");
    std_msgs::UInt8 msg1;
    msg1.data = 1;
    ROS_INFO("The message is %d", msg1.data);
    location_pub.publish(msg1);
  }
  else
  {
    ROS_INFO("Failed to reach pick up goal");
  }

  //return 0;

  sleep(10);

   // Send the drop off goal position and orientation for the robot to reach
  ROS_INFO("Sending drop-off goal");
  ac.sendGoal(drop_goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    std_msgs::UInt8 msg2;
    msg2.data = 3;
    ROS_INFO("The message is %d", msg2.data);
    location_pub.publish(msg2);
    ROS_INFO("Reached pick up goal");
  }
  else
  {
    ROS_INFO("Failed to reach pick up goal");
  }

 sleep(10);

  return 0;

}
