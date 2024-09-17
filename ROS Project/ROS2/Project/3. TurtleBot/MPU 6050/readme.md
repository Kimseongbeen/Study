# 라즈베리 파이와 RViz2를 이용한 IMU 설정 및 시각화

이 가이드는 MPU6050 IMU 센서를 라즈베리 파이에 설정하고, ROS 2 드라이버를 실행한 후, 다른 컴퓨터에서 RViz2를 사용하여 데이터를 시각화하는 방법을 설명합니다.

## 준비물

- Ubuntu와 ROS 2가 설치된 라즈베리 파이
- Ubuntu와 ROS 2가 설치된 다른 컴퓨터 (RViz2 실행용)
- MPU6050 IMU 센서
- 점퍼 케이블

## 하드웨어 설정

![](https://velog.velcdn.com/images/smile_b/post/499e17e2-00d2-4105-9ece-3e59b4a0d847/image.png)


1. MPU6050을 라즈베리 파이에 연결:
   - VCC를 5V에 연결
   - GND를 GND에 연결
   - SDA를 SDA에 연결
   - SCL을 SCL에 연결

## 라즈베리 파이 설정

1. SSH를 통해 라즈베리 파이에 접속:
   ```
   ssh raspberry@<라즈베리_파이_IP>
   ```

2. 작업 공간 생성 (아직 없는 경우):
   ```
   mkdir -p ~/bumperbot_ws/src
   ```

3. ROS 2 패키지를 라즈베리 파이로 복사:
   ```
   scp -r <src_폴더_경로> raspberry@<라즈베리_파이_IP>:~/bumperbot_ws/
   ```

4. SMBus 라이브러리 설치:
   ```
   pip install smbus
   ```

5. 작업 공간 빌드:
   ```
   cd ~/bumperbot_ws
   colcon build --parallel-workers 2
   ```

6. 작업 공간 소스:
   ```
   . install/setup.bash
   ```

7. IMU 드라이버 실행:
   ```
   ros2 run bumperbot_firmware mpu6050_driver.py
   ```

## 시각화 컴퓨터 설정

1. RViz IMU 플러그인 설치:
   ```
   sudo apt-get install ros-humble-rviz-imu-plugin
   ```

2. ROS_DOMAIN_ID를 라즈베리 파이와 동일하게 설정 (이 경우 2):
   ```
   export ROS_DOMAIN_ID=2
   ```

3. RViz2 실행:
   ```
   rviz2
   ```

4. RViz2에서:
   - Fixed Frame을 "base_footprint"로 설정
   - Add 버튼을 클릭하고 By topic 선택
   - "/imu/out/imu" 선택
   - IMU 플러그인 설정에서 가속도 화살표 표시 활성화

이제 RViz2에서 IMU 데이터가 시각화되어야 하며, 센서의 읽기 값에 따라 가속도 화살표가 움직이는 것을 볼 수 있습니다.

주의: 라즈베리 파이와 시각화 컴퓨터가 동일한 네트워크에 있고 같은 ROS_DOMAIN_ID를 사용하고 있는지 확인하세요. 이는 올바른 통신을 위해 필요합니다.