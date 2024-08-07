iron 에러, humble 사용
https://github.com/moveit/moveit2_tutorials/issues/931

https://www.youtube.com/watch?v=gPjoFJBKXf0

git clone https://github.com/moveit/moveit2_tutorials -b humble


source /opt/ros/humble/setup.bash


```
# 첫번째 창
ros2 launch moveit2_tutorials mtc_demo.launch.py

# 두번째 창
ros2 launch moveit2_tutorials pick_place_demo.launch.py
```