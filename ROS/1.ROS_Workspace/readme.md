## ROS WS 를 만드는 작업

### 1. 워크스페이스 만들기
```
mkdir bumperbot_ws
cd bumperbot_ws
```

![](https://velog.velcdn.com/images/smile_b/post/ef6699cb-9729-4d64-9f3c-76919c0a2039/image.png)

### 2. src 폴더 생성
```
mkdir src
```
![](https://velog.velcdn.com/images/smile_b/post/ba95a8a5-64c2-4e7a-a84d-04922fd2cb69/image.png)
### 3. 워크스페이스 초기화
#ROS 오버레이 - 모든 ROS 패키지와 코스를 따라 개발할 모든 새 패키지에 접근할 수 있다.
#### 캣킨은 기본적인 빌드 도구이며 빌드 도구는 소스코드를 변환한다. > 파이썬,C++을 이용하여 실행 파일로 개발할 것.
```
catkin_make
```
![](https://velog.velcdn.com/images/smile_b/post/6f04b0da-9403-4dda-ab26-cc32a1ff3e9d/image.png)
### 4. ROS 패키지 생성

#### catkin_create_pkg [패키지 이름] [종속성 라이브러리]
```
catkin_create_pkg bumperbot_examples roscpp rospy std_msgs 
```
![](https://velog.velcdn.com/images/smile_b/post/2b48a9b8-35e6-46d7-b6c5-2a2f71b8054a/image.png)
### 5. WS 다시 구축
#### 생성한 새 패키지를 포함해서 다시 구축
```
catkin_make
```
![](https://velog.velcdn.com/images/smile_b/post/eb58e666-8514-42a2-9339-74ee0e242255/image.png)
### 6. WS 활성화
#### bumperbot 폴더가 ROS 오버레이로 인식 > devel 폴더에 자동으로 생성된 파일을 소싱
```
source setup.bash
```
![](https://velog.velcdn.com/images/smile_b/post/f83c29da-69f7-403a-a077-7b0db04a46c1/image.png)

![](https://velog.velcdn.com/images/smile_b/post/15f77d06-bda1-48c6-b6cd-fec0878e7af1/image.png)
### 7. ROS 패키지 리다이렉션
#### WS가 정상적으로 활성화가 되면 해당 명령어를 입력했을 때 이동한다.
```
roscd bumperbot_examples
```
![](https://velog.velcdn.com/images/smile_b/post/7708cf22-cb4c-4bbd-9917-622664693140/image.png)
#### 주의점
터미널을 껏다가 다시 켰을때
roscd bumperbot_examples를 실행하게 되면 찾지 못한다고 나온다.

프로젝트를 실행할때 마다 패키지(bumperbot_examples)가 든 워크스페이스(bumperbot_ws) 에 찾아 가야한다.

![](https://velog.velcdn.com/images/smile_b/post/df1f6237-c819-4b15-acdc-e64dddb527b7/image.png)

터미널을 다시 실행시켰을 때 보면, roscd 명령어가 동작하지 않는다.