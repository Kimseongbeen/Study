# 라즈베리 파이 ROS 2 설치 및 프로젝트 설정 가이드

이 가이드는 라즈베리 파이에 ROS 2 Humble을 설치하고, PC에서 개발한 프로젝트를 라즈베리 파이로 옮겨 빌드하는 과정을 설명합니다.

## 1. SSH 연결

먼저 라즈베리 파이에 SSH로 연결합니다:

```bash
ssh raspberry@raspberry
```

## 2. ROS 2 Humble 설치

### 로케일 설정

```bash
locale  # UTF-8 확인

sudo apt update && sudo apt install locales
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8
```

이 단계는 시스템 로케일을 UTF-8로 설정하여 문자 인코딩 관련 문제를 방지합니다.

### ROS 2 저장소 추가

```bash
sudo apt install software-properties-common
sudo add-apt-repository universe

sudo apt update && sudo apt install curl -y
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg

echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
```

이 과정은 ROS 2 패키지를 다운로드할 수 있는 저장소를 시스템에 추가합니다.

### ROS 2 설치

```bash
sudo apt update
sudo apt upgrade

sudo apt install ros-humble-desktop
sudo apt install ros-dev-tools

source /opt/ros/humble/setup.bash
```

이 단계에서 ROS 2 Humble과 개발 도구를 설치하고, ROS 2 환경을 활성화합니다.

### 설치 확인

새 터미널을 열고 다시 SSH 연결 후 ROS 2 명령어 실행:

```bash
ssh raspberry@raspberry
ros2
ros2 --help
```

이 과정을 통해 ROS 2가 올바르게 설치되었는지 확인합니다.

## 3. 프로젝트 설정

### 워크스페이스 생성

라즈베리 파이에서:

```bash
mkdir bumperbot_ws
```

### 프로젝트 파일 전송

VMWare(가상환경) 터미널에서:

```bash
scp -r src/ raspberry@raspberry:/home/raspberry/bumperbot_ws
```

이 명령어는 로컬 PC의 프로젝트 파일을 라즈베리 파이로 전송합니다.

### 의존성 설치

라즈베리 파이에서:

```bash
cd bumperbot_ws
sudo rosdep init
rosdep update
rosdep install --from-paths src -y --ignore-src --skip-keys "gazebo_ros gazebo_ros_pkgs gazebo_plugins gazebo_ros2_control"
sudo apt-get install python3-pip
pip install transforms3d
pip install pyserial
```

이 과정은 프로젝트에 필요한 ROS 2 패키지와 Python 라이브러리를 설치합니다.

### 워크스페이스 빌드

```bash
colcon build --parallel-workers 2
```

이 명령어는 프로젝트를 빌드합니다. `--parallel-workers 2` 옵션은 라즈베리 파이의 제한된 리소스를 고려하여 병렬 작업 수를 제한합니다.

## 주의사항

- 라즈베리 파이의 성능을 고려하여 빌드 시간이 PC보다 오래 걸릴 수 있습니다.
- Gazebo 관련 패키지는 그래픽 인터페이스가 없는 라즈베리 파이에서 필요하지 않으므로 설치를 건너뜁니다.
- 문제가 발생할 경우, 로그를 확인하고 필요에 따라 추가 의존성을 설치하세요.

이 가이드를 따라 설정하면 라즈베리 파이에서 ROS 2 프로젝트를 실행할 준비가 완료됩니다.