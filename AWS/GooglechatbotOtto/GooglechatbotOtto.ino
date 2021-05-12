#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Servo.h> 

// 아래의 6개설정은 사용자 환경에 맞게 수정하세요.
const char* ssid = "sbk"; // 와이파이 AP, 또는 스마트폰의 핫스판 이름
const char* password = "00000000";  // 와이파이 AP, 또는 스마트폰의 핫스판 이름
//const char* mqtt_server = "broker.mqtt-dashboard.com"; //브로커 주소
const char* thingId = "18.217.190.7";
const char* host = "a1uh55iuflfli7-ats.iot.us-east-2.amazonaws.com";
const char* outTopic = "/qodj/inTopic"; // 이름이 중복되지 않게 설정 기록
const char* inTopic = "/qodj/outTopic"; // 이름이 중복되지 않게 설정 기록
const char* clientName = "";  // setup 함수에서 자동생성

// 고유 ID생성
String sChipID;
char cChipID[20];


// 사물 인증서 (파일 이름: xxxxxxxxxx-certificate.pem.crt) 개인 AWS 사물 인증서를 입력
const char cert_str[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----

-----END CERTIFICATE-----
)EOF";
// 사물 인증서 프라이빗 키 (파일 이름: xxxxxxxxxx-private.pem.key)
const char key_str[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----

-----END RSA PRIVATE KEY-----
)EOF";
// Amazon Trust Services(ATS) 엔드포인트 CA 인증서 (서버인증 > "RSA 2048비트 키: Amazon Root CA 1" 다운로드)
const char ca_str[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----

-----END CERTIFICATE-----
)EOF";

long lastMsg = 0;
char msg[50];
// 모터 선언
Servo servoLeft1;
Servo servoLeft2;
Servo servoRight1;
Servo servoRight2;

//json을 위한 설정
StaticJsonDocument<200> doc;
DeserializationError error;
JsonObject root;

int Duty,order =0; //
int data[100],volume;  //volume : data[]의 개수
int iTime=500;  // 로봇 동작속도
// 통신에서 문자가 들어오면 이 함수의 payload 배열에 저장된다.

void callback(char* topic, byte* payload, unsigned int length) {
    int i,j,k;
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  deserializeJson(doc,payload);
  root = doc.as<JsonObject>();
  order = root["order"];
  Duty = root["duty"];
  int a = 8;
 
  if(order==0) // Dialogflow, 구글챗봇-Intents Parameter-order의 정지 값,구글챗봇에게 정지를 말하면 0이 들어오고 initset함수를 실행
    InitSet();                      
       
    //front 110070070110 070110110070
  else if(order==1){         //order==1 dialoglflow/Fulfillment/index.js에 order로 지정해둔 문자가 들어오면 해당  숫자가뜸    
    volume=a;
    data[0]=110;  
    data[1]=70;  
    data[2]=70;  
    data[3]=110;
    data[4]=70;
    data[5]=110; 
    data[6]=110; 
    data[7]=70;
  }
  
   //back 100110070070 070070100110
  else if(order==2){
    volume=a;
    data[0]=100;
    data[1]=110; 
    data[2]=70;
    data[3]=70;
    data[4]=70;
    data[5]=70; 
    data[6]=100;
    data[7]=110;
  }

  //right 130040090090 070100090090
  else if(order==3){
    volume=a;
    data[0]=60;
    data[1]=90; 
    data[2]=120; 
    data[3]=90;
    data[4]=120; 
    data[5]=90; 
    data[6]=60; 
    data[7]=90;
  }

  // left 090090060130 090090110070
  else if(order==4){
    volume=a;
    data[0]=60; 
    data[1]=90; 
    data[2]=120;  
    data[3]=90;
    data[4]=120;
    data[5]=90; 
    data[6]=60; 
    data[7]=90;
  }
  
  //dance 090040090140 090140090040
  else if(order==5){
    volume=a;
    data[0]=90; 
    data[1]=40; 
    data[2]=90;  
    data[3]=140;
    data[4]=90;
    data[5]=140; 
    data[6]=90; 
    data[7]=40;
  }
}

void InitSet() {
  servoLeft1.write(90);
  delay(iTime);
  servoLeft2.write(90);
  delay(iTime);
  servoRight1.write(90);
  delay(iTime);  
  servoRight2.write(90);
  delay(iTime);   
}

X509List ca(ca_str);
X509List cert(cert_str);
PrivateKey key(key_str);
WiFiClientSecure wifiClient;
PubSubClient client(host, 8883, callback, wifiClient);

void setup() {
  Serial.begin(115200);
  setup_wifi();
  delay(1000);

  //이름 자동으로 생성
  sChipID=String(ESP.getChipId(),HEX);
  sChipID.toCharArray(cChipID,sChipID.length()+1);
  clientName=&cChipID[0];
  Serial.println(clientName);

  client.setServer(host, 8883); //개인 포트에 맞춰서 AWS 8883, MQTT 1883
  client.setCallback(callback);

  servoLeft1.attach(5);  // 서보모터 GIO(숫자)
  servoLeft2.attach(4);  
  servoRight1.attach(0); 
  servoRight2.attach(2); 
}

void setClock() {
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));
}

void setup_wifi() {
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  wifiClient.setTrustAnchors(&ca);
  wifiClient.setClientRSACert(&cert, &key);
  Serial.println("Certifications and key are set");

  setClock();
  client.setServer(host, 8883);
  client.setCallback(callback);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(clientName)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(outTopic, "Reconnected");
      // ... and resubscribe
      client.subscribe(inTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      char buf[256];
      wifiClient.getLastSSLError(buf,256);
      Serial.print("WiFiClientSecure SSL error: ");
      Serial.println(buf);
      
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void DoArray() {
  int i,j,k;
  k=volume/4;
  for(i=0 ; i<volume ; i++) {
    j=i%4;
    Serial.println(j);
    Serial.println(data[i]);
    if(j==0)
       servoLeft1.write(data[i]);
    else if(j==1)
       servoLeft2.write(data[i]);
    else if(j==2)
       servoRight1.write(data[i]);
    else if(j==3)
       servoRight2.write(data[i]);

    delay(iTime);
  }
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
    client.loop();
  if(order==1||order==2||order==3||order==4||order==5) //order 들어오면 DoArray를 
    DoArray();
}
