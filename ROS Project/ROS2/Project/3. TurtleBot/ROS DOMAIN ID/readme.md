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

## ROS 2에서 이러한 도메인 방식을 사용하는 이유와 환경 변수 설정 설명

1. ROS 2에서 도메인 방식을 사용하는 이유:

ROS 2에서 도메인 ID를 사용하는 주요 이유는 다음과 같습니다:

a) 네트워크 격리: 여러 ROS 2 시스템이 같은 네트워크에 있을 때, 서로 간섭하지 않도록 합니다.
b) 보안: 승인되지 않은 노드가 시스템에 접근하는 것을 방지합니다.
c) 유연성: 필요에 따라 시스템 간 통신을 쉽게 제어할 수 있습니다.
d) 리소스 관리: 불필요한 데이터 교환을 줄여 네트워크 대역폭을 절약합니다.

2. 환경 변수 설정에 대한 질문:

.bashrc 파일에 ROS_DOMAIN_ID=1을 설정한 후, 터미널에서 export ROS_DOMAIN_ID=2를 실행하면, 현재 터미널 세션에서만 도메인 ID가 2로 변경됩니다. 이는 임시적인 변경이며, 다음과 같이 작동합니다:

a) .bashrc의 설정:
   - 이는 새로운 터미널 세션이 시작될 때마다 적용되는 기본 설정입니다.
   - 모든 새 터미널은 기본적으로 ROS_DOMAIN_ID=1로 시작합니다.

b) export 명령어:
   - 이는 현재 터미널 세션에서만 유효한 임시 설정입니다.
   - 해당 터미널에서만 ROS_DOMAIN_ID가 2로 변경됩니다.
   - 이 터미널을 닫거나 새 터미널을 열면 다시 .bashrc의 설정(ROS_DOMAIN_ID=1)이 적용됩니다.

c) 현재 상황:
   - 가상 우분투: 기본적으로 ROS_DOMAIN_ID=1 (.bashrc 설정)
   - 라즈베리파이: ROS_DOMAIN_ID=2

이 상태에서 가상 우분투의 터미널에서 export ROS_DOMAIN_ID=2를 실행하면:
   - 해당 터미널에서만 일시적으로 라즈베리파이와 같은 도메인(2)에 있게 됩니다.
   - 다른 터미널이나 새로 열린 터미널은 여전히 도메인 1에 있습니다.

이러한 방식은 필요에 따라 유연하게 도메인을 변경할 수 있게 해주며, 동시에 시스템의 기본 설정을 유지할 수 있게 해줍니다. 예를 들어, 특정 작업을 위해 일시적으로 다른 도메인의 노드와 통신해야 할 때 유용합니다.

영구적인 변경을 원한다면 .bashrc 파일을 직접 수정해야 합니다. 이렇게 하면 모든 새로운 터미널 세션에 변경사항이 적용됩니다.