```
cd arduinobot_ws/src
ls
ros2 pkg create --build-type ament_camke arduinobot_description
cd ..
# pkg(description)에 파일 넣은 후 
colcon build
```
### Create & Complete URDF Model
```
## 새 터미널 오픈 및 조절 RViz
# Create
. install/setup.bash
sudo apt-get install ros-humble-urdf-tutorial
ros2 launch urdf_tutorial display.launch.py model:=/home/smileb(usr 이름)/arduinobot_ws/src/arduinobot_description/urdf/arduinobot.urdf.xacro

# Complete
ros2 launch urdf_tutorial display.launch.py model:=/home/smileb(usr 이름)/arduinobot_ws/src/arduinobot_description/urdf/arduinobot.urdf.xacro
```

### RViz 실행
```
. install/setup.bash
ros2 launch arduinobot_description display.launch.py
```

### Gazebo
```
. install/setup.bash
ros2 launch arduinobot_description gazebo.launch.py
```