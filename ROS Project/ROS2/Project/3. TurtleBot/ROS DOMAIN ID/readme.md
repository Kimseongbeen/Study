# ROS 2 도메인 설정 및 통신 가이드

이 가이드는 ROS 2의 도메인 개념을 설명하고, 라즈베리 파이와 가상 우분투 환경 간의 통신 설정 과정을 단계별로 안내합니다.

## 1. 기본 통신 설정

### 라즈베리 파이에서:
```bash
ssh raspberry@test
```
- 라즈베리 파이에 SSH로 접속합니다.

```bash
ros2 topic pub /test std_msgs/msg/String "data: 'Hi from raspberry'"
```
- '/test' 토픽에 'Hi from raspberry' 메시지를 발행합니다.

### 가상 우분투에서:
```bash
ros2 topic list
```
- 현재 사용 가능한 토픽 목록을 확인합니다. '/test' 토픽이 보여야 합니다.

```bash
ros2 topic echo /test
```
- '/test' 토픽의 메시지를 구독하여 'Hi from raspberry' 메시지를 확인합니다.

## 2. 도메인 설정

요청하신 대로 DDS 설치 및 설정, 그리고 DOMAIN 추가 및 제거 부분을 포함하여 가이드를 수정하겠습니다.

# ROS 2 도메인 설정 및 통신 가이드

## 1. DDS 설치 및 설정

ROS 2는 기본적으로 Fast-RTPS(FastDDS)를 사용하지만, 다른 DDS 구현을 사용할 수도 있습니다. 여기서는 Cyclone DDS를 예로 들어 설명하겠습니다.

### Cyclone DDS 설치:
```bash
sudo apt update
sudo apt install ros-humble-rmw-cyclonedds-cpp
```

### RMW 구현 설정:
```bash
export RMW_IMPLEMENTATION=rmw_cyclonedds_cpp
```

이 설정을 영구적으로 적용하려면 `.bashrc` 파일에 추가하세요:
```bash
echo "export RMW_IMPLEMENTATION=rmw_cyclonedds_cpp" >> ~/.bashrc
source ~/.bashrc
```

## 2. 도메인 설정

### 도메인 ID 추가:
일시적으로 도메인 ID를 설정하려면:
```bash
export ROS_DOMAIN_ID=1
```

영구적으로 설정하려면 `.bashrc` 파일에 추가:
```bash
echo "export ROS_DOMAIN_ID=1" >> ~/.bashrc
source ~/.bashrc
```

### 도메인 ID 제거:
현재 세션에서 도메인 ID 설정을 제거하려면:
```bash
unset ROS_DOMAIN_ID
```

`.bashrc` 파일에서 영구적으로 제거하려면:
```bash
sed -i '/export ROS_DOMAIN_ID/d' ~/.bashrc
source ~/.bashrc
```

## 3. 기본 통신 설정

### 라즈베리 파이에서:
```bash
ssh raspberry@test
ros2 topic pub /test std_msgs/msg/String "data: 'Hi from raspberry'"
```

### 가상 우분투에서:
```bash
ros2 topic list
ros2 topic echo /test
```

## 4. 도메인 간 통신

### 가상 우분투에서:
```bash
ros2 topic list
export ROS_DOMAIN_ID=2
ros2 topic list
ros2 topic echo /test
```

### 라즈베리 파이에서:
```bash
export ROS_DOMAIN_ID=2
ros2 topic pub /test std_msgs/msg/String "data: 'Hi from raspberry'"
```

## 5. 새 터미널에서의 도메인 설정

### 새 터미널에서:
```bash
ros2 topic list
export ROS_DOMAIN_ID=2
ros2 topic list
```

## 주의사항
- ROS_DOMAIN_ID 설정은 서로 다른 ROS 2 시스템 간의 통신을 제어합니다.
- 같은 도메인 ID를 가진 노드들만 서로 통신할 수 있습니다.
- 기본적으로 새 터미널을 열 때마다 ROS_DOMAIN_ID를 다시 설정해야 합니다 (`.bashrc`에 추가하지 않은 경우).
- RMW 구현을 변경할 때는 모든 ROS 2 노드를 재시작해야 합니다.
- 도메인 ID를 변경한 후에는 ROS 2 데몬을 재시작하는 것이 좋습니다: `ros2 daemon stop && ros2 daemon start`

이 가이드는 DDS 설치 및 설정, 도메인 ID 추가 및 제거 방법을 포함하여 업데이트되었습니다. ROS 2의 도메인 개념과 그 사용 이유에 대한 설명은 이전과 동일하게 유지됩니다.