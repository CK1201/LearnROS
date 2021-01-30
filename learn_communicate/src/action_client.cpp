#include "ros/ros.h"
#include <actionlib/client/simple_action_client.h>
#include "learn_communicate/washdishAction.h"

typedef actionlib::SimpleActionClient<learn_communicate::washdishAction> Client;

void doneCallback(const actionlib::SimpleClientGoalState& state,const learn_communicate::washdishResultConstPtr& result){
    ROS_INFO("all the dishes are cleaned");
    ros::shutdown();
}

void activateCallback(){
    ROS_INFO("goal has been activated");
}

void feedbackCallback(const learn_communicate::washdishFeedbackConstPtr& feedback){
    ROS_INFO("percent_complete:%f", feedback->perscent_complete);
}

int main(int argc,char** argv){
    ros::init(argc, argv, "action_client");
    ros::NodeHandle n;
    Client client("do_dishes", true);
    client.waitForServer();
    learn_communicate::washdishGoal goal;
    goal.dishwasher_id = 1;
    client.sendGoal(goal, &doneCallback, &activateCallback, &feedbackCallback);
    ros::spin();
    return 0;
}