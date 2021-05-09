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


String sChipID;
char cChipID[20];

// 사물 인증서 (파일 이름: xxxxxxxxxx-certificate.pem.crt)
const char cert_str[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUGPsurvDzpxlj1suob0PBdQek1K8wDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIxMDQwOTAyMjIw
MVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKW4zB4X1OOxbiQkVLRd
Eiz7AvAgEDU/7PItsKBHrdfObVkkps8naTS6LM4+LJuUw6qNQG5UPA7rLmU1QtBA
Z7APY0abzo5Y8tfDfY4cckJErd/BbNl3ieSnkolJ4ktqmYGtFn/KXvEwIS5w9+fz
xjfPs7pYr0qX+MD9NeWwRD+81oe3BCx2XZJYcrCKTbJ1b+msepkv4yy3/cz98jaQ
VDJRBpT04guDQlgJPsicLBtLvZtDIiBHqOF+ZpgvT5wObF+4uA7hKDX4rPEj3Iia
c50kKtGNyAlSuBpHEB34jlyTPp6vqzY7B0B9hXrlL2TQNKCQIH4lkuKlQofU01iA
NnkCAwEAAaNgMF4wHwYDVR0jBBgwFoAUFAyhpZJtASAjkY8QdCJ3H8m6B9AwHQYD
VR0OBBYEFPiV8+6AU/stpN3NI1ehfT0xUVzOMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQAiWeDM0PfmDqKPIoGFW1ms9Bj7
6VMJ04CL7S30YYUCObIryGNZnhHRkPXbUzhuvog1E6dZhX1Zwj65gqU1IEnIezMf
CNeUPVvBkuzrojTChTOJdvhD3NUEr06Fi8bbOEj1on90tf0H0u7P4/TM+peNkCVn
Ine3kFauw5pxQzDgi22rI79hQSDACAtqD1NBKF39k3lpEtboe6lX2mzih7scoKQb
qZgdZstIfmlR3YFPCz78C4vhEBErtZdNUSw+XL7p48eOa3RMoWEc2H5ldlJ4+jBm
80eiwnNKDVBZp8DzaaAIRk5zSMj4tXpTHtSnIuKdHUt48ya9VeIdNaQPcjjX
-----END CERTIFICATE-----
)EOF";
// 사물 인증서 프라이빗 키 (파일 이름: xxxxxxxxxx-private.pem.key)
const char key_str[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEApbjMHhfU47FuJCRUtF0SLPsC8CAQNT/s8i2woEet185tWSSm
zydpNLoszj4sm5TDqo1AblQ8DusuZTVC0EBnsA9jRpvOjljy18N9jhxyQkSt38Fs
2XeJ5KeSiUniS2qZga0Wf8pe8TAhLnD35/PGN8+zulivSpf4wP015bBEP7zWh7cE
LHZdklhysIpNsnVv6ax6mS/jLLf9zP3yNpBUMlEGlPTiC4NCWAk+yJwsG0u9m0Mi
IEeo4X5mmC9PnA5sX7i4DuEoNfis8SPciJpznSQq0Y3ICVK4GkcQHfiOXJM+nq+r
NjsHQH2FeuUvZNA0oJAgfiWS4qVCh9TTWIA2eQIDAQABAoIBAFO/8GfE43GuWVsq
gSQlZOoWcIWproc6pyQ8suZNUy2cxOYn/6Tw5dofvET+Zsy5gajPeaBIMZHYiLnd
EMbtxXjUTfeBBgIqMY+Y2/rVpWiYDMbnmXrNToKfrQ50qEg0tx8xug0a2KBLEnnF
3YL7T1ElRk8GQpAP/UaKsJJDYjpTBDsBnEQzbEMiWcOGpF2n4zQUYVpbwIrA3XiQ
hPOAoHPPmEV5RyjHzlXtx6RVgF4ehyuAAmWMbFMWLUmcAxxBR0OkipT4Cxy7y6Vq
hEAMFeM7NzyjyqfWukLJx5nlbJotE7QP9ogzZlJlrIWMYZdunUYcchAFY5hNeH53
yRE8QAECgYEA1qWbkq0FRc35iLsYppZlA7fhVK7X39fwPQstTHkIQoecptw5x/AA
vhSY/NiWuXNhBMjjCt36fx7k3U6NAYxmw2sSLZg1pA7dF/n66xx6HFdvY7RY29xq
oPc0NiTv3Lh3k2KLQCf914tZqx2jBCHM/FW9ON4QJXW0X3fN0cCJtjkCgYEAxaY0
fhFAu9QWd2S+w0YEiyS/2h1RnxtixgCIMfPnY6Bwgi/Qhe7fVsUThdEgH+RG8KTP
Clqsf9bcz4jhxhUQAvNSlObxg39bFZMP4v6sqYTkzhpG7BXknIFHs9qClXJw5Rq4
/UvAKnf0H8frDI/PnMz5jQBdv1BdVzi2j78AgkECgYAUC1MD13RumFV9FzuuEs1M
E5fPOKSgGqIskSahxYun6tIOIvKiYR8woOvIcNFicAvXToslMKV7yX7Fy9gPFPVj
ulPwPg6ES38KBiYQXpBopSGZxfWmUmcCsRMHG1vq2K8R7Fnkm9dwkWrGN/ZJJH7n
8XnCHbqURPGbGKz3sWsqwQKBgQCLgDOshyDZcWgp/MFnshOi4d1HZUomsn2Uout9
1liKyMKgIH9dCKw54f9Vg7TYzZYEY05+UGFQGabgFAzGcjdK3dJ7pkTwOwNext1/
qaDURSf5EDLejtU8YULqfl+Me6mTCrlmjgCj+OYlSEVuKFKwqTu5eXixf1diKHUy
H+2MAQKBgQCYd9/SXaZdUCx8wUcV6/z9lYoxJKX2JnlT6oNx8J3Ct3qCBEPNkG56
X7LubBfD1ES/RZQdL5g4RwKK0iZvLwERedloEOOdASnWfPEWSH3WIYqk8sOKcHtL
RMQBTOTfGBFxmHXu4dfbaxNJok4ZWjFP3h5rqB/d6SuefyZEvaq1GQ==
-----END RSA PRIVATE KEY-----
)EOF";
// Amazon Trust Services(ATS) 엔드포인트 CA 인증서 (서버인증 > "RSA 2048비트 키: Amazon Root CA 1" 다운로드)
const char ca_str[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----

)EOF";


long lastMsg = 0;
char msg[50];
Servo servoLeft1;
Servo servoLeft2;
Servo servoRight1;
Servo servoRight2;

//json을 위한 설정
StaticJsonDocument<200> doc;
DeserializationError error;
JsonObject root;

int Duty,mode=0; //imode 0=초기치 1,2,3,4=서보모터 회전 5=동작속도 9=DoArray
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

  int premode=mode;
  deserializeJson(doc,payload);
  root = doc.as<JsonObject>();
  mode = root["mode"];
  Duty = root["duty"];
  if(mode==0)
    InitSet();
  else if(mode==1)
    servoLeft1.write(Duty);
  else if(mode==2)
    servoLeft2.write(Duty);
  else if(mode==3)
    servoRight1.write(Duty);
  else if(mode==4)
    servoRight2.write(Duty);
  else if(mode==5) {
    iTime = root["valocity"];
    mode=premode;
  }
  else if(mode==9) { 
      volume = root["volume"]; 
      Serial.println(volume);
      for(i=0; i<volume;i++)
        data[i]= root["data"][i];     
    Serial.println("=======");
    for(i=0;i<volume;i++)
      Serial.println(data[i]);
  }
  else
    Serial.print("No choice");
  Serial.print(mode);
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

  client.setServer(host, 8883);
  client.setCallback(callback);

  servoLeft1.attach(5);  // attaches the servo on GIO5 to the servo object 
  servoLeft2.attach(4);  
  servoRight1.attach(0); 
  servoRight2.attach(2); 
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
  //client.setServer(host, 8883);
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

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  if(mode==9)
    DoArray();
}
