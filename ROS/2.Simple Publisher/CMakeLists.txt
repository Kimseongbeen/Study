cmake_minimum_required(VERSION X.X.X) # 내 버전에 맞게 수정
project(bumperbot_examples)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

catkin_package(

)

include_directories(
    ${catkin_INCLUDE_DIRS}
)

# 추가 부분
catkin_install_python(PROGRAMS
  nodes/simple_publisher.py
  DESTINATION ${CATKKIN_PACKAGE_BIN_DESTINATION})