# ROS 2 Humble 설치 가이드

https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debians.html

ROS 2 Humble은 2027년까지 지원되는 현재의 장기 지원 버전(LTS)입니다. 이 가이드는 설치 과정과 각 단계의 목적을 설명합니다.

## 사전 요구사항

- Ubuntu 22.04 (Jammy Jellyfish)

Ubuntu 버전 확인 방법:
```
lsb_release -a
```
목적: ROS 2 Humble은 Ubuntu 22.04와 호환되므로, 올바른 운영 체제 버전을 사용하고 있는지 확인합니다.

## 설치 단계

1. 로케일 설정:

```bash
locale  # UTF-8 확인

sudo apt update && sudo apt install locales
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8

locale  # 설정 확인
```
목적: 시스템의 언어 및 지역 설정을 영어(미국)로 설정합니다. 이는 ROS 2가 예상대로 작동하고 오류 메시지를 올바르게 표시하도록 보장합니다.

```bash
sudo apt install software-properties-common
sudo add-apt-repository universe
```


```bash
sudo apt update && sudo apt install curl -y
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
```

```bash
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
```

```bash
sudo apt update
sudo apt upgrade
```

2. ROS 2 Humble Desktop (전체 버전) 설치:

```bash
sudo apt install ros-humble-desktop
```
목적: ROS 2 Humble의 모든 핵심 패키지, 시뮬레이터, 데모, 튜토리얼을 설치합니다. 이는 Gazebo 시뮬레이터도 포함합니다.

주의: 패키지를 찾을 수 없다는 오류가 발생하면 Ubuntu 22.04를 사용 중인지 다시 확인하세요.

3. ROS 2 설정 파일 소스:

```bash
source /opt/ros/humble/setup.bash
```
목적: ROS 2 환경 변수를 현재 터미널 세션에 로드합니다. 이를 통해 시스템이 ROS 2 명령어와 패키지를 인식할 수 있게 됩니다.

4. 설치 테스트:

```bash
ros2
```
목적: ROS 2가 올바르게 설치되고 환경 변수가 제대로 설정되었는지 확인합니다.

5. .bashrc 파일에 소스 명령 추가:

bashrc 여는 법

A. 파일관리자에서 Ctrl + H 를 눌러서 .bashrc 파일 열기

B. .bashrc 파일 열기:
```bash
nano ~/.bashrc
```

파일 끝에 다음 줄 추가:
```bash
source /opt/ros/humble/setup.bash
```

파일을 저장하고 닫습니다. 그 다음 터미널을 재시작하거나 다음 명령어를 실행하세요:
```bash
source ~/.bashrc
```
목적: 새로운 터미널 세션을 열 때마다 자동으로 ROS 2 환경을 설정합니다. 이로 인해 매번 수동으로 소스 명령을 실행할 필요가 없어집니다.

## 확인

새 터미널을 열고 다음을 실행하세요:
```bash
ros2
```
목적: ROS 2가 모든 새 터미널 세션에서 자동으로 인식되는지 확인합니다.

## 추가 정보

- 전체 설치 가이드: https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debians.html
- ROS 버전은 특정 Ubuntu 버전과 연결되어 있습니다. 설치 전 호환성을 꼭 확인하세요.
- `ros-humble-desktop` 패키지는 개발에 필요한 대부분의 도구와 라이브러리를 포함하는 완전한 설치를 제공합니다.

# ROS 2 Humble 워크스페이스 및 패키지 설정 가이드

이 가이드는 ROS 2 Humble에서 워크스페이스를 생성하고 패키지를 설정하는 과정을 안내합니다.

## 워크스페이스 생성

1. 워크스페이스 디렉토리 생성:
   ```bash
   mkdir -p ~/smileb_ws/src
   ```
   `-p` 옵션은 필요한 경우 상위 디렉토리도 함께 생성합니다.

2. 워크스페이스로 이동:
   ```bash
   cd ~/smileb_ws
   ```

3. ROS 2 설치 확인:
   ```bash
   colcon build
   ```
   이 명령어로 워크스페이스가 생성되고 ROS 2가 올바르게 설치되었는지 확인합니다.

## 패키지 생성

1. src 디렉토리로 이동:
   ```bash
   cd src
   ```

2. 새 패키지 생성:
   ```bash
   ros2 pkg create --build-type ament_python robotic_arms_control
   ```
   이 명령어는 'robotic_arms_control'이라는 이름의 Python 패키지를 생성합니다.

3. VS Code로 패키지 열기:
   워크스페이스의 src 디렉토리에서 VS Code를 열어 패키지 파일을 쉽게 조작할 수 있습니다.

4. 패키지 빌드 확인:
   ```bash
   cd ~/smileb_ws
   colcon build
   ```
   새로 생성된 패키지를 빌드하여 모든 것이 정상적으로 작동하는지 확인합니다.

## 빌드 및 소싱 프로세스 간소화

1. .bashrc 파일 열기:
   ```bash
   nano ~/.bashrc
   ```
   또는 파일 관리자에서 Ctrl+H를 눌러 숨김 파일을 표시한 후 .bashrc 파일을 엽니다.

2. 다음 별칭(alias)을 .bashrc 파일 끝에 추가:
   ```bash
   alias cbs="colcon build && source install/setup.bash"
   alias sws="source install/setup.bash"
   alias cb="colcon build"
   ```

3. 변경사항 적용:
   .bashrc 파일을 저장하고 닫은 후, 새 터미널을 열거나 다음 명령어를 실행합니다:
   ```bash
   source ~/.bashrc
   ```

## 별칭 사용법

- `cbs`: 워크스페이스를 빌드하고 소스합니다.
- `sws`: 워크스페이스를 소스합니다.
- `cb`: 워크스페이스를 빌드합니다.

이제 `cbs` 명령어를 사용하여 워크스페이스를 빌드하고 소스할 수 있습니다. 이후 `ros2 run robotic_arms_control` 명령어를 사용하면 패키지가 자동으로 인식됩니다.

## 주의사항

- 여러 워크스페이스가 있는 경우, 각 워크스페이스를 개별적으로 소스해야 합니다.
- 이러한 별칭 설정은 여러 개발 환경에서 작업할 때 매우 유용합니다.
