# DC 모터 ROS2 제어 프로젝트

이 프로젝트는 ROS2와 Arduino를 사용하여 DC 모터를 양방향으로 제어하는 시스템을 구현합니다.
![](https://velog.velcdn.com/images/smile_b/post/36bbf596-d817-4912-8ebc-84a5ae86bcb0/image.png)
## 하드웨어 구성

- Arduino (예: Arduino Uno)
- L298N H-브릿지 모터 드라이버
- DC 모터 (12V)
- 전원 공급 장치 (11.1V 배터리)

## 회로 연결

1. L298N H-브릿지:
   - ENA: Arduino 9번 핀 (PWM)
   - IN1: Arduino 12번 핀
   - IN2: Arduino 13번 핀
   - 모터 출력: DC 모터에 연결
   - 전원 입력: 11.1V 배터리

2. Arduino:
   - USB 케이블로 컴퓨터에 연결

## 소프트웨어 설정

### Arduino 코드

Arduino IDE에서 다음 코드를 업로드합니다:

```cpp
// L298N H-브릿지 연결 핀
#define L298N_enA 9  // PWM 제어 핀
#define L298N_in2 13 // 모터 A 방향 제어 핀 2
#define L298N_in1 12 // 모터 A 방향 제어 핀 1

float cmd = 0; // 모터 제어 명령 변수

void setup() {
  // 핀 모드 설정
  pinMode(L298N_enA, OUTPUT);
  pinMode(L298N_in1, OUTPUT);
  pinMode(L298N_in2, OUTPUT);
  
  Serial.begin(115200); // 시리얼 통신 시작 (115200 baud)
}

void loop() {
  if (Serial.available()) {
    cmd = Serial.readString().toFloat(); // 시리얼로부터 명령 읽기
    setMotor(cmd); // 모터 설정 함수 호출
  }
}

void setMotor(float speed) {
  int pwmValue = abs(speed) * 100;  // 0-255 범위로 변환
  pwmValue = constrain(pwmValue, 0, 255);  // PWM 값을 유효한 범위로 제한
  
  if (speed >= 0) {
    // 정방향 회전
    digitalWrite(L298N_in1, HIGH);
    digitalWrite(L298N_in2, LOW);
  } else {
    // 역방향 회전
    digitalWrite(L298N_in1, LOW);
    digitalWrite(L298N_in2, HIGH);
  }
  
  analogWrite(L298N_enA, pwmValue); // PWM으로 모터 속도 제어
}
```

### ROS2 설정

1. ROS2 워크스페이스로 이동:
   ```
   cd bumperbot_ws
   ```

2. 환경 설정:
   ```
   . install/setup.bash
   ```

3. 시리얼 통신 노드 실행:
   ```
   ros2 run bumperbot_firmware simple_serial_transmitter --ros-args -p port:=/dev/ttyUSB0
   ```
   (주의: ttyUSB0은 사용자의 시스템에 따라 다를 수 있습니다.)

## 사용 방법

모터 제어를 위해 다음 ROS2 명령어를 사용합니다:

1. 정방향 최대 속도:
   ```
   ros2 topic pub /serial_transmitter std_msgs/msg/String "data: '2.55'"
   ```

2. 정방향 중간 속도:
   ```
   ros2 topic pub /serial_transmitter std_msgs/msg/String "data: '1.275'"
   ```

3. 정지:
   ```
   ros2 topic pub /serial_transmitter std_msgs/msg/String "data: '0.0'"
   ```

4. 역방향 중간 속도:
   ```
   ros2 topic pub /serial_transmitter std_msgs/msg/String "data: '-1.275'"
   ```

5. 역방향 최대 속도:
   ```
   ros2 topic pub /serial_transmitter std_msgs/msg/String "data: '-2.55'"
   ```

## 주의사항

- 모터 제어 명령은 -2.55에서 2.55 사이의 값을 사용합니다.
- 양수 값은 정방향, 음수 값은 역방향 회전을 의미합니다.
- 절대값이 클수록 모터의 회전 속도가 빨라집니다.

## 문제 해결

- 모터가 동작하지 않을 경우:
  1. 모든 연결을 확인하세요.
  2. 배터리 전압을 확인하세요.
  3. Arduino 코드가 성공적으로 업로드되었는지 확인하세요.
  4. ROS2 노드가 올바른 시리얼 포트를 사용하고 있는지 확인하세요.

- 예상치 못한 동작이 발생할 경우:
  1. H-브릿지의 연결을 다시 확인하세요.
  2. 입력 명령의 범위가 올바른지 확인하세요.

## 추가 개발 아이디어

- 엔코더를 추가하여 모터의 실제 속도를 측정하고 피드백 제어를 구현할 수 있습니다.
- 여러 모터를 제어하여 차동 구동 로봇을 만들 수 있습니다.
- PID 제어를 구현하여 더 정밀한 속도 제어를 할 수 있습니다.