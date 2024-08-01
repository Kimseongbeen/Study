
# ROS2 로봇 팔 패키지 만들기

extension

ROS2
Python

```
sudo apt-get update
sudo apt-get install ros-humble-joint-state-publisher-gui
```

## 1. 패키지 구조 생성
터미널 rarm_ws 실행 및 VScode Open

```
cd ~/Rarm_ws && source /opt/ros/humble/setup.bash && source install/setup.bash
code .
```

1. 새 ROS2 패키지를 생성합니다.
2. 패키지(src/robotic_arms_control) 내에 다음 디렉토리를 만듭니다:
   - `launch`
   - `urdf`
   - `config`

## 2. 파일 생성

1. `urdf` 디렉토리에 `arms.urdf` 파일을 생성합니다.
2. URDF 파일에 로봇 구조를 정의합니다:
   - arms.urdf 내용 붙여 넣기
   

## 3. 빌드 및 실행

1. 소스 파일 수정 후 `cbs` 명령어를 실행합니다.
2. `install/robotic_arms_control/share/robotic_arms_control` 내부 내용을 확인합니다.
3. 빌드 후 `config`, `launch`, `urdf` 폴더가 생성되었는지 확인합니다.
4. 다음 명령어로 RViz를 실행합니다:
   ```
   ros2 launch robotic_arms_control rviz_bringup.launch.py
   ```

## 4. RViz 설정

1. Add > TF 추가
2. Add > RobotModel 추가
3. Fixed Frame > "world" 선택
4. TF > Show Names 체크
5. RobotModel > Description Topic > "/robot_description" 선택
