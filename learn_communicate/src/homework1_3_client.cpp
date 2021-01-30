#include "ros/ros.h"
#include "learn_communicate/moveAction.h"
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<learn_communicate::moveAction> Client_move;

void doneCallback(const actionlib::SimpleClientGoalState& state,const learn_communicate::moveResultConstPtr& result){
    ROS_INFO("reach the goal");
    ros::shutdown();
}

void activateCallback(){
    ROS_INFO("begin to move");
}

void feedbackCallback(const learn_communicate::moveFeedbackConstPtr& feedback){
    ROS_INFO("reach(%f,%f),distance:%f", feedback->x, feedback->y, feedback->distance);
}

int main(int argc,char** argv){
    ros::init(argc, argv, "homework1_3_client");
    ros::NodeHandle n;
    Client_move client_move("move_to_goal", true);
    client_move.waitForServer();
    learn_communicate::moveGoal goal;
    goal.x = 10;
    goal.y = 10;
    client_move.sendGoal(goal, &doneCallback, &activateCallback, &feedbackCallback);
    ros::spin();
    return 0;
}