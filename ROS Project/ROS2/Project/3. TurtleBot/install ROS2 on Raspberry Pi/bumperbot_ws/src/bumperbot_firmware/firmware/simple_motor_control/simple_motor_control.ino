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
  
  // Set Motor Rotation Direction
  digitalWrite(L298N_in1, HIGH);
  digitalWrite(L298N_in2, LOW);

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
