#include <Servo.h> 
#include <DFRobot_SIM808.h>
#define PHONE_NUMBER "0996205639"
#define morningMessage "Take your morning dose"
#define afternoonMessage "Take your afternoon dose"
#define nightMessage "Take your night dose"
DFRobot_SIM808 sim808(&Serial);
#define   NOTE_C4 262
String medTimes[]={"Morning","Afternoon","Night"};
String medNow;
Servo med1;
Servo med2;
Servo med3;
Servo med4;
int medController=0;
int medCount=0;
int led=7;
int buzz=8;
int button=9;
int buttonState;
int doorPosition=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  med1.attach(13);
  med2.attach(12);
  med3.attach(11);
  med4.attach(10);
  pinMode(button,INPUT_PULLUP);
  pinMode(buzz,OUTPUT);
  pinMode(led,OUTPUT);

  // while(!sim808.init()){
  //   delay(1000);
  //   Serial.println("Sim init error");
  // }
  
    // sim808.sendSMS(PHONE_NUMBER,message);
}

void loop() {
//   put your main code here, to run repeatedly:
medNow=medTimes[medCount];
if(medController==0){
  tone(buzz, NOTE_C4);
  digitalWrite(led,HIGH);
}
  buttonState=digitalRead(button);
if(doorPosition==1 && buttonState==0){

 if(medNow== "Morning" && medController==0) {
 med1.write(60); 
 med2.write(60);
// Serial.println("Morning");

 digitalWrite(led,LOW);
// sim808.sendSMS(PHONE_NUMBER,morningMessage );
noTone(buzz);
 medController=1;
}
else if(medNow=="Afternoon" && medController==0) {
Serial.println("Afternoon");
 med2.write(60);
 med3.write(60);
 med4.write(60);
 noTone(buzz);
//  sim808.sendSMS(PHONE_NUMBER,afternoonMessage);

 digitalWrite(led,LOW);
 medController=1;
}
else if(medNow=="Night" && medController==0) {
  Serial.println("Night");
 med1.write(60);
 med2.write(60);
 med3.write(60);
//  med4.write(60);
//     sim808.sendSMS(PHONE_NUMBER,nightMessage);
    noTone(buzz);
    
 digitalWrite(led,LOW);
  medController=1; 
}
else{
 med1.write(179);
 med2.write(179); 
 med3.write(179);
 med4.write(179);
  noTone(buzz);
 digitalWrite(led,LOW);
 medController=0;
}

if(medController==1){
  delay(100);
}
else{
delay(3000);
}

}
doorPosition=buttonState;
  if(medCount>2){
    medCount=0;
  }else{
    medCount++;
  }

}
