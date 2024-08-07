1. 기존 ROS 2 및 관련 패키지 제거:
   ```
   sudo apt remove ros-* && sudo apt autoremove
   ```

2. ROS 2 관련 디렉토리 삭제:
   ```
   rm -rf ~/ros2_ws
   rm -rf ~/ws_moveit
   ```

3. ROS 2 Iron 설치 (Ubuntu 22.04 기준):
   ```
   sudo apt update && sudo apt install software-properties-common
   sudo add-apt-repository universe
   sudo apt update && sudo apt install curl
   sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
   echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
   sudo apt update
   sudo apt upgrade
   sudo apt install ros-iron-desktop
   ```

4. 환경 설정:
   ```
   echo "source /opt/ros/iron/setup.bash" >> ~/.bashrc
   source ~/.bashrc
   ```

5. 개발 도구 및 ROS 2 패키지 설치:
   ```
   sudo apt install python3-rosdep python3-rosinstall python3-rosinstall-generator python3-wstool build-essential
   sudo apt install python3-colcon-common-extensions
   ```

6. rosdep 초기화:
   ```
   sudo rosdep init
   rosdep update
   ```

7. MoveIt 2 워크스페이스 생성 및 소스 코드 다운로드:
   ```
   mkdir -p ~/ws_moveit/src
   cd ~/ws_moveit/src
   git clone https://github.com/ros-planning/moveit2.git -b iron
   vcs import < moveit2/moveit2.repos
   ```

8. 의존성 설치:
   ```
   cd ~/ws_moveit
   rosdep install -r --from-paths . --ignore-src --rosdistro iron -y
   ```

9. 빌드:
   ```
   colcon build --event-handlers desktop_notification- status- --cmake-args -DCMAKE_BUILD_TYPE=Release
   ```
   빌드는 20분 소요

10. 환경 설정:
    ```
    echo "source ~/ws_moveit/install/setup.bash" >> ~/.bashrc
    source ~/.bashrc
    ```

11. 설치

```
git clone https://github.com/moveit/moveit_task_constructor.git -b ros2
```

