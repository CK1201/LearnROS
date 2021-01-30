#include<iostream>
#include "ros/ros.h"
#include "learn_communicate/distance.h"

int main(int argc,char** argv){
    ros::init(argc, argv, "client");
    if(argc!=5){
        ROS_INFO("please input two point:x1 y1 x2 y2");
        return 1;
    }
    ros::NodeHandle n;
    ros::ServiceClient cli = n.serviceClient<learn_communicate::distance>("cal_distance");
    learn_communicate::distance srv;
    srv.request.point1_x = atof(argv[1]);
    srv.request.point1_y = atof(argv[2]);
    srv.request.point2_x = atof(argv[3]);
    srv.request.point2_y = atof(argv[4]);

    if(cli.call(srv)){
        ROS_INFO("distance of two point is:%f", srv.response.dis);
    }
    else{
        ROS_ERROR("Fail");
        return 1;
    }
    return 0;
}