#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// WiFi 설정
const char* ssid = "";        // 와이파이 이름
const char* password = "";     // 와이파이 비밀번호

// MQTT 설정
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char* control_topic = "n8n/relay/control";  // 제어 명령 수신
const char* status_topic = "n8n/relay/status";    // 상태 보고

// 핀 설정
const int RELAY_PINS[4] = {26, 27, 32, 33};  // 출력 핀 (릴레이)
const int INPUT_PINS[4] = {16, 17, 18, 19};  // 입력 핀 (GPIO 36, 39, 34, 35는 입력 전용)
bool relayStates[4] = {false, false, false, false};   // 릴레이 상태 저장
bool lastRelayStates[4] = {false, false, false, false}; // 이전 릴레이 상태 저장
bool inputStates[4] = {false, false, false, false};   // 입력 상태 저장
bool lastInputStates[4] = {false, false, false, false}; // 이전 입력 상태

// 상태 체크 타이머
unsigned long lastStatusCheck = 0;
const long statusInterval = 5000;  // 입력 상태 체크 주기 (5000ms)

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  delay(10);

  // 핀 초기화
  for(int i = 0; i < 4; i++) {
    pinMode(RELAY_PINS[i], OUTPUT);
    digitalWrite(RELAY_PINS[i], LOW);
    pinMode(INPUT_PINS[i], INPUT);
  }
  
  // WiFi 연결
  WiFi.begin(ssid, password);
  Serial.println("WiFi 연결 중...");
  
  int wifiAttempts = 0;
  while (WiFi.status() != WL_CONNECTED && wifiAttempts < 20) {
    delay(500);
    Serial.print(".");
    wifiAttempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi 연결됨");
    Serial.println("IP 주소: " + WiFi.localIP().toString());
    
    // MQTT 설정
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
    client.setKeepAlive(60);  // keepalive 시간 설정
  } else {
    Serial.println("\nWiFi 연결 실패");
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // 입력 상태 주기적 체크
  unsigned long currentMillis = millis();
  if (currentMillis - lastStatusCheck >= statusInterval) {
    lastStatusCheck = currentMillis;
    checkStates();
  }
}

// 입력 상태 체크
void checkStates() {
  bool stateChanged = false;
  
  // 입력 핀의 상태 체크
  for(int i = 0; i < 4; i++) {
    bool currentState = digitalRead(INPUT_PINS[i]);
    if(currentState != lastInputStates[i]) {
      inputStates[i] = currentState;
      lastInputStates[i] = currentState;
      stateChanged = true;
      
      Serial.print("입력 ");
      Serial.print(i);
      Serial.println(currentState ? " HIGH" : " LOW");
    }
  }

  // 출력(릴레이) 상태 체크
  for(int i = 0; i < 4; i++) {
    if(relayStates[i] != lastRelayStates[i]) {
      lastRelayStates[i] = relayStates[i];
      stateChanged = true;
      
      Serial.print("출력 ");
      Serial.print(i);
      Serial.println(relayStates[i] ? " HIGH" : " LOW");
    }
  }

  // 상태가 변경되었다면 업데이트 전송
  if(stateChanged) {
    sendStatus();
  }
}

// MQTT 메시지 수신 콜백
void callback(char* topic, byte* payload, unsigned int length) {
  char message[length + 1];
  memcpy(message, payload, length);
  message[length] = '\0';

  Serial.println("수신된 메시지: " + String(message));

  DynamicJsonDocument doc(200);
  DeserializationError error = deserializeJson(doc, message);
  
  if (!error) {
    // 개별 릴레이 제어
    if (doc.containsKey("relay") && doc.containsKey("state")) {
      int relay = doc["relay"].as<int>();
      bool state = doc["state"].as<bool>();
      
      if (relay >= 0 && relay < 4) {
        digitalWrite(RELAY_PINS[relay], state ? HIGH : LOW);
        relayStates[relay] = state;
        
        Serial.print("릴레이 ");
        Serial.print(relay);
        Serial.println(state ? " 켜짐" : " 꺼짐");
        
        sendStatus();
      }
    }
    // 모든 릴레이 제어
    else if (doc.containsKey("all")) {
      bool state = doc["all"].as<bool>();
      for (int i = 0; i < 4; i++) {
        digitalWrite(RELAY_PINS[i], state ? HIGH : LOW);
        relayStates[i] = state;
      }
      Serial.println(state ? "모든 릴레이 켜짐" : "모든 릴레이 꺼짐");
      sendStatus();
    }
  }
}

// MQTT 재연결
void reconnect() {
  while (!client.connected()) {
    Serial.print("MQTT 연결 시도...");
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("연결됨");
      client.subscribe(control_topic);
      sendStatus(); // 초기 상태 전송
    } else {
      Serial.print("실패, rc=");
      Serial.print(client.state());
      Serial.println(" 5초 후 재시도");
      delay(5000);
    }
  }
}

// 상태 전송
void sendStatus() {
  DynamicJsonDocument doc(200);
  
  // 출력(릴레이) 상태
  JsonArray outputs = doc.createNestedArray("outputs");
  for (int i = 0; i < 4; i++) {
    outputs.add(relayStates[i]);
  }

  // 입력 상태
  JsonArray inputs = doc.createNestedArray("inputs");
  for (int i = 0; i < 4; i++) {
    inputs.add(inputStates[i]);
  }
  
  char buffer[200];
  serializeJson(doc, buffer);
  client.publish(status_topic, buffer);
  Serial.println("상태 전송: " + String(buffer));
}
