
https://drive.google.com/file/d/1wZ5hWY3-TxNJ2jlb9edfXXXRHFhalbIk/view?usp=sharing

1. src 폴더 구조 설정:
   ```
   src/
   ├── franka_description
   └── robotic_arms_control
   ```

2. 워크스페이스 빌드:
   ```
   cbs
   ```
   출력:
   ```
   Starting >>> franka_description
   Starting >>> robotic_arms_control
   Finished <<< franka_description
   ...
   ```

3. 필요한 패키지 설치:
   ```
   sudo apt install ros-humble-gazebo-ros2-control
   ```

4. 의존성 설치:
   ```
   rosdep install --from-paths src --ignore-src -r -y
   ```

5. 실행 중인 Gazebo 프로세스 종료:
   ```
   killall gzserver gzclient
   ```

6. 런치 파일 실행:
   ```
   ros2 launch robotic_arms_control gazebo_bringup.launch.py
   ```