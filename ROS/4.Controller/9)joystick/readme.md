# Bumperbot Controller with Joystick

이 프로젝트는 ROS를 사용하여 조이스틱으로 Bumperbot 로봇을 제어하는 시스템을 구현합니다.

## joystick 세팅
공식 가이드 : http://wiki.ros.org/joy/Tutorials/ConfiguringALinuxJoystick
테스트 : https://hardwaretester.com/gamepad
teleop_twist_joy' 패키지가 설치
sudo apt-get install ros-noetic-teleop-twist-joy

ls /dev/input/

sudo jstest /dev/input/jsX

ls -l /dev/input/jsX

## 설정

1. 조이스틱을 USB 또는 블루투스로 연결합니다.
2. ROS 워크스페이스를 소스합니다: `source devel/setup.bash`

## 실행 방법

수정 후 패키지 빌드

cd ~/bumperbot_ws
catkin_make
source devel/setup.bash

1. Gazebo 시뮬레이션 실행:

roslaunch bumperbot_description gazebo.launch

2. 로봇 제어 시스템 실행:

roslaunch bumperbot_controller controller.launch

3. 조이스틱 텔레오퍼레이션 노드 실행:

roslaunch bumperbot_controller joystick_teleop.launch

모니터링 

rostopic echo /bumperbot_controller/cmd_vel


## 파일 설명

- `joystick.yaml`: 조이스틱 축과 로봇 명령 간의 매핑을 정의
- `joystick_teleop.launch`: 조이스틱 관련 노드들을 실행하는 launch 파일

## 작동 원리

1. `joy_node`가 조이스틱 입력을 읽어 `/joy` 토픽으로 발행
2. `joy_teleop` 노드가 이 입력을 구독하고 `joystick.yaml` 설정에 따라 변환
3. 변환된 명령은 `/bumperbot_controller/cmd_vel` 토픽으로 발행
4. 로봇 컨트롤러가 이 명령을 받아 실제 모터 제어

## 주의사항

- 조이스틱이 제대로 인식되지 않는 경우, `/dev/input/js0` 장치 파일을 확인하세요.
- 축 매핑은 사용 중인 조이스틱 모델에 따라 다를 수 있습니다. 필요시 `joystick.yaml` 파일을 수정하세요.