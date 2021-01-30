#include<iostream>
#include "ros/ros.h"
#include "learn_communicate/beat.h"
void beatCallback(const learn_communicate::beat &msg){
    ROS_INFO("I hear [Beat %s on his %s %d times]", msg.name.c_str(), msg.part.c_str(), msg.beat_times);
}
int main(int argc,char **argv){
    ros::init(argc, argv, "listener2");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("beat_sb", 1000, beatCallback);
    ros::spin();
    return 0;
}