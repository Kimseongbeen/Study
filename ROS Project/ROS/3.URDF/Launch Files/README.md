
# ROS Launch 파일을 사용한 로봇 모델 시각화 (~2024-07-17)

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

# 시뮬레이션 런치 파일 (2024-07-18~)

BumperBot 로봇의 Gazebo 시뮬레이션을 실행하기 위한 단계:

1. 워크스페이스로 이동:
   ```
   cd bumperbot_ws
   ```

2. 워크스페이스 설정 파일 소스:
   ```
   source devel/setup.bash
   ```

3. Gazebo 시뮬레이션 런치:
   ```
   roslaunch bumperbot_description gazebo.launch
   ```

실행 시 출력되는 `model` 및 `world` 관련 정보:
- 이는 `gazebo.launch` 파일에서 정의된 두 개의 인자(argument) 때문입니다.
- `model`: 시뮬레이션에 사용될 로봇 모델 파일을 지정합니다.
- `world`: Gazebo 시뮬레이션 환경(월드)을 지정합니다.

이 런치 파일은 다음 작업을 수행합니다:
1. XACRO 파일을 URDF로 변환하여 로봇 모델을 로드합니다.
2. Gazebo 시뮬레이터를 시작합니다.
3. 지정된 월드(기본값: empty_world)에서 시뮬레이션을 시작합니다.
4. 로봇 모델을 Gazebo 환경에 스폰(생성)합니다.

이 과정을 통해 빈 Gazebo 환경에 BumperBot 로봇 모델이 나타나며, 시뮬레이션이 시작됩니다. 이 시뮬레이션 환경은 향후 로봇의 새로운 기능과 패키지를 테스트하는 데 중요한 도구로 사용될 것입니다.