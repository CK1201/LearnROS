#include "ros/ros.h"
#include "learn_communicate/washdishAction.h"
#include <actionlib/server/simple_action_server.h>

typedef actionlib::SimpleActionServer<learn_communicate::washdishAction> Server;

void execute(const learn_communicate::washdishGoalConstPtr &goal,Server* as){
    ros::Rate r(1);
    learn_communicate::washdishFeedback feedback;
    ROS_INFO("Dishwasher %d is working", goal->dishwasher_id);
    for(int i = 1; i < 10;i++){
        feedback.perscent_complete = i * 10;
        as->publishFeedback(feedback);
        r.sleep();
    }
    ROS_INFO("Dishwasher %d finish working", goal->dishwasher_id);
    as->setSucceeded();
}

int main(int argc,char** argv){
    ros::init(argc, argv, "action_server");
    ros::NodeHandle n;
    Server server(n, "do_dishes", boost::bind(&execute, _1, &server), false);
    server.start();
    ros::spin();
    return 0;
}