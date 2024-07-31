1. ROS2 워크스페이스 설정:
   ```bash
   sudo apt install python3-colcon-common-extensions
   mkdir -p Rarm_ws/src
   cd Rarm_ws/
   ```

2. 초기 빌드:
   ```bash
   colcon build
   ```

3. ROS2 패키지 생성:
   ```bash
   source /opt/ros/humble/setup.bash
   cd src
   ros2 pkg create --build-type ament_python robotic_arms_control
   cd ..
   colcon build
   ```

4. 빌드 및 소싱 간소화 (.bashrc에 추가):
   ```bash
   alias rarm_ws='cd ~/Rarm_ws && source /opt/ros/humble/setup.bash && source install/setup.bash'
   alias cbs='colcon build && source install/setup.bash'
   alias sws='source install/setup.bash'
   alias cb='colcon build'
   ```

`source /opt/ros/humble/setup.bash`와 `source install/setup.bash`의 차이:

1. `source /opt/ros/humble/setup.bash`:
   - ROS2 Humble 배포판의 기본 설정을 로드합니다.
   - 시스템에 설치된 ROS2의 전역 환경을 설정합니다.
   - ROS2의 기본 명령어, 라이브러리, 패키지 등을 사용할 수 있게 해줍니다.

2. `source install/setup.bash`:
   - 현재 워크스페이스(Rarm_ws)의 로컬 설정을 로드합니다.
   - 워크스페이스에서 개발 중인 사용자 정의 패키지와 그 의존성을 환경에 추가합니다.
   - 워크스페이스의 패키지를 ROS2 환경에서 인식하고 실행할 수 있게 해줍니다.