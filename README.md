# ROS_BallChaser
The BallChaser project simulates a robot model which can chase a movable white ball in the gazebo world environment under the ROS (Robot Operating System) framework. The robot possesses a RGB camera which provides live video feed and this project contains the source code written in C++ language to analyze the images from RGB camera and outputs the direction for the robot to move. 

## Installation
1. Open a new terminal and build the catkin workspace:

    * `$ mkdir -p /home/workspace/catkin_ws/src`
 
    * `$ cd /home/workspace/catkin_ws/src`
 
    * `$ catkin_init_workspace`
 
  
2. Clone the project under  **/home/workspace/catkin_ws/src** directory:

    * `git clone https://github.com/tonyli0130/ROS_BallChaser.git`
 
 3. Make and compiler the project (**remember to source the environment variables in every new opened terminals**):
 
    * `cd /home/workspace/catkin_ws`
 
    * `catkin_make`
 
    * `source devel/setup.bash`
 
 
4. Update and upgrade the workspace image to get the lattest features of Gazebo, open a terminal and write the following statements:

    * `$ sudo apt-get update && sudo apt-get upgrade -y`

## Usage

1. Now run the ChaseBall project, first launch the `world.launch` file and have the robot simulation environment ready:

    * `roslaunch my_robot world.launch`
 
    The simulation environment contains the house, white ball and the robot. A closed view of the environment shows below:
 
 
      ![gazebo_world](https://user-images.githubusercontent.com/60047845/89233792-fb47c800-d5af-11ea-853f-10f9a1bd0d8c.PNG)
 
 
   The RViz which provides a better visualization of both robot and simulation environment will open simultaneously and the live video feed from robot camera will appear after waiting few minutes:



      ![camera_view](https://user-images.githubusercontent.com/60047845/89233806-01d63f80-d5b0-11ea-98cc-6136cba2c267.PNG)


2. Next launch the `ball_chaser.launch` file which opens the scripts containing the main code to interact with robot in gazeo world:
    * `roslaunch ball_chaser ball_chaser.launch`
 
   After launching the `world.launch` and `ball_chaser.launch`, the ball chasing process is ready. Use the drag button shown below to move the white ball to different locations as long as the robot camera can capture. The robot should start to move and chase toward the ball.
 
 
    ![drag_button](https://user-images.githubusercontent.com/60047845/89233799-ff73e580-d5af-11ea-87ea-d89b2f941129.PNG)
 
 ## Source Code Explaination
 
 The `/process_image` node has a subscriber which receives the live images from topic `/camera/rgb/image_raw` and its own callback function will analyze which direction the robot should move toward. After the direction is decided, the service client will send the velocity request through `/ball_chaser/command_robot` service to `/drive_bot` node which contains the service server.
 
 The `/drive_bot` node has a service server which receives request of linear velocity in x direction and angular velocity in z direction throught service `/ball_chaser/command_robot` and the publisher will publish them to topic `/cmd_vel` to move the robot. 
 
