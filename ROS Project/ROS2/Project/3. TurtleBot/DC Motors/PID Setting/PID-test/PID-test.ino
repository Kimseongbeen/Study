#include <PID_v1.h>

// L298N H-브릿지 연결 핀
#define L298N_enA 9  // PWM
#define L298N_in2 13  // 모터 A 방향
#define L298N_in1 12  // 모터 A 방향
#define right_encoder_phaseA 3  // 인터럽트 
#define right_encoder_phaseB 5  

// 엔코더 및 기어비 상수
const double encoderPPR = 823.1;  // 회전당 펄스 수
const double gearRatio = 75.0;    // 1:75 기어비

// 엔코더 변수
volatile unsigned int right_encoder_counter = 0;
String right_encoder_sign = "p";  // 'p' = 양수, 'n' = 음수

// PID 변수
double setpoint, input, output;
double Kp = 10, Ki = 5, Kd = 0.1;  // 초기 PID 값

PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

unsigned long lastTime = 0;
const long interval = 100;  // 100ms 간격으로 속도 계산 및 PID 제어

void setup() {
  pinMode(L298N_enA, OUTPUT);
  pinMode(L298N_in1, OUTPUT);
  pinMode(L298N_in2, OUTPUT);
  
  digitalWrite(L298N_in1, HIGH);
  digitalWrite(L298N_in2, LOW);
  
  Serial.begin(115200);
  
  pinMode(right_encoder_phaseB, INPUT);
  attachInterrupt(digitalPinToInterrupt(right_encoder_phaseA), rightEncoderCallback, RISING);

  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(interval);
  myPID.SetOutputLimits(0, 255);  // PWM 출력 범위

  setpoint = 2.0;  // 목표 속도 (rad/s)
}

void loop() {
  unsigned long currentTime = millis();
  
  if (currentTime - lastTime >= interval) {
    // 속도 계산 (rad/s)
    double rpm = (right_encoder_counter * 60.0 * 1000) / (encoderPPR * gearRatio * interval);
    input = rpm * 0.10472;  // RPM to rad/s

    myPID.Compute();  // PID 계산

    analogWrite(L298N_enA, output);  // 모터 속도 제어
    
    // 결과 출력
    Serial.print("Setpoint: ");
    Serial.print(setpoint);
    Serial.print(" Input: ");
    Serial.print(input);
    Serial.print(" Output: ");
    Serial.println(output);

    // 엔코더 카운터 리셋
    right_encoder_counter = 0;
    lastTime = currentTime;
  }

  // PID 값 조정을 위한 시리얼 입력 처리
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    if (command.startsWith("P")) {
      Kp = command.substring(1).toFloat();
    } else if (command.startsWith("I")) {
      Ki = command.substring(1).toFloat();
    } else if (command.startsWith("D")) {
      Kd = command.substring(1).toFloat();
    } else if (command.startsWith("S")) {
      setpoint = command.substring(1).toFloat();
    }
    myPID.SetTunings(Kp, Ki, Kd);
    Serial.print("New PID values - Kp: ");
    Serial.print(Kp);
    Serial.print(" Ki: ");
    Serial.print(Ki);
    Serial.print(" Kd: ");
    Serial.println(Kd);
  }
}

void rightEncoderCallback() {
  if(digitalRead(right_encoder_phaseB) == HIGH) {
    right_encoder_sign = "p";
  } else {
    right_encoder_sign = "n";
  }
  right_encoder_counter++;
}