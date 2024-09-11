# 라즈베리 파이 ROS 2 설치 및 프로젝트 설정 가이드

이 가이드는 라즈베리 파이에 ROS 2 Humble을 설치하고, PC에서 개발한 프로젝트를 라즈베리 파이로 옮겨 빌드하는 과정을 설명합니다.

## 1. SSH 연결

먼저 라즈베리 파이에 SSH로 연결합니다:
나와있는 test는 https://www.youtube.com/watch?v=foqVHERvxpc 에서 
sudo nano /etc/hosts 에서 설정했던 test입니다.

```bash
ssh raspberry@test
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

echo "source /opt/ros/humble/setup.bash" >> .bashrc
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
sudo apt install --only-upgrade linux-raspi
sudo reboot

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



# Pub/Sub Node with Arduino

ROS2와 Arduino를 사용하여 LED를 제어하는 시스템입니다.

## 설정 및 실행

1. 워크스페이스로 이동하고 설정 스크립트를 소스합니다:

   ```bash
   cd bumperbot_ws
   source install/setup.bash
   ```

2. 시리얼 통신 노드를 실행합니다:
   ```bash
   ros2 run bumperbot_firmware simple_serial_transmitter --ros-args -p port:=/dev/ttyUSB0
   
   ros2 run bumperbot_firmware simple_serial_receiver --ros-args -p port:=/dev/ttyUSB0   
   ```
   주의: `/dev/ttyUSB0`는 사용자의 시스템에 따라 다를 수 있습니다. 실제 Arduino가 연결된 포트로 변경하세요.

## 사용법

1. 사용 가능한 토픽 확인:
   ```bash
   ros2 topic list
   ```
   `/serial_transmitter` 토픽이 목록에 표시되어야 합니다. OR
   `/serial_receiver` 

2. LED 켜기:
   LED를 켜려면 '0'이 아닌 값을 보냅니다.
   ```bash
   ros2 topic pub /serial_transmitter std_msgs/msg/String "data: '1'"
   ```

3. LED 끄기:
   LED를 끄려면 '0' 값을 보냅니다.
   ```bash
   ros2 topic pub /serial_transmitter std_msgs/msg/String "data: '0'"
   ```

## 주의사항

- Arduino 코드가 올바르게 업로드되어 있는지 확인하세요.
- 시리얼 포트 설정(예: /dev/ttyUSB0)이 올바른지 확인하세요.
- ROS2 환경이 제대로 설정되어 있는지 확인하세요.

```

이 README는 사용자가 프로젝트를 쉽게 설정하고 실행할 수 있도록 필요한 모든 단계를 제공합니다. 프로젝트의 구조나 의존성 등 추가적인 정보가 있다면 README에 포함시키는 것이 좋습니다.