#include <Servo.h> //servo library

Servo myservo; // create servo object to control servo

#define LT1 digitalRead(10)// linetracker 1
#define LT2 digitalRead(4)// linetracker 2
#define LT3 digitalRead(2)// linetracker 3


#define ENA 5
#define ENB 11
#define M1 6
#define M2 7
#define M3 8
#define M4 9

#define ABS 75
const int max_distance = 33;
int middle_distance = 0;
int stop_distance = 7;
int Echo = A4; // ultrasonic sensor
int Trig = A5; // ultrasonic sensor


//Different maneuvers for the Robot
// extreme is a hard turn
void forward() {
  analogWrite(ENA, ABS);
  analogWrite(ENB, ABS);
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  digitalWrite(M3, LOW);
  digitalWrite(M4, HIGH);

}

void back() {
  analogWrite(ENA, ABS);
  analogWrite(ENB, ABS);
  digitalWrite(M1, LOW);
  digitalWrite(M2, HIGH);
  digitalWrite(M3, HIGH);
  digitalWrite(M4, LOW);

}

void left() {
  analogWrite(ENA, ABS);
  analogWrite(ENB, ABS);
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  digitalWrite(M3, LOW);
  digitalWrite(M4, LOW);

}

void extremeleft() {
  analogWrite(ENA, ABS);
  analogWrite(ENB, ABS);
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  digitalWrite(M3, HIGH);
  digitalWrite(M4, LOW);

}

void right() {
  analogWrite(ENA, ABS);
  analogWrite(ENB, ABS);
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  digitalWrite(M3, LOW);
  digitalWrite(M4, HIGH);
}
void extremeright() {
  analogWrite(ENA, ABS);
  analogWrite(ENB, ABS);
  digitalWrite(M1, LOW);
  digitalWrite(M2, HIGH);
  digitalWrite(M3, LOW);
  digitalWrite(M4, HIGH);
}

void mstop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);

}
//measure the distance to an object
int Distance_test()
{
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);
  float Fdistance = pulseIn(Echo, HIGH);
  Fdistance = Fdistance / 58.2;
  return (int)Fdistance;
}
//Stop and pick up obstacle
void stopenpakop(){

 
 digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
   
     myservo.write(120);
  delay(2650);// tijd nog opmeten
  myservo.write(90);
  delay(2000);
  
  extremeright();
  delay(750);
  
forward();
delay(250);

  mstop();
  delay(1000);
  
  myservo.write(0);
  delay(2600);

myservo.write(90);
  delay(2600);
  
  /* mstop();
  delay(1000);
  */
  back();
  delay(150);
  
/*   mstop();
  delay(1000);
  */
  extremeleft();
  delay(750);
  
}
//line following code
void linefollower(){
  if  (LT2){

    
      forward();
      while (LT2);
     
    }

 else if (LT1) {
      left();

      while (LT1);

    }
  else if (LT3) {
      right();

      while (LT3);
    }

   // else mstop;
}

void setup() {

  Serial.begin(9600);//my servo.attach(3);
myservo.attach(12);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
//  pinMode(servoPin, OUTPUT); // hieer kijken waar we nog kunnen aansluiten
}
//main loop
void loop() {
 
Serial.println(Distance_test());
middle_distance=Distance_test();
delay(50); 

  while (middle_distance < 10)
  { 
stopenpakop();
  Serial.println(Distance_test());
middle_distance=Distance_test();
delay(50); }

  while (middle_distance >=10 ){
    linefollower();
    delay(0.001);
    
   
    Serial.println(Distance_test());
middle_distance=Distance_test();
delay(1); 
  }}
   


