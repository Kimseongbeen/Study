
# ROS2 로봇 팔 패키지 만들기

## 1. 패키지 구조 생성

1. 새 ROS2 패키지를 생성합니다.
2. 패키지 내에 다음 디렉토리를 만듭니다:
   - `launch`
   - `urdf`
   - `config`

## 2. URDF 파일 생성

1. `urdf` 디렉토리에 `arms.urdf` 파일을 생성합니다.
2. URDF 파일에 로봇 구조를 정의합니다:
   - arms_guide1.urdf 내용 붙여 넣기
   

## 3. 빌드 및 실행

1. 소스 파일 수정 후 `cbs` 명령어를 실행합니다.
2. `install/robotic_arms_control/share/robotic_arms_control` 내부 내용을 확인합니다.
3. 빌드 후 `config`, `launch`, `urdf` 폴더가 생성되었는지 확인합니다.
4. 다음 명령어로 RViz를 실행합니다:
   ```
   ros2 launch robotic_arms_control rviz_bringup.launch.py
   ```

## 4. RViz 설정

1. Add > TF 추가
2. Add > RobotModel 추가
3. Fixed Frame > "world" 선택
4. TF > Show Names 체크
5. RobotModel > Description Topic > "/robot_description" 선택

## 4-1. 예제

arms_guide2.urdf 파일 넣고 rviz 재실행
0.5 크기의 박스와 

## 5. URDF 구조와 RViz 표현

URDF 파일의 주요 구성요소와 RViz에서의 표현:

1. `base_link`:
   - 검은색 실린더 (길이: 0.05, 반지름: 0.2)
   - RViz에서 로봇의 기초 부분으로 표시됨

2. `link_1`:
   - 파란색 실린더 (길이: 0.5, 반지름: 0.08)
   - 로봇 팔의 첫 번째 부분으로 표시됨

3. `link_2`:
   - 빨간색 실린더 (길이: 0.1, 반지름: 0.08)
   - 로봇 팔의 두 번째 부분, 회전 조인트 역할

4. `link_3`:
   - 회색 실린더 (길이: 0.4, 반지름: 0.05)
   - 로봇 팔의 마지막 부분

5. 조인트:
   - `joint_base`: world와 base_link 연결 (고정)
   - `joint_1`: base_link와 link_1 연결 (연속 회전)
   - `joint_2`: link_1과 link_2 연결 (연속 회전)
   - `joint_3`: link_2와 link_3 연결 (고정)

RViz에서는 이러한 링크들이 지정된 색상과 크기로 표시되며, TF를 통해 각 링크의 위치와 방향을 확인할 수 있습니다.

## 6. 테스트 및 수정

1. URDF 파일 수정 후 다음 명령어로 재빌드 및 실행:
   ```
   cbs && ros2 launch robotic_arms_control rviz_bringup.launch.py
   ```
2. RViz를 "Always on Top"으로 설정하여 변경사항을 쉽게 확인할 수 있습니다.
3. 링크의 크기, 위치, 회전 등을 수정하고 RViz에서 즉시 변경사항을 확인합니다.

### 관계도
```
world
  |
  | (joint_base: fixed)
  |
base_link (검은색 실린더)
  |
  | (joint_1: continuous)
  |
link_1 (파란색 긴 실린더)
  |
  | (joint_2: continuous)
  |
link_2 (빨간색 짧은 실린더)
  |
  | (joint_3: fixed)
  |
link_3 (회색 실린더)
```