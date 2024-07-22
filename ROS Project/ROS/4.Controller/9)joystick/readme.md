# Bumperbot Controller with Joystick

이 프로젝트는 ROS를 사용하여 조이스틱으로 Bumperbot 로봇을 제어하는 시스템을 구현합니다.

## 조이스틱 설정

1. 공식 가이드: [ROS Joy 튜토리얼](http://wiki.ros.org/joy/Tutorials/ConfiguringALinuxJoystick)
2. 조이스틱 테스트: [온라인 게임패드 테스터](https://hardwaretester.com/gamepad)
3. 필요한 패키지 설치:
   ```
   sudo apt-get install ros-noetic-teleop-twist-joy
   ```
4. 조이스틱 연결 확인:
   ```
   ls /dev/input/
   sudo jstest /dev/input/jsX
   ls -l /dev/input/jsX
   ```

## 초기 설정

1. 조이스틱을 USB 또는 블루투스로 연결합니다.
2. ROS 워크스페이스를 소스합니다:
   ```
   source devel/setup.bash
   ```

## 실행 방법
소스 업로드 후 
패키지 빌드:
```
cd ~/bumperbot_ws
catkin_make
source devel/setup.bash
```

각 구성 요소 실행:

1. Gazebo 시뮬레이션:
   ```
   roslaunch bumperbot_description gazebo.launch
   ```

2. 로봇 제어 시스템:
   ```
   roslaunch bumperbot_controller controller.launch
   ```

3. 조이스틱 텔레오퍼레이션 노드:
   ```
   roslaunch bumperbot_controller joystick_teleop.launch
   ```

모니터링:
```
rostopic echo /bumperbot_controller/cmd_vel
```

## 주요 파일

- `joystick.yaml`: 조이스틱 축과 로봇 명령 간의 매핑 정의
- `joystick_teleop.launch`: 조이스틱 관련 노드 실행을 위한 launch 파일

## 작동 원리

1. `joy_node`: 조이스틱 입력을 읽어 `/joy` 토픽으로 발행
2. `joy_teleop` 노드: `/joy` 토픽 구독 및 `joystick.yaml` 설정에 따라 변환
3. 변환된 명령: `/bumperbot_controller/cmd_vel` 토픽으로 발행
4. 로봇 컨트롤러: 발행된 명령을 받아 실제 모터 제어

## 주의사항

- 조이스틱 인식 문제 시 `/dev/input/js0` 장치 파일을 확인하세요.
- 축 매핑은 조이스틱 모델에 따라 다를 수 있습니다. 필요 시 `joystick.yaml` 파일을 수정하세요.
