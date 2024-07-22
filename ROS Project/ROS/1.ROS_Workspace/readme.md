# ROS 워크스페이스 생성 가이드

이 가이드는 ROS 워크스페이스를 만들고 초기화하는 과정을 설명합니다.

## 1. 워크스페이스 생성

```bash
mkdir bumperbot_ws
cd bumperbot_ws
```

![](https://velog.velcdn.com/images/smile_b/post/ef6699cb-9729-4d64-9f3c-76919c0a2039/image.png)

## 2. src 폴더 생성

```bash
mkdir src
```

![](https://velog.velcdn.com/images/smile_b/post/ba95a8a5-64c2-4e7a-a84d-04922fd2cb69/image.png)

## 3. 워크스페이스 초기화

ROS 오버레이를 생성하여 모든 ROS 패키지와 새로 개발할 패키지에 접근할 수 있게 합니다.

```bash
catkin_make
```

![](https://velog.velcdn.com/images/smile_b/post/6f04b0da-9403-4dda-ab26-cc32a1ff3e9d/image.png)

## 4. ROS 패키지 생성

```bash
catkin_create_pkg bumperbot_examples roscpp rospy std_msgs
```

![](https://velog.velcdn.com/images/smile_b/post/2b48a9b8-35e6-46d7-b6c5-2a2f71b8054a/image.png)

## 5. 워크스페이스 재구축 및 활성화

새로 생성한 패키지를 포함하여 워크스페이스를 다시 구축하고 활성화해야 합니다. 이 과정은 반드시 워크스페이스의 최상위 디렉토리(bumperbot_ws)에서 실행해야 합니다.

```bash
cd ~/bumperbot_ws
catkin_make
source devel/setup.bash
```

![](https://velog.velcdn.com/images/smile_b/post/eb58e666-8514-42a2-9339-74ee0e242255/image.png)

'source devel/setup.bash' 명령은 현재 터미널 세션에서만 유효합니다. 새 터미널을 열 때마다 이 명령을 실행해야 해줘야합니다.

주의할 점은, 새 터미널 세션을 시작할 때마다 워크스페이스를 다시 활성화해야 한다는 것입니다. 'source devel/setup.bash' 명령을 실행해야 roscd 등의 ROS 명령어를 사용할 수 있습니다.

![](https://velog.velcdn.com/images/smile_b/post/f83c29da-69f7-403a-a077-7b0db04a46c1/image.png)
워크스페이스 활성화를 종료하려면, 단순히 터미널을 닫거나 새로운 터미널 세션을 시작하면 됩니다.

![](https://velog.velcdn.com/images/smile_b/post/15f77d06-bda1-48c6-b6cd-fec0878e7af1/image.png)

## 6. ROS 패키지 접근 확인

워크스페이스가 정상적으로 활성화되면 다음 명령어로 패키지 디렉토리로 이동할 수 있습니다.

```bash
roscd bumperbot_examples
```

![](https://velog.velcdn.com/images/smile_b/post/7708cf22-cb4c-4bbd-9917-622664693140/image.png)

## 주의사항

- 새 터미널 세션을 시작할 때마다 워크스페이스를 다시 활성화해야 합니다.
- 터미널을 새로 열 때마다 워크스페이스 디렉토리로 이동하고 `source devel/setup.bash` 명령을 실행해야 `roscd` 등의 ROS 명령어를 사용할 수 있습니다.

![](https://velog.velcdn.com/images/smile_b/post/df1f6237-c819-4b15-acdc-e64dddb527b7/image.png)

이 과정을 따라하면 ROS 워크스페이스를 성공적으로 설정하고 사용할 수 있습니다.

# 개발 환경 세팅

## VSCode 다운로드 및 설치
1. [Visual Studio Code](https://code.visualstudio.com/)를 다운로드합니다.

## Extension(확장) 설치
- C++
- Python
- CMake
- CMake Tools
- XML Tools
- ROS

## 터미네이터 설치
1. App Store를 엽니다.
2. 'terminator (터미네이터)'를 검색하여 설치합니다.