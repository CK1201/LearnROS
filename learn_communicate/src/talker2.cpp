#include<iostream>
#include "ros/ros.h"
#include "learn_communicate/beat.h"

int main(int argc,char **argv){
    ros::init(argc, argv, "talker2");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<learn_communicate::beat>("beat_sb", 1000);
    ros::Rate loop_rate(10);

    int beat_time = 0;
    while(ros::ok()){
        learn_communicate::beat msg;
        msg.name = "wcj";
        msg.beat_times = beat_time;
        msg.part = "arm";
        ROS_INFO("Beat %s on his %s %d times", msg.name.c_str(), msg.part.c_str(),msg.beat_times);
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
        beat_time++;
    }
}