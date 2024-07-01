cmake_minimum_required(VERSION 3.0.2) # 본인 버전에 맞게 변경돼있을 것
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

## Publisher & Subscriber
# Python 추가 부분
catkin_install_python(PROGRAMS
  nodes/simple_publisher.py # pub
  nodes/simple_subscriber.py #sub
  DESTINATION ${CATKKIN_PACKAGE_BIN_DESTINATION})

# C++ 추가 부분
add_executable(simple_cpp_publisher nodes/simple_publisher.cpp)
target_link_libraries(simple_cpp_publisher ${catkin_LIBRARIES})
