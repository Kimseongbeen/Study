1. Udemy Workspace 생성:
   ```
   mkdir -p /Rarm_ws/src
   cd Rarm_ws/
   ```

2. ROS2 설치 확인 및 초기 빌드:
   ```
   colcon build
   ```

3. ROS2 패키지 생성:
   ```
   cd src
   ros2 pkg create --build-type ament_python robotic_arms_control
   cd ..
   colcon build
   ```

4. 빌드 및 소싱 과정 간소화:
   `.bashrc` 파일에 다음 별칭(alias) 추가:
   ```
   alias cbs="colcon build && source install/setup.bash"
   alias sws="source install/setup.bash"
   alias cb="colcon build"
   ```

5. 별칭 사용 예:
   - `cbs`: 빌드 후 워크스페이스 소싱
   - `sws`: 워크스페이스 소싱만 수행
   - `cb`: 빌드만 수행

이렇게 설정하면 매번 `source install/setup.bash`를 실행할 필요 없이 패키지를 더 쉽게 실행하고 관리할 수 있습니다.