## BumperBot 컨트롤러 설정 및 실행 가이드

### 1. 컨트롤러 패키지 생성
```bash
cd bumperbot_ws/src
catkin_create_pkg bumperbot_controller roscpp rospy
```

### 2. 컨트롤러 실행

#### A. Gazebo 시뮬레이션 실행
```bash
cd bumperbot_ws
source devel/setup.bash
roslaunch bumperbot_description gazebo.launch
```

#### B. 컨트롤러 실행
```bash
source devel/setup.bash
roslaunch bumperbot_controller controller.launch
```

#### C. 토픽 확인 및 조인트 상태 모니터링
```bash
rostopic list
```
새로 추가된 토픽:
- `/joint_states`: 각 조인트의 위치와 속도
- `/wheel_left_controller/command`
- `/wheel_right_controller/command`

조인트 상태 확인:
```bash
rostopic echo /joint_states
```

#### D. 로봇 제어
```bash
rostopic list
```
(joint_states 토픽은 제외됨)

1. 왼쪽 바퀴 회전 (로봇이 왼쪽으로 회전):
   ```bash
   rostopic pub /wheel_left_controller/command std_msgs/Float64 "data: 0.5"
   ```

2. 양쪽 바퀴 같은 방향 회전 (로봇 전진):
   ```bash
   rostopic pub /wheel_right_controller/command std_msgs/Float64 "data: 0.5"
   ```

3. 양쪽 바퀴 반대 방향 회전 (제자리 회전):
   ```bash
   rostopic pub /wheel_right_controller/command std_msgs/Float64 "data: -0.5"
   ```

참고: 명령어 입력 시 Tab 키를 두 번 눌러 자동 완성 기능을 활용할 수 있습니다.

이 가이드를 통해 BumperBot의 컨트롤러를 설정하고 Gazebo 시뮬레이션에서 로봇을 제어할 수 있습니다.