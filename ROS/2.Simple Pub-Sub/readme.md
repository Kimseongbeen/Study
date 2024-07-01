# Pubblisher
# 사용 언어
## Python 
### 1. Simple_publisher.py 생성
코드 참조
### 2. CMakeLists.txt 코드 추가
```
catkin_install_python(PROGRAMS
  nodes/simple_publisher.py
  DESTINATION ${CATKKIN_PACKAGE_BIN_DESTINATION})
```
### 3. 터미널

```
$ cd bumperbot_ws
$ catkin_make
$ roscore
$ source devel/setup.bash 


# 아래 코드를 입력 후 hello world from python +1을 보내는중
# 받는 곳이 없어 출력되진 않음
$ rosrun bumperbot_examples simple_publisher.py


# simper_publisher에서 작성한 smileb가 list에 출력되는지 확인
$ rostopic list 


# ctrl + c 로 노드를 종료했을때 list 확인
# 다시 rostopic list를 입력하면 smileb가 출력되지 않는 모습
$ ctrl + c


# 아래를 실행하게 되면 위에서 보내고 있던 hellow world +1 출력을 받게됨
$ rostopic echo /smileb


# 아래 코드 다시 실행시 받고있는 측에서는 다시 1부터 받음
$ rosrun bumperbot_examples simple_publisher.py


# 주제에 대한 추가적인 정보 출력
$ rostopic info /smileb


# topic에 게시된 메시지를 분석해 빈도를 계산
# 빈도는 py 함수에서 선언했던 rospy.Rate(10) 속도와 같다
$ rostopic hz /chatter 
```

## C++
### 1. Simple_publisher.cpp 생성
코드 참조
### 2. CMakeLists.txt 코드 추가
```
$ add_executable(simple_cpp_publisher nodes/simple_publisher.cpp)
$ target_link_libraries(simple_cpp_publisher ${catkin_LIBRARIES})
```

### 3. 터미널
```
### 마스터 터미널
$ cd bumperbot_ws
$ catkin_make
$ roscore


### 슬레이브 터미널 - publisher
$ source devel/setup.bash
$ rosrun bumperbot_examples simple_cpp_publisher

# 값 받고있는 도중 publisher 터미널에서 다시 cpp 코드 실행 시 1부터 값 수신

### 슬레이브 터미널 - subscribe
$ rostopic list


# /smileb, /rosout, /rosout_agg 출력 확인
# publisher 터미널에서 코드를 종료(rosrun cpp)하고 subscribe 터미널에서 topic list를 입력시 /smileb는 출력되지 않음
# /smileb 토픽으로 값 받기
$ rostopic echo /smileb


# topic에 대한 내용 확인 현재 open 돼있는 topic은 cpp 이므로 python 정보는 출력되지 않음
$ rostopic info /smileb


# smileb topic의 hz(주파수) 분석 빈도수가 얼마나 되는지,
rostopic hz /smileb
# 10hz 초당 10개의 메시지 전송

```

# subscriber
# 사용 언어
## Python 
### 1. Simple_publisher.py 생성
코드 참조
### 2. CMakeLists.txt 코드 추가

```
catkin_install_python(PROGRAMS
  nodes/simple_publisher.py # pub
  nodes/simple_subscriber.py #sub
  DESTINATION ${CATKKIN_PACKAGE_BIN_DESTINATION})
```
### 3. 터미널
#### 노드 실행
```
cd bumperbot_ws
catkin_make
roscore
```
#### 워크스페이스 불러오기
```
source devel/setup.bash
rosrun bumperbot_examples simple_subscriber.py
```

#### 테스트
```
# 설정한 토픽 출력되는지 확인
rostopic list
# 해당 토픽의 정보 출력
rostopic info /smileb
# 특정 topic에 신호 전송
# 입력 시 워크스페이스에서 실행하고 있는 subscriber에서 Hi ROS 문자열 수신
rostopic pub /smileb std_msgs/String "data: 'Hi ROS'"
```

#### pub 파일 실행
subscribe 파일이 실행되고 있는 터미널이 아닌 새로운 터미널에서 실행
cpp_ publisher 송신 값이 subscribe를 실행하고있는 워크스페이스에 수신
```
rosrun bumperbot_examples simple_cpp_publisher
```

