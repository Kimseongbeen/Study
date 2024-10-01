// L298N H-브릿지 연결 핀
#define L298N_enA 9  // PWM
#define L298N_in2 13  // 모터 A 방향
#define L298N_in1 12  // 모터 A 방향
#define right_encoder_phaseA 3  // 인터럽트 
#define right_encoder_phaseB 5

// 엔코더 및 기어비 상수
const double encoderPPR = 823.1;  // 회전당 펄스 수
const double gearRatio = 75.0;    // 1:75 기어비

volatile unsigned int right_encoder_counter = 0;
String right_encoder_sign = "p";  // 'p' = 양수, 'n' = 음수
double right_wheel_meas_vel = 0.0;    // rad/s

// 모터 속도 제어 변수
int motorSpeed = 0;  // 초기 모터 속도 (0-255 범위)
bool isForward = true;  // 모터 방향

unsigned long lastTime = 0;
const unsigned long sampleTime = 100;  // 100ms 샘플링 시간

void setup() {
  // 핀 모드 설정
  pinMode(L298N_enA, OUTPUT);
  pinMode(L298N_in1, OUTPUT);
  pinMode(L298N_in2, OUTPUT);
  
  // 초기 모터 방향 설정
  setMotorDirection(true);
  
  Serial.begin(115200);
  
  pinMode(right_encoder_phaseB, INPUT);
  attachInterrupt(digitalPinToInterrupt(right_encoder_phaseA), rightEncoderCallback, RISING);
}

void loop() {
  unsigned long currentTime = millis();
  
  if (currentTime - lastTime >= sampleTime) {
    // RPM 계산
    double right_rpm = (right_encoder_counter * 60.0 * 1000) / (encoderPPR * gearRatio * sampleTime);
    
    // 라디안/초로 변환
    right_wheel_meas_vel = right_rpm * 0.10472;
    
    String encoder_read = "r" + right_encoder_sign + String(right_wheel_meas_vel, 4);  // 4 decimal places
    Serial.println(encoder_read);
    
    right_encoder_counter = 0;
    lastTime = currentTime;
  }
  
  // 모터 속도 제어
  analogWrite(L298N_enA, abs(motorSpeed));

  // 시리얼 입력을 통한 속도 조절
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    int speed = input.toInt();
    if (speed >= -255 && speed <= 255) {
      motorSpeed = speed;
      isForward = (speed >= 0);
      setMotorDirection(isForward);
      Serial.println("Motor speed set to: " + String(motorSpeed));
    }
  }
}

// 오른쪽 휠 엔코더의 새 펄스
void rightEncoderCallback() {
  right_encoder_sign = isForward ? "p" : "n";
  right_encoder_counter++;
}

// 모터 방향 설정 함수
void setMotorDirection(bool forward) {
  digitalWrite(L298N_in1, forward ? HIGH : LOW);
  digitalWrite(L298N_in2, forward ? LOW : HIGH);
}