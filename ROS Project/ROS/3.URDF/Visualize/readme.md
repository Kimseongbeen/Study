

# ROS Parameter Server 실습

ROS 파라미터 서버는 변수나 파라미터를 저장하는 데 사용됩니다. 이 실습에서는 코드 작성 없이 터미널과 ROS 명령어만으로 파라미터 서버를 사용해 볼 것입니다.

## 실습 과정

### 1. ROS 마스터 실행
새 터미널을 열고 다음 명령어를 실행합니다. 이 명령어는 ROS 마스터와 함께 파라미터 서버의 인스턴스도 자동으로 시작합니다.
```bash
roscore
```

### 2. 파라미터 서버 조작
새로운 터미널을 열고 다음 명령어들을 차례로 실행해 봅시다.

#### 2.1 파라미터 목록 확인
```bash
rosparam list
```
이 명령어는 현재 파라미터 서버에 저장된 모든 파라미터의 목록을 보여줍니다.

#### 2.2 특정 파라미터 값 확인
```bash
rosparam get /rosdistro
```
이 명령어는 '/rosdistro' 파라미터의 값을 보여줍니다. 이는 현재 사용 중인 ROS 버전을 나타냅니다.

#### 2.3 새 파라미터 설정
```bash
rosparam set /name "smilb"
```
이 명령어는 '/name'이라는 새 파라미터를 생성하고 그 값을 "smilb"로 설정합니다.

#### 2.4 새로 설정한 파라미터 값 확인
```bash
rosparam get /name
```
이 명령어는 방금 설정한 '/name' 파라미터의 값을 확인합니다.

### 3. ROS 마스터 재실행 및 파라미터 초기화 확인

1. 첫 번째 터미널에서 Ctrl+C를 눌러 `roscore`를 종료합니다.
2. 다시 `roscore`를 실행합니다.
3. 두 번째 터미널에서 다음 명령어를 실행합니다:

```bash
rosparam list
```

이제 이전에 설정했던 '/name' 파라미터가 없어지고, 기본 파라미터들만 표시되는 것을 확인할 수 있습니다.

## 결론
이 실습을 통해 ROS 파라미터 서버의 기본적인 사용법과 특성을 배웠습니다. 파라미터 서버는 `roscore`와 함께 생성되고 종료되며, 종료 시 저장된 모든 사용자 정의 파라미터가 삭제된다는 점을 기억하세요.


<hr style="border: 2px solid #4a90e2;">


# Visualize the Robot 실습

이 실습에서는 ROS를 사용하여 로봇 모델을 RViz에서 시각화하는 과정을 단계별로 진행합니다.

## 1. ROS 마스터 실행 (A 터미널)

```bash
roscore  # ROS 마스터 실행 및 파라미터 서버 시작
```

## 2. 로봇 모델 로드 및 상태 퍼블리셔 실행 (B 터미널)

```bash
rosparam load bumperbot_ws/src/bumperbot_description/urdf/bumperbot.urdf robot_description  # URDF 파일을 파라미터 서버에 로드
rosparam list  # 파라미터 목록 확인
rosparam get /robot_description  # 로드된 로봇 설명 확인
rosrun robot_state_publisher robot_state_publisher  # 로봇 상태 퍼블리셔 실행
```

## 3. RViz 실행 (C 터미널)

```bash
cd bumperbot_ws/  # 작업 공간으로 이동
source devel/setup.bash  # 환경 설정
rosrun rviz rviz  # RViz 실행
```

## 4. Joint State Publisher GUI 실행 (D 터미널)

```bash
rosrun joint_state_publisher_gui joint_state_publisher_gui  # 관절 상태 퍼블리셔 GUI 실행
```

## 주의사항

- 각 명령어는 별도의 터미널 창에서 실행해야 합니다.
- RViz에서 로봇 모델을 올바르게 표시하려면 추가 설정이 필요할 수 있습니다 (예: Fixed Frame 설정, TF 및 RobotModel 추가 등).
- Joint State Publisher GUI를 실행하면 로봇의 관절을 interactive하게 조작할 수 있는 새 창이 열립니다.

이 실습을 통해 ROS 환경에서 로봇 모델을 시각화하고 상호작용하는 기본적인 과정을 배울 수 있습니다.