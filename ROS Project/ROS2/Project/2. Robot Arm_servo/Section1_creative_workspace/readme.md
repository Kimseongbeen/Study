```
mkdir -p arduinobot_ws/src
cd arduinobot_ws/src
ros2 pkg create --build-type ament_python arduinobot_py_examples
ros2 pkg create --build-type ament_python arduinobot_cpp_examples
cd ..
colcon build
cd install
. setup.bash

# 패키지 리스트 확인 - arduinobot 추가 확인
ros2 pkg list

# 새로운 터미널 열고 나서 ros2 pkg list 입력시 arduinobot 없음 이유는 새 터미널을 열때마다 . install/setup.bash 를 실행해줘야함
. install/setup.bash
ros2 pkg list
```