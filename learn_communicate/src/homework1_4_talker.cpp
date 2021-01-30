#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "tf/transform_broadcaster.h"
#include "tf/tfMessage.h"

int main(int argc,char** argv){
    ros::init(argc, argv, "talker_PointStamped");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<geometry_msgs::PointStamped>("data_PointStamped", 10);
    tf::TransformBroadcaster tf_broadcaster;
    ros::Rate loop_rate(1);
    float count = 1;
    while (ros::ok())
    {
        geometry_msgs::PointStamped msg;
        msg.point.x=50;
        msg.point.y=50;
        msg.point.z=count;
        msg.header.frame_id = "base_laser";
        msg.header.stamp = ros::Time::now();
        ROS_INFO("send data (%f,%f,%f)", msg.point.x, msg.point.y, msg.point.z);
        pub.publish(msg);
        count++;

        
        tf::StampedTransform tf_transform;
        tf_transform.setOrigin(tf::Vector3(10, 0, 20));
        tf::Quaternion q;
        q.setRPY(0, 0, 0);
        tf_transform.setRotation(q);
        tf_broadcaster.sendTransform(tf::StampedTransform(tf_transform, ros::Time::now(), "base_link", "base_laser"));
        

        loop_rate.sleep();
        ros::spinOnce();
        
    }
}