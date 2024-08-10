```
ros2 launch moveit_setup_assistant setup_assistant.launch.py
```

```
# A 터미널
. install/setup.bash
ros2 launch arduinobot_description gazebo.launch.py

# B 터미널
. install/setup.bash
ros2 launch arduinobot_controller controller.launch.py

# C 터미널
. install/setup.bash
ros2 launch arduinobot_moveit moveit.launch.py

```

RViz

- Fixed Frame : World
- Add 
motionplanning