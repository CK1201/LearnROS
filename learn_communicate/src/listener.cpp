#include<iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"

void listenCallback(const std_msgs::String::ConstPtr &msg){
    ROS_INFO("I hear [%s]", msg->data.c_str());
}

int main(int argc,char **argv){
    ros::init(argc, argv, "listener");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("topic_pub", 1000, listenCallback);
    ros::spin();
    return 0;
}