### 1. Simple_publisher.py 생성
코드 참조
### 2. CMakeLists.txt 코드 추가
코드 참조 <br>

추가 부분만 작성!
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


