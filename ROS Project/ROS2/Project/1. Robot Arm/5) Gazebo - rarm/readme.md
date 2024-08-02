arms_pos_controller.yaml - config

gazebo_bringup.launch.py - launch

arms.urdf - urdf 

위 세개 파일 업로드

라이브러리 다운
```bash
sudo apt update && sudo apt install -y ros-humble-franka-description gazebo ros-humble-gazebo-ros-pkgs ros-humble-gazebo-ros2-control ros-humble-gazebo-ros
```
패스 설정 - 라이브러리 환경 설정
```bash
export GAZEBO_MODEL_PATH=$GAZEBO_MODEL_PATH:/opt/ros/humble/share
export GAZEBO_PLUGIN_PATH=$GAZEBO_PLUGIN_PATH:/opt/ros/humble/lib/gazebo_ros
```

빌드 후 설치
```bash
cbs && ros2 launch robotic_arms_control gazebo_bringup.launch.py
```

