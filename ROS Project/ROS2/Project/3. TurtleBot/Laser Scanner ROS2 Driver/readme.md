# RPLiDAR 설정 가이드

## 설치

ROS 2 Humble RPLiDAR 패키지 설치:

```bash
sudo apt-get install ros-humble-rplidar-ros
```

## USB 포트 확인

RPLiDAR의 USB 장치 확인:

```bash
ls /dev | grep ttyUSB
```

## RPLiDAR 노드 실행

RPLiDAR 노드 시작 (필요시 시리얼 포트 조정):

```bash
ros2 launch rplidar_ros rplidar_a1_launch.py serial_port:=/dev/ttyUSB0
```

## 토픽 생성 확인

`/scan` 토픽이 생성되었는지 확인:

```bash
ros2 topic list
```

## 토픽 데이터 검사

`/scan` 토픽에 발행되는 데이터 확인:

```bash
ros2 topic echo /scan
```

## RViz2로 시각화

1. RViz2 실행:
   ```bash
   rviz2
   ```

2. RViz2 설정:
   - 프레임을 `laser`로 변경
   - LaserScan 디스플레이 추가
   - 가시성 향상을 위해 크기를 0.1에서 0.5로 조정

이제 RViz2에서 RPLiDAR 데이터가 시각화되어 표시됩니다.