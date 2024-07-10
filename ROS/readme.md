# ROS Noetic 설치 가이드 (Ubuntu 20.04)

이 가이드는 Ubuntu 20.04 환경에서 ROS Noetic을 설치하는 방법을 안내합니다. 자세한 정보는 [공식 ROS 위키](https://wiki.ros.org/noetic/Installation/Ubuntu)를 참조하세요.

## 1. 소스 리스트 설정

packages.ros.org에서 소프트웨어를 받아들이도록 시스템을 설정합니다.

```bash
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
```

## 2. 키 설정

```bash
sudo apt install curl
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
```

## 3. ROS 설치

Desktop-Full Install (권장): 모든 기능과 2D/3D 시뮬레이터, 인식 패키지 포함

```bash
sudo apt update
sudo apt install ros-noetic-desktop-full
```

**참고**: 설치에 약 10분 이상 소요될 수 있습니다.

## 4. ROS 환경 변수 설정

```bash
echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

### 설치 확인

다음 명령어로 설치를 확인합니다:

```bash
roscore
```

에러가 발생하지 않으면 정상적으로 설치된 것입니다. 종료하려면 `Ctrl + C`를 누르세요.

## 5. 추가 라이브러리 설치

```bash
sudo apt install python3-rosdep python3-rosinstall python3-rosinstall-generator python3-wstool build-essential
sudo rosdep init
rosdep update
```

이 과정을 따라하면 ROS Noetic을 성공적으로 설치할 수 있습니다.