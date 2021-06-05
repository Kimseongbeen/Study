int S = A0; // Analog Input
int d4=D4;
int d1=D1;
int d2=D2;
int d3=D3;
int count=0;
void setup()
{
 Serial.begin(115200); 
 pinMode(S, INPUT);
 pinMode(d4, INPUT);
 pinMode(d1, OUTPUT);
 pinMode(d2, OUTPUT);
 pinMode(d3, OUTPUT);
}

void loop()
{
if(analogRead(S) >100)
count++;
  if(count>=5)
  count=0;
  if(count==0){
    digitalWrite(d1,0);  //Blue
    digitalWrite(d2,0);   //Green
    digitalWrite(d3,0);   //Red
}
  else if(count==1){
   digitalWrite(d1,255);
   digitalWrite(d2,0);
   digitalWrite(d3,0);
}          
  else if(count==2){
   digitalWrite(d1,0); 
   digitalWrite(d2,255);
   digitalWrite(d3,0);
}         
  else if(count==3){
   digitalWrite(d1,0);  //Blue
   digitalWrite(d2,0);   //Green
   digitalWrite(d3,255);   //Red
}         
  else if(count==4){
   digitalWrite(d1,255);  //Blue
   digitalWrite(d2,255);   //Green
   digitalWrite(d3,255);   //Red
  }
 Serial.println(analogRead(S));
 Serial.println(digitalRead(d4));
 delay(200);
}
