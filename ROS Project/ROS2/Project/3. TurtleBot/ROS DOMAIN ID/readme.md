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

### 가상 우분투에서:
```bash
vim .bashrc
```
- .bashrc 파일을 편집하기 위해 엽니다.

```bash
export ROS_DOMAIN_ID=1
```
- .bashrc 파일에 위 줄을 추가하여 ROS_DOMAIN_ID를 1로 설정합니다.

```bash
source .bashrc
```
- 변경된 .bashrc 파일을 적용합니다.

```bash
ros2 topic list
```
- 토픽 목록을 다시 확인합니다. 이제 '/test' 토픽이 보이지 않아야 합니다.

### 라즈베리 파이에서:
```bash
vim .bashrc
```
- 라즈베리 파이의 .bashrc 파일을 편집합니다.

```bash
export ROS_DOMAIN_ID=2
```
- 라즈베리 파이의 ROS_DOMAIN_ID를 2로 설정합니다.

```bash
source .bashrc
```
- 변경된 설정을 적용합니다.

```bash
ros2 topic pub /test std_msgs/msg/String "data: 'Hi from raspberry'"
```
- 다시 메시지를 발행합니다.

## 3. 도메인 간 통신

### 가상 우분투에서:
```bash
ros2 topic list
```
- 토픽 목록을 확인합니다. '/test' 토픽이 보이지 않아야 합니다.

```bash
export ROS_DOMAIN_ID=2
```
- 가상 우분투의 ROS_DOMAIN_ID를 라즈베리 파이와 동일하게 설정합니다.

```bash
ros2 topic list
```
- 다시 토픽 목록을 확인합니다. 이제 '/test' 토픽이 보여야 합니다.

```bash
ros2 topic echo /test
```
- '/test' 토픽의 메시지를 다시 구독하여 확인합니다.

## 4. 새 터미널에서의 도메인 설정

### 새 터미널에서:
```bash
ros2 topic list
```
- 새 터미널에서는 기본 도메인 설정으로 인해 '/test' 토픽이 보이지 않습니다.

```bash
export ROS_DOMAIN_ID=2
```
- ROS_DOMAIN_ID를 2로 설정하여 라즈베리 파이와 같은 도메인으로 변경합니다.

```bash
ros2 topic list
```
- 토픽 목록을 확인합니다. 이제 '/test' 토픽이 보여야 합니다.

## 주의사항
- ROS_DOMAIN_ID 설정은 서로 다른 ROS 2 시스템 간의 통신을 제어합니다.
- 같은 도메인 ID를 가진 노드들만 서로 통신할 수 있습니다.
- 기본적으로 새 터미널을 열 때마다 ROS_DOMAIN_ID를 다시 설정해야 합니다.
- 영구적인 설정을 위해서는 .bashrc 파일에 export 명령어를 추가해야 합니다.

도메인간 통신