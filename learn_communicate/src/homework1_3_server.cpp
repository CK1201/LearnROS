#include "ros/ros.h"
#include "learn_communicate/moveAction.h"
#include <actionlib/server/simple_action_server.h>
// #include <climits>
#include <cmath>

typedef actionlib::SimpleActionServer<learn_communicate::moveAction> Server_move;

void execute(const learn_communicate::moveGoalConstPtr& goal,Server_move* as){
    ROS_INFO("get goal:(%f,%f) start moving", goal.get()->x, goal.get()->y);
    ros::Rate r(1);
    learn_communicate::moveFeedback feedback;
    double distance0 = sqrt(pow(goal->x, 2) + pow(goal->y, 2));
    feedback.distance = distance0;
    double velocity = 1;
    double theta = atan2(goal->x, goal->y);
    while (feedback.distance != 0)
    {
        if (feedback.distance-velocity>0){
            feedback.distance = feedback.distance - velocity;
        }
        else{
            feedback.distance = 0;
        }
        feedback.x = (distance0 - feedback.distance) * cos(theta);
        feedback.y = (distance0 - feedback.distance) * sin(theta);
        as->publishFeedback(feedback);
        r.sleep();
    }
    ROS_INFO("reach goal:(%f,%f) stop moving", goal.get()->x, goal.get()->y);
    as->setSucceeded();
}

int main(int argc,char** argv){
    ros::init(argc, argv, "homework1_3_server");
    ros::NodeHandle n;
    Server_move server_move(n, "move_to_goal", boost::bind(&execute, _1, &server_move), false);
    server_move.start();
    ros::spin();
    return 0;
}