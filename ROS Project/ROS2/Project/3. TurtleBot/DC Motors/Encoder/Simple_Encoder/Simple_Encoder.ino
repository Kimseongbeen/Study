// L298N H-브릿지 연결 핀
#define L298N_enA 9  // PWM
#define L298N_in2 13  // 모터 A 방향
#define L298N_in1 12  // 모터 A 방향
#define right_encoder_phaseA 3  // 인터럽트 
#define right_encoder_phaseB 5  

// 엔코더 및 기어비 상수
const double encoderPPR = 823.1;  // 회전당 펄스 수
const double gearRatio = 75.0;    // 1:75 기어비

unsigned int right_encoder_counter = 0;
String right_encoder_sign = "p";  // 'p' = 양수, 'n' = 음수
double right_wheel_meas_vel = 0.0;    // rad/s

void setup() {
  // 핀 모드 설정
  pinMode(L298N_enA, OUTPUT);
  pinMode(L298N_in1, OUTPUT);
  pinMode(L298N_in2, OUTPUT);
  
  // 모터 회전 방향 설정
  digitalWrite(L298N_in1, HIGH);
  digitalWrite(L298N_in2, LOW);
  
  Serial.begin(115200);
  
  pinMode(right_encoder_phaseB, INPUT);
  attachInterrupt(digitalPinToInterrupt(right_encoder_phaseA), rightEncoderCallback, RISING);
}

void loop() {
  // RPM 계산
  double right_rpm = (right_encoder_counter * 60.0) / (encoderPPR * gearRatio);
  
  // 라디안/초로 변환
  right_wheel_meas_vel = right_rpm * 0.10472;
  
  String encoder_read = "r" + right_encoder_sign + String(right_wheel_meas_vel);
  Serial.println(encoder_read);
  
  right_encoder_counter = 0;
  
  analogWrite(L298N_enA, 100);
  delay(100);
}

// 오른쪽 휠 엔코더의 새 펄스
void rightEncoderCallback()
{
  if(digitalRead(right_encoder_phaseB) == HIGH)
  {
    right_encoder_sign = "p";
  }
  else
  {
    right_encoder_sign = "n";
  }
  right_encoder_counter++;
}