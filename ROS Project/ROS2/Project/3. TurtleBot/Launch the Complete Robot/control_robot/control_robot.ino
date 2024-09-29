#include <PID_v1.h>

// L298N H-브릿지 연결 핀
#define L298N_enA 9  // PWM
#define L298N_enB 11  // PWM
#define L298N_in4 8  // 모터 B 방향
#define L298N_in3 7  // 모터 B 방향
#define L298N_in2 13  // 모터 A 방향
#define L298N_in1 12  // 모터 A 방향

// 휠 엔코더 연결 핀
#define right_encoder_phaseA 3  // 인터럽트 
#define right_encoder_phaseB 5  
#define left_encoder_phaseA 2   // 인터럽트
#define left_encoder_phaseB 4

// 엔코더
unsigned int right_encoder_counter = 0;
unsigned int left_encoder_counter = 0;
String right_wheel_sign = "p";  // 'p' = 양수, 'n' = 음수
String left_wheel_sign = "p";  // 'p' = 양수, 'n' = 음수
unsigned long last_millis = 0;
const unsigned long interval = 100;

// 엔코더 및 기어비 상수
const double encoderPPR = 823.1;  // 회전당 펄스 수
const double gearRatio = 75.0;    // 1:75 기어비

// 시리얼 메시지 해석
bool is_right_wheel_cmd = false;
bool is_left_wheel_cmd = false;
bool is_right_wheel_forward = true;
bool is_left_wheel_forward = true;
char value[] = "00.00";
uint8_t value_idx = 0;
bool is_cmd_complete = false;

// PID
// 설정값 - 목표
double right_wheel_cmd_vel = 0.0;     // rad/s
double left_wheel_cmd_vel = 0.0;      // rad/s
// 입력 - 측정값
double right_wheel_meas_vel = 0.0;    // rad/s
double left_wheel_meas_vel = 0.0;     // rad/s
// 출력 - 명령
double right_wheel_cmd = 0.0;             // 0-255
double left_wheel_cmd = 0.0;              // 0-255
// 튜닝
double Kp_r = 11.5;
double Ki_r = 7.5;
double Kd_r = 0.1;
double Kp_l = 12.8;
double Ki_l = 8.3;
double Kd_l = 0.1;
// 컨트롤러
PID rightMotor(&right_wheel_meas_vel, &right_wheel_cmd, &right_wheel_cmd_vel, Kp_r, Ki_r, Kd_r, DIRECT);
PID leftMotor(&left_wheel_meas_vel, &left_wheel_cmd, &left_wheel_cmd_vel, Kp_l, Ki_l, Kd_l, DIRECT);

void setup() {
  // L298N H-브릿지 연결 핀 초기화
  pinMode(L298N_enA, OUTPUT);
  pinMode(L298N_enB, OUTPUT);
  pinMode(L298N_in1, OUTPUT);
  pinMode(L298N_in2, OUTPUT);
  pinMode(L298N_in3, OUTPUT);
  pinMode(L298N_in4, OUTPUT);

  // 모터 회전 방향 설정
  digitalWrite(L298N_in1, HIGH);
  digitalWrite(L298N_in2, LOW);
  digitalWrite(L298N_in3, HIGH);
  digitalWrite(L298N_in4, LOW);

  rightMotor.SetMode(AUTOMATIC);
  leftMotor.SetMode(AUTOMATIC);
  Serial.begin(115200);

  // 엔코더 초기화
  pinMode(right_encoder_phaseB, INPUT);
  pinMode(left_encoder_phaseB, INPUT);
  // 휠 엔코더 펄스에 대한 콜백 설정
  attachInterrupt(digitalPinToInterrupt(right_encoder_phaseA), rightEncoderCallback, RISING);
  attachInterrupt(digitalPinToInterrupt(left_encoder_phaseA), leftEncoderCallback, RISING);
}

void loop() {
  // 휠 속도 명령 읽기 및 해석
  if (Serial.available())
  {
    char chr = Serial.read();
    // 오른쪽 휠 모터
    if(chr == 'r')
    {
      is_right_wheel_cmd = true;
      is_left_wheel_cmd = false;
      value_idx = 0;
      is_cmd_complete = false;
    }
    // 왼쪽 휠 모터
    else if(chr == 'l')
    {
      is_right_wheel_cmd = false;
      is_left_wheel_cmd = true;
      value_idx = 0;
    }
    // 양의 방향
    else if(chr == 'p')
    {
      if(is_right_wheel_cmd && !is_right_wheel_forward)
      {
        // 회전 방향 변경
        digitalWrite(L298N_in1, HIGH - digitalRead(L298N_in1));
        digitalWrite(L298N_in2, HIGH - digitalRead(L298N_in2));
        is_right_wheel_forward = true;
      }
      else if(is_left_wheel_cmd && !is_left_wheel_forward)
      {
        // 회전 방향 변경
        digitalWrite(L298N_in3, HIGH - digitalRead(L298N_in3));
        digitalWrite(L298N_in4, HIGH - digitalRead(L298N_in4));
        is_left_wheel_forward = true;
      }
    }
    // 음의 방향
    else if(chr == 'n')
    {
      if(is_right_wheel_cmd && is_right_wheel_forward)
      {
        // 회전 방향 변경
        digitalWrite(L298N_in1, HIGH - digitalRead(L298N_in1));
        digitalWrite(L298N_in2, HIGH - digitalRead(L298N_in2));
        is_right_wheel_forward = false;
      }
      else if(is_left_wheel_cmd && is_left_wheel_forward)
      {
        // 회전 방향 변경
        digitalWrite(L298N_in3, HIGH - digitalRead(L298N_in3));
        digitalWrite(L298N_in4, HIGH - digitalRead(L298N_in4));
        is_left_wheel_forward = false;
      }
    }
    // 구분자
    else if(chr == ',')
    {
      if(is_right_wheel_cmd)
      {
        right_wheel_cmd_vel = atof(value);
      }
      else if(is_left_wheel_cmd)
      {
        left_wheel_cmd_vel = atof(value);
        is_cmd_complete = true;
      }
      // 다음 명령을 위한 초기화
      value_idx = 0;
      value[0] = '0';
      value[1] = '0';
      value[2] = '.';
      value[3] = '0';
      value[4] = '0';
      value[5] = '\0';
    }
    // 명령 값
    else
    {
      if(value_idx < 5)
      {
        value[value_idx] = chr;
        value_idx++;
      }
    }
  }

  // 엔코더
  unsigned long current_millis = millis();
  if(current_millis - last_millis >= interval)
  {
    // RPM 계산
    double right_rpm = (right_encoder_counter * 60.0) / (encoderPPR * gearRatio);
    double left_rpm = (left_encoder_counter * 60.0) / (encoderPPR * gearRatio);

    // 라디안/초로 변환
    right_wheel_meas_vel = right_rpm * 0.10472;
    left_wheel_meas_vel = left_rpm * 0.10472;
    
    rightMotor.Compute();
    leftMotor.Compute();

    // 관성보다 작은 명령 무시
    if(right_wheel_cmd_vel == 0.0)
    {
      right_wheel_cmd = 0.0;
    }
    if(left_wheel_cmd_vel == 0.0)
    {
      left_wheel_cmd = 0.0;
    }

    String encoder_read = "r" + right_wheel_sign + String(right_wheel_meas_vel) + ",l" + left_wheel_sign + String(left_wheel_meas_vel) + ",";
    Serial.println(encoder_read);
    last_millis = current_millis;
    right_encoder_counter = 0;
    left_encoder_counter = 0;

    analogWrite(L298N_enA, right_wheel_cmd);
    analogWrite(L298N_enB, left_wheel_cmd);
  }
}

// 오른쪽 휠 엔코더의 새 펄스
void rightEncoderCallback()
{
  if(digitalRead(right_encoder_phaseB) == HIGH)
  {
    right_wheel_sign = "p";
  }
  else
  {
    right_wheel_sign = "n";
  }
  right_encoder_counter++;
}

// 왼쪽 휠 엔코더의 새 펄스
void leftEncoderCallback()
{
  if(digitalRead(left_encoder_phaseB) == HIGH)
  {
    left_wheel_sign = "n";
  }
  else
  {
    left_wheel_sign = "p";
  }
  left_encoder_counter++;
}