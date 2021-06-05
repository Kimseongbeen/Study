const int buzzPin = D1;
const int trigPin = D2; 
const int echoPin = D3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(buzzPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);  // 2us
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // 10us
  digitalWrite(trigPin, LOW);

  long timeDistance = pulseIn(echoPin, HIGH);
  long distance = (timeDistance/2) / 29.1; //cm 변환

  Serial.print(distance);
  Serial.println("cm");

  if(distance <=10){
    digitalWrite(D1,HIGH); 
  }
  else{
    digitalWrite(D1,LOW);
}
}
