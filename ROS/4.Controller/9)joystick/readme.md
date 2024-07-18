터미널 - gazebo 실행
cd bumperbot_ws
source devel/setup.bash
roslaunch bumperobt_description gazebo.launch

새 터미널 오픈 - 로봇 제어 시스템
source devel/setup.bash
roslaunch bumperbot_controller controller.launch

새터미널 open 후 Joystick 연결
source devel/setup.bash
roslaunch bumperbot_controller joystick_teleop.launch