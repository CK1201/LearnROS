#include "ros/ros.h"
#include "tf/transform_listener.h"
#include "sensor_msgs/LaserScan.h"


class LearnTf{
    private:
        ros::NodeHandle m_n;
        ros::Subscriber m_sub;
        tf::TransformListener m_listener;
        tf::StampedTransform m_transform;
        ros::Timer m_timer;
        geometry_msgs::PointStamped m_point_laser, m_point_base;

    public:
        LearnTf(){
            m_point_laser.header.stamp = ros::Time::now();
            m_point_laser.header.frame_id = "base_laser";
            m_point_laser.point.x = 0;
            m_point_laser.point.y = 0;
            m_point_laser.point.z = 0;
            m_sub = m_n.subscribe("data_PointStamped", 10, &LearnTf::msgCallback,this);
        }
        void msgCallback(const geometry_msgs::PointStamped &point){
            m_point_laser = point;
            // ROS_INFO("I heard (%f,%f,%f)", m_point_laser.point.x, m_point_laser.point.y, m_point_laser.point.z);
            try{
                m_listener.waitForTransform("base_link", "base_laser", ros::Time(0), ros::Duration(3.0));
                m_listener.lookupTransform("base_link", "base_laser", ros::Time(0), m_transform);
                m_listener.transformPoint("base_link", m_point_laser, m_point_base);
                ROS_INFO("laser point:(%f,%f,%f)", m_point_laser.point.x, m_point_laser.point.y, m_point_laser.point.z);
                ROS_INFO("base point:(%f,%f,%f)", m_point_base.point.x, m_point_base.point.y, m_point_base.point.z);
                ROS_INFO("---------------------------------------");
            }
            catch(tf::TransformException &ex){
                ROS_ERROR("%s", ex.what());
                ros::Duration(1).sleep();
            }
        }
};


int main(int argc,char** argv){
    ros::init(argc, argv, "listener_PointStamped");
    LearnTf learntf;
    // ros::NodeHandle n;
    // ros::Subscriber sub = n.subscribe("data_PointStamped", 10, msgCallback);

    ros::spin();
    return 0;
}