# URDF와 Bumperbot 로봇 설명

## URDF (Unified Robot Description Format)

URDF는 로봇의 구조를 설명하기 위한 XML 기반의 파일 형식입니다.

### URDF의 주요 특징

1. **목적**: 
   - 로봇의 물리적 구조를 컴퓨터가 이해할 수 있는 형태로 표현
   - 시뮬레이션, 시각화, 제어 등에 사용

2. **주요 구성 요소**:
   - 링크(Link): 로봇의 각 부분 (예: 팔, 다리, 몸체)
   - 조인트(Joint): 링크들 사이의 연결과 움직임

3. **특징**:
   - XML 형식 사용
   - 3D 모델 파일(STL, DAE 등)과 연동 가능
   - 물리적 속성(질량, 관성 등) 포함 가능

4. **사용 분야**:
   - ROS(Robot Operating System)
   - 로봇 시뮬레이션
   - 운동학 및 동역학 계산

5. **장점**:
   - 표준화된 형식으로 호환성 제공
   - 복잡한 로봇 구조도 쉽게 기술 가능

## Bumperbot 로봇 URDF 설명

Bumperbot은 두 개의 구동 바퀴와 두 개의 캐스터 휠을 가진 이동 로봇입니다.

### 로봇 구조 요약

1. **base_footprint**: 로봇의 기준점
2. **base_link**: 로봇의 주 본체
3. **wheel_right_link**: 오른쪽 바퀴
4. **wheel_left_link**: 왼쪽 바퀴
5. **caster_front_link**: 전방 캐스터 휠
6. **caster_rear_link**: 후방 캐스터 휠

### 조인트 구조

- **base_joint**: base_footprint와 base_link 연결 (고정)
- **wheel_right_joint**: base_link와 오른쪽 바퀴 연결 (연속 회전)
- **wheel_left_joint**: base_link와 왼쪽 바퀴 연결 (연속 회전)
- **caster_front_joint**: base_link와 전방 캐스터 연결 (고정)
- **caster_rear_joint**: base_link와 후방 캐스터 연결 (고정)

### 주요 특징

- STL 파일을 사용하여 각 부품의 3D 모델을 정의
- 바퀴는 연속 회전 조인트를 사용하여 자유로운 회전 가능
- 캐스터 휠은 고정 조인트를 사용하여 본체에 부착
- 각 링크와 조인트의 위치와 방향이 정확히 지정되어 있음

### 코드 구조

1. 로봇 정의 시작 (`<robot>` 태그)
2. 각 링크 정의 (`<link>` 태그)
   - 시각적 요소 포함 (`<visual>` 태그)
   - 3D 모델 파일 지정 (`<mesh>` 태그)
3. 조인트 정의 (`<joint>` 태그)
   - 부모 링크와 자식 링크 지정
   - 조인트 유형 및 축 지정
4. 로봇 정의 종료

이 URDF 파일은 Bumperbot의 전체 구조를 상세히 설명하고 있어, 시뮬레이션이나 실제 로봇 제어에 활용할 수 있습니다.