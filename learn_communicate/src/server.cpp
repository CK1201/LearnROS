#include<iostream>
#include<cmath>
#include "ros/ros.h"
#include "learn_communicate/distance.h"


bool calDistance(learn_communicate::distance::Request &req,learn_communicate::distance::Response &res){
    res.dis = sqrt(pow((req.point1_x - req.point2_x), 2) + pow((req.point1_y - req.point2_y), 2));
    ROS_INFO("point1:(%f,%f)", req.point1_x, req.point1_y);
    ROS_INFO("point2:(%f,%f)", req.point2_x, req.point2_y);
    ROS_INFO("distance of two point:%f", res.dis);
    return true;
}

int main(int argc,char** argv){
    ros::init(argc, argv, "server");
    ros::NodeHandle n;
    ros::ServiceServer ser = n.advertiseService("cal_distance", calDistance);
    ROS_INFO("readt to cal distance");
    ros::spin();
    return 0;
}