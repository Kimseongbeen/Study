
# ROS Launch 파일을 사용한 로봇 모델 시각화

이 실습에서는 ROS launch 파일을 사용하여 로봇의 URDF 모델을 RViz에서 시각화하는 과정을 설명합니다.

## Launch 파일 생성

1. `bumperbot_description` 패키지 내에 `launch` 폴더를 생성합니다.
2. `launch` 폴더 안에 `display.launch` 파일을 생성하고 다음 내용을 추가합니다:

```xml
<launch>
    <!-- URDF 모델을 파라미터 서버에 로드 -->
    <rosparam param="robot_description" file="$(find bumperbot_description)/urdf/bumperbot.urdf" command="load"/>

    <!-- 로봇 상태 퍼블리셔 노드 실행 -->
    <node pkg="robot_state_publisher" type="robot_state_publisher" name="robot_state_publisher"/>

    <!-- 조인트 상태 퍼블리셔 GUI 노드 실행 -->
    <node pkg="joint_state_publisher_gui" type="joint_state_publisher_gui" name="joint_state_publisher_gui"/>

    <!-- RViz 실행 및 설정 파일 로드 -->
    <node pkg="rviz" type="rviz" name="rviz" args="-d $(find bumperbot_description)/rviz/display.rviz"/>
</launch>
```
## Launch 파일 실행

터미널에서 다음 명령어를 실행합니다:

```bash
cd bumperbot_ws/              # 작업 공간으로 이동
source devel/setup.bash       # 환경 설정
roslaunch bumperbot_description display.launch  # launch 파일 실행
```

## 주요 특징 및 이점

1. **단일 명령어 실행**: 여러 터미널과 명령어 대신 하나의 명령어로 모든 것을 시작할 수 있습니다.

2. **roscore 자동 실행**: `roslaunch` 명령어는 자동으로 `roscore`를 실행하므로, 별도로 `roscore`를 실행할 필요가 없습니다.

3. **파라미터 로드**: `rosparam` 태그를 사용하여 URDF 모델을 파라미터 서버에 자동으로 로드합니다.

4. **노드 자동 실행**: `robot_state_publisher`, `joint_state_publisher_gui`, `rviz` 등의 노드가 자동으로 실행됩니다.

5. **RViz 설정 자동 로드**: -d 옵션: 설정 파일을 지정합니다.
$(find bumperbot_description): bumperbot_description 패키지의 경로를 찾습니다.
/rviz/display.rviz: 패키지 내의 RViz 설정 파일 경로입니다.

이 설정을 통해 RViz가 시작될 때 자동으로 저장된 설정(로봇 모델 표시, 프레임 등)을 로드하므로, 매번 수동으로 설정할 필요가 없습니다.

6. **재사용성**: Launch 파일을 사용하면 복잡한 설정을 쉽게 재현하고 공유할 수 있습니다.

## 주의사항

- Launch 파일 내의 노드 실행 순서는 파일에 나열된 순서와 정확히 일치하지 않을 수 있습니다.
- 노드들은 실행 순서에 관계없이 올바르게 작동하도록 설계되어야 합니다.

이 방법을 사용하면 로봇 모델 시각화 과정이 크게 간소화되며, 한 번의 명령으로 모든 필요한 구성 요소를 시작할 수 있습니다.
