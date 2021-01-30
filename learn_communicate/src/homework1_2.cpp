#include<iostream>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"
#include "turtlesim/Pose.h"

void printPoseCallback(const turtlesim::Pose &msg){
    ROS_INFO("position:(%f,%f)", msg.x, msg.y);
    ROS_INFO("theta:%f", msg.theta);
    ROS_INFO("linear velocity:%f", msg.linear_velocity);
    ROS_INFO("angular velocity:%f", msg.angular_velocity);
}

int main(int argc,char **argv){
    ros::init(argc, argv, "contorl_turtle");
    ros::NodeHandle n;

    ros::service::waitForService("spawn");
    ros::ServiceClient add_turtle = n.serviceClient<turtlesim::Spawn>("spawn");
    turtlesim::Spawn srv;
    srv.request.x = 5;
    srv.request.y = 5;
    srv.request.theta = 0;
    srv.request.name = "turtle2";
    add_turtle.call(srv);

    ros::Publisher pub1 = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
    ros::Publisher pub2 = n.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 10);
    ros::Subscriber sub = n.subscribe("turtle1/pose", 10, printPoseCallback);
    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        geometry_msgs::Twist cmd_vel_msg;
        cmd_vel_msg.linear.x = 1;
        cmd_vel_msg.angular.z = 1;
        pub1.publish(cmd_vel_msg);
        cmd_vel_msg.linear.x = 1;
        cmd_vel_msg.angular.z = -1;
        pub2.publish(cmd_vel_msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
}