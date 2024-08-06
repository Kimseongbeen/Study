기존 ROS 2 및 관련 패키지 제거:

```
sudo apt remove ros-* && sudo apt autoremove
```

# MoveIt Task Constructor Pick and Place 튜토리얼

이 README는 MoveIt Task Constructor를 사용하여 Pick and Place 작업을 구현하는 과정을 안내합니다.

## 사전 준비

1. ROS 2 Iron 설치
   - Ubuntu 22.04 사용 권장
   - 다음 링크의 지침을 따라 설치: https://docs.ros.org/en/iron/Installation/Ubuntu-Install-Debians.html
   
   주요 설치 단계:
   ```bash
   sudo apt update && sudo apt install software-properties-common
   sudo add-apt-repository universe
   sudo apt update && sudo apt install curl
   sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
   echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
   sudo apt update
   sudo apt upgrade
   sudo apt install ros-iron-desktop
   ```

가제보 삭제, gazebo11 설치

```
sudo add-apt-repository --remove ppa:openrobotics/gazebo11-gz-cli

sudo apt update
sudo apt install libgazebo11=11.10.2+dfsg-1
rosdep install -r --from-paths . --ignore-src --rosdistro $ROS_DISTRO -y
```
에러발생
![](https://velog.velcdn.com/images/smile_b/post/361beb27-370f-4770-ac3c-6c445c6600b7/image.png)
https://github.com/doosan-robotics/doosan-robot2/issues/61

2. 환경 설정
   ```bash
   echo "source /opt/ros/iron/setup.bash" >> ~/.bashrc
   source ~/.bashrc
   ```

3. 추가 도구 및 의존성 설치
   ```bash
   sudo apt install python3-rosdep python3-colcon-common-extensions python3-colcon-mixin python3-vcstool
   sudo rosdep init
   rosdep update
   ```

4. MoveIt 2 설치
   ```bash
   sudo apt install ros-iron-moveit
   ```

5. 작업 환경 설정
   ```bash
   mkdir -p ~/ws_moveit/src
   cd ~/ws_moveit/src
   git clone https://github.com/moveit/moveit2_tutorials -b iron
   vcs import < moveit2_tutorials/moveit2_tutorials.repos
   cd ~/ws_moveit
   rosdep install -r --from-paths . --ignore-src --rosdistro iron -y
   colcon build --mixin release
   source ~/ws_moveit/install/setup.bash
   ```

## MoveIt Task Constructor 튜토리얼 시작

1. 새 패키지 생성
   ```bash
   cd ~/ws_moveit/src
   ros2 pkg create --build-type ament_cmake --dependencies moveit_task_constructor_core rclcpp --node-name mtc_node mtc_tutorial
   ```

2. 코드 작성
   `~/ws_moveit/src/mtc_tutorial/src/mtc_node.cpp` 파일을 열고 다음 순서로 코드를 작성합니다:

   a. 필요한 헤더 파일 포함
   b. MTCTaskNode 클래스 정의
   c. MTCTaskNode 생성자 정의
   d. getNodeBaseInterface() 함수 정의
   e. setupPlanningScene() 함수 정의
   f. doTask() 함수 정의
   g. createTask() 함수 정의 (기본 task 설정, 솔버 정의, 스테이지 추가)
   h. main() 함수 정의

3. CMakeLists.txt 수정
   `~/ws_moveit/src/mtc_tutorial/CMakeLists.txt` 파일을 열고 다음 라인을 추가합니다:
   ```cmake
   install(DIRECTORY launch
     DESTINATION share/${PROJECT_NAME}
   )
   ```

4. 런치 파일 작성
   `~/ws_moveit/src/mtc_tutorial/launch/pick_place_demo.launch.py` 파일을 생성하고 런치 파일 코드를 작성합니다.

5. 빌드 및 실행
   ```bash
   cd ~/ws_moveit
   colcon build --packages-select mtc_tutorial
   source install/setup.bash
   ros2 launch moveit2_tutorials mtc_demo.launch.py
   ```
   새 터미널에서:
   ```bash
   ros2 launch mtc_tutorial pick_place_demo.launch.py
   ```

## 단계별 구현

1. "open hand" 스테이지 추가
2. Pick 스테이지 추가
3. Place 스테이지 추가
4. "return home" 스테이지 추가

각 단계의 세부 구현은 `createTask()` 함수 내에서 이루어집니다. 튜토리얼 문서를 참조하여 각 스테이지의 코드를 순서대로 추가하세요.

## 디버깅 및 시각화

- RViz를 사용하여 로봇 동작과 계획된 경로를 시각화할 수 있습니다.
- 터미널 출력을 통해 각 스테이지의 성공/실패 여부를 확인할 수 있습니다.
