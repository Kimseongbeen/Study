int S = A0; // Analog Input
int d1=D1;
void setup()
{
 Serial.begin(115200); // 시리얼 통신 초기화
 pinMode(d1, OUTPUT);
 pinMode(S, INPUT);
}

void loop()
{
  int sensor=analogRead(S);

  if(sensor>15){             //센서값이 15 초과일때 NC
    digitalWrite(d1,LOW);
}
  else if(sensor<=15){       //센서값이 15 이하일때 NO 
    digitalWrite(d1,HIGH);
  }
 Serial.println(sensor);
 delay(1000);
}
