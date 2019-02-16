#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/UInt8.h>

uint8_t cycle = 0;

void callBack(const std_msgs::UInt8::ConstPtr& msg)
{
   ROS_INFO("Data received: %d ", msg->data);
   cycle = msg->data;
   return;
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(5);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber location_sub = n.subscribe("/destination_reached", 1, callBack);
  bool done = false;

  uint32_t shape = visualization_msgs::Marker::CUBE;

  while (ros::ok())
  {

    ros::spinOnce();

    visualization_msgs::Marker marker;

    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();
    marker.ns = "basic_shapes";
    marker.id = 0;
    marker.type = shape;

    switch (cycle)
    {

      case 0:
        ROS_INFO_ONCE("Pick up location");
        marker.action = visualization_msgs::Marker::ADD;
        marker.pose.position.x = 4.0;
        marker.pose.position.y = 2.0;
        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;
        break;

      case 1:
        ROS_INFO_ONCE("Reached pick up destination");
        marker.action = visualization_msgs::Marker::DELETE;
        cycle += 1;
        break;

      case 2:
        marker.action = visualization_msgs::Marker::DELETE;
        break;

      case 3: 
        ROS_INFO_ONCE("Drop Off Location");
        marker.action = visualization_msgs::Marker::ADD;
        marker.pose.position.x = -3.5;
        marker.pose.position.y = 3.0;
        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;
        done = true;
        break;
    }

    marker.scale.x = 0.4;
    marker.scale.y = 0.4;
    marker.scale.z = 0.4;

    marker.color.r = 1.0f;
    marker.color.g = 1.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;
    marker.lifetime = ros::Duration();
    
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }

    marker_pub.publish(marker);

    if (done)
      return 0;

    r.sleep();
  }
  return 0;
}
