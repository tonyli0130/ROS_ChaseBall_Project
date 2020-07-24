#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"
#include <std_msgs/Float64.h>
#include <unistd.h>

// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;
geometry_msgs::Twist motor_command;

// TODO: Create a handle_drive_request callback function that executes whenever a drive_bot service is requested
// This function should publish the requested linear x and angular velocities to the robot wheel joints
// After publishing the requested velocities, a message feedback should be returned with the requested wheel velocities

bool my_callback(ball_chaser::DriveToTarget::Request &req,
                 ball_chaser::DriveToTarget::Response &res)
{
    ROS_INFO("The Service /ball_chaser/command_robot has been called");
    motor_command.linear.x = req.linear_x;
    motor_command.angular.z = req.angular_z;

    if (motor_command.angular.z == 0.2) {
        ROS_INFO("Turing Left");
        motor_command_publisher.publish(motor_command);
        usleep(1000000);
    } else if (motor_command.angular.z == -0.2) {
        ROS_INFO("Turing Right");
        motor_command_publisher.publish(motor_command);
        usleep(1000000);
    } else {
        motor_command_publisher.publish(motor_command);
    }

    

    res.msg_feedback = "The linear velocity of robot is " + std::to_string(motor_command.linear.x) + ", and the angular velocity of robot is " +  std::to_string(motor_command.angular.z);
    ROS_INFO_STREAM(res.msg_feedback);
    return true;

}
int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "drive_bot");

    // Create a ROS NodeHandle object
    ros::NodeHandle n;

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    // TODO: Define a drive /ball_chaser/command_robot service with a handle_drive_request callback function
    ros::ServiceServer my_service = n.advertiseService("/ball_chaser/command_robot", my_callback);

    // TODO: Handle ROS communication events
    //ros::spin();
    ROS_INFO("Service /ball_chaser/command_robot Ready");
    ros::spin();

    return 0;
}
