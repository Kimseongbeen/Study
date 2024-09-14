#include <Arduino.h>

// L298N H-Bridge Connection PINs
#define L298N_enA 9  // PWM
#define L298N_enB 11 // PWM
#define L298N_in4 8  // Dir Motor B
#define L298N_in3 7  // Dir Motor B
#define L298N_in2 13 // Dir Motor A
#define L298N_in1 12 // Dir Motor A

// Control variables
double right_wheel_cmd_vel = 0.0; // rad/s
double left_wheel_cmd_vel = 0.0;  // rad/s
double right_wheel_cmd = 0.0;     // 0-255
double left_wheel_cmd = 0.0;      // 0-255

// Timing
unsigned long last_millis = 0;
const unsigned long interval = 100;

void setup() {
  // Init L298N H-Bridge Connection PINs
  pinMode(L298N_enA, OUTPUT);
  pinMode(L298N_enB, OUTPUT);
  pinMode(L298N_in1, OUTPUT);
  pinMode(L298N_in2, OUTPUT);
  pinMode(L298N_in3, OUTPUT);
  pinMode(L298N_in4, OUTPUT);

  // Set initial Motor Rotation Direction
  digitalWrite(L298N_in1, HIGH);
  digitalWrite(L298N_in2, LOW);
  digitalWrite(L298N_in3, HIGH);
  digitalWrite(L298N_in4, LOW);

  Serial.begin(115200);
}

void loop() {
  // Read and Interpret Wheel Velocity Commands
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    parseCommand(command);
  }

  // Update motor commands
  unsigned long current_millis = millis();
  if (current_millis - last_millis >= interval) {
    updateMotorCommands();
    last_millis = current_millis;
  }
}

void parseCommand(String command) {
  int commaIndex = command.indexOf(',');
  if (commaIndex != -1) {
    right_wheel_cmd_vel = command.substring(0, commaIndex).toFloat();
    left_wheel_cmd_vel = command.substring(commaIndex + 1).toFloat();
  }
}

void updateMotorCommands() {
  // Simple mapping from rad/s to PWM values (0-255)
  // You may need to adjust these mappings based on your motor specifications
  right_wheel_cmd = map(abs(right_wheel_cmd_vel * 100), 0, 1000, 0, 255);
  left_wheel_cmd = map(abs(left_wheel_cmd_vel * 100), 0, 1000, 0, 255);

  // Set direction
  digitalWrite(L298N_in1, right_wheel_cmd_vel >= 0 ? HIGH : LOW);
  digitalWrite(L298N_in2, right_wheel_cmd_vel >= 0 ? LOW : HIGH);
  digitalWrite(L298N_in3, left_wheel_cmd_vel >= 0 ? HIGH : LOW);
  digitalWrite(L298N_in4, left_wheel_cmd_vel >= 0 ? LOW : HIGH);

  // Set speed
  analogWrite(L298N_enA, right_wheel_cmd);
  analogWrite(L298N_enB, left_wheel_cmd);

  // Send feedback (estimated velocities based on commands)
  String feedback = "r" + String(right_wheel_cmd_vel >= 0 ? "p" : "n") + String(abs(right_wheel_cmd_vel), 2) + 
                    ",l" + String(left_wheel_cmd_vel >= 0 ? "p" : "n") + String(abs(left_wheel_cmd_vel), 2) + ",";
  Serial.println(feedback);
}