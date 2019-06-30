/*
 id   1  |  2     col   3   2   1   0
     _________     ___________________
    |   ___   |   |_  |   |   |   |   |
    |  _____  |   |_  |   |   |   |   |
    | |_____| |    _|     C   B   A   |
    | _______ |   |__H   F   E   D    |  
    ||_______||     I|                |
    |_________|    __|________G_______|

*/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>
#define SERVOMIN  150
#define SERVOMAX  600 
#define G_OPEN 25
#define G_CLOSE 60
#define H_OPEN 150
#define H_CLOSE 30
#define OPEN 60
#define CLOSE 150
#define DISTANCE 10
#define A1 0
#define B1 1
#define C1 15
#define D1 2
#define E1 3
#define F1 5
#define I1 6
#define A2 7
#define B2 8
#define C2 9
#define D2 10
#define E2 11
#define F2 12
#define I2 13
#define TRIGPIN1 2
#define ECHOPIN1 3
#define TRIGPIN2 4
#define ECHOPIN2 5
#define G1PIN 6
#define H1PIN 9
#define G2PIN 10
#define H2PIN 11
#define DELAYH 2000
#define DELAYG 2000
#define DURATION 1000
#define OPEN_I 30
#define CLOSE_I 120
#define OPEN_DEF 30
#define CLOSE_DEF 120

const float temperature=26; //Celsius degree
float v=331.5 + 0.6*temperature; //sound velocity
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Servo myservoG1, myservoH1;
Servo myservoG2, myservoH2;
int column1 = 0;
int column2 = 0;
uint16_t openLen = map(OPEN, 0, 180, SERVOMIN, SERVOMAX);
uint16_t closeLen = map(CLOSE, 0, 180, SERVOMIN, SERVOMAX);
uint16_t openLen_I = map(OPEN_I, 0, 180, SERVOMIN, SERVOMAX);
uint16_t closeLen_I = map(CLOSE_I, 0, 180, SERVOMIN, SERVOMAX);
uint16_t openLen_DEF = map(OPEN_DEF, 0, 180, SERVOMIN, SERVOMAX);
uint16_t closeLen_DEF = map(CLOSE_DEF, 0, 180, SERVOMIN, SERVOMAX);
char id;

long ping(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  unsigned long tUs=pulseIn(echoPin, HIGH); 
  float t=tUs/1000.0/1000.0/2; //turn us to s of single way
  float d=t*v;
  return d*100; // cm
}

long measure(int trigPin, int echoPin){
  int n = 0;
  long sum = 0;
  while(n<10){
    long cm = ping(trigPin, echoPin);
    //Serial.println(cm);
    if(cm < 25) sum += cm;
    else sum += 25;
    n++;
    delay(20);
  }
  float avg = sum/10;
  return (long)avg;
}

void Export(int id, int trigPin, int echoPin, Servo myservoG, Servo myservoH){
  if(id == 1){
    // OPEN/CLOSE H
    myservoH.write(H_OPEN);
    delay(DELAYH);
    myservoH.write(H_CLOSE);
    delay(DURATION);
    
    // OPEN/CLOSE G 
    myservoG.write(G_OPEN);
    delay(DELAYG);
    myservoG.write(G_CLOSE);
    delay(DURATION);
  }
  if(id == 2){
    // OPEN/CLOSE H
    myservoH.write(H_CLOSE);
    delay(DELAYH);
    myservoH.write(H_OPEN);
    delay(DURATION);
    
    // OPEN/CLOSE G 
    myservoG.write(G_CLOSE);
    delay(DELAYG);
    myservoG.write(G_OPEN);
    delay(DURATION);
  }
  
  long cm = measure(trigPin, echoPin);
  Serial.print("distance = ");
  Serial.println(cm);
  
  if(cm > DISTANCE){ //NO ITEM
    Serial.println("change column!");
    if(id == 1){
      if(column1 == 0){
        pwm.setPWM(A1, 0, openLen);
        delay(2*DURATION);
        column1++;
      }
      else if(column1 == 1){
        pwm.setPWM(B1, 0, openLen);
        delay(3*DURATION);
        column1++;
      }
      else if(column1 == 2){
        pwm.setPWM(C1, 0, openLen);
        delay(4*DURATION);
        column1++;
      }
      else if(column1 == 3){
        Serial.println("NO ITEM 1");
      }
    // OPEN/CLOSE G 
    myservoG.write(G_OPEN);
    delay(DELAYG);
    myservoG.write(G_CLOSE);
    delay(DURATION);
    Serial.print("column = ");
    Serial.println(column1);
    }
    if(id == 2){
      if(column2 == 0){
        pwm.setPWM(A2, 0, closeLen);
        delay(2*DURATION);
        column2++;
      }
      else if(column2 == 1){
        pwm.setPWM(B2, 0, closeLen);
        delay(3*DURATION);
        column2++;
      }
      else if(column2 == 2){
        pwm.setPWM(C2, 0, closeLen);
        delay(4*DURATION);
        column2++;
      }
      else if(column2 == 3){
        Serial.println("NO ITEM 2");
      }
    myservoG.write(G_CLOSE);
    delay(DELAYG);
    myservoG.write(G_OPEN);
    delay(DURATION);
    Serial.print("column = ");
    Serial.println(column2);
    }
  }
}

void Shutdown(){
  myservoG1.write(G_CLOSE);
  myservoH1.write(H_CLOSE);
  myservoG2.write(G_OPEN);
  myservoH2.write(H_OPEN);
  pwm.setPWM(A1, 0, closeLen);
  pwm.setPWM(B1, 0, closeLen);
  pwm.setPWM(C1, 0, closeLen);
  pwm.setPWM(A2, 0, openLen);
  pwm.setPWM(B2, 0, openLen);
  pwm.setPWM(C2, 0, openLen);
  delay(1000);
//  pwm.setPWM(I1, 0, closeLen_I);
//  pwm.setPWM(I2, 0, openLen_I);
//  pwm.setPWM(D1, 0, closeLen_DEF);
//  pwm.setPWM(E1, 0, closeLen_DEF);
//  pwm.setPWM(F1, 0, closeLen_DEF);
//  pwm.setPWM(D2, 0, openLen_DEF);
//  pwm.setPWM(E2, 0, openLen_DEF);
//  pwm.setPWM(F2, 0, openLen_DEF);
  delay(1000);
}

void reset(){
  column1 = 0;
  column2 = 0;
  myservoG1.write(G_CLOSE);
  myservoH1.write(H_CLOSE);
  myservoG2.write(G_OPEN);
  myservoH2.write(H_OPEN);
//  pwm.setPWM(I1, 0, openLen_I);
//  pwm.setPWM(I2, 0, closeLen_I);
//  pwm.setPWM(D1, 0, openLen_DEF);
//  pwm.setPWM(E1, 0, openLen_DEF);
//  pwm.setPWM(F1, 0, openLen_DEF);
//  pwm.setPWM(D2, 0, closeLen_DEF);
//  pwm.setPWM(E2, 0, closeLen_DEF);
//  pwm.setPWM(F2, 0, closeLen_DEF);
  delay(1000);
  pwm.setPWM(A1, 0, closeLen);
  pwm.setPWM(B1, 0, closeLen);
  pwm.setPWM(C1, 0, closeLen);
  pwm.setPWM(A2, 0, openLen);
  pwm.setPWM(B2, 0, openLen);
  pwm.setPWM(C2, 0, openLen);
}

void setup() 
{
  column1 = 0;
  column2 = 0;
  Serial.begin(9600);
  myservoG1.attach(G1PIN);
  myservoH1.attach(H1PIN);
  myservoG2.attach(G2PIN);
  myservoH2.attach(H2PIN);
  pinMode(TRIGPIN1, OUTPUT);
  pinMode(ECHOPIN1, INPUT);
  pinMode(TRIGPIN2, OUTPUT);
  pinMode(ECHOPIN2, INPUT);
  pwm.begin();
  pwm.setPWMFreq(60);
  reset();
}

void loop() {
  id = Serial.read();
  if(id == '1') Export(1, TRIGPIN1, ECHOPIN1, myservoG1, myservoH1);
  if(id == '2') Export(2, TRIGPIN2, ECHOPIN2, myservoG2, myservoH2);
  if(id == 'r') reset();
  if(id == 's') Shutdown();
  delay(1000);
}
