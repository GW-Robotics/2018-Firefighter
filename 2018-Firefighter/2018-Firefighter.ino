#include <Servo.h>

#include <Ultrasonic.h>

#include "FreqCount.h"

#define LEFT_SERVO_PIN  4
#define RIGHT_SERVO_PIN 5
#define IR_PIN 6
#define EXTINGUISHER_PIN 7
#define FLAME_LED 9
#define MIC_LED 11
#define BABY_LED 17
#define CAMERA 15
#define CAMERA_LED 16

//Ultrasonic Trigger and Echo pins (30-39)
#define F_L_ECHO  30  //Front-left Ultrasonic
#define F_L_TRIG  31
#define F_R_ECHO  32  //Front-right Ultrasonic
#define F_R_TRIG  33
#define R_ECHO  34  //Right Ultrasonic
#define R_TRIG  35
#define B_ECHO  36  //Back Ultrasonic
#define B_TRIG  37
#define L_ECHO  38  //Left Ultrasonic
#define L_TRIG  39

// Bounds for start sound frequency:
#define LOW_START 3306
#define HIGH_START 4294

Servo leftServo;
Servo rightServo;
Servo extinguisher;

Ultrasonic frontLeftUltrasonic(F_L_ECHO, F_L_TRIG, true);
Ultrasonic frontRightUltrasonic(F_R_ECHO, F_R_TRIG, true);
Ultrasonic leftUltrasonic(L_ECHO, L_TRIG, true);
Ultrasonic rightUltrasonic(R_ECHO, R_TRIG, true);
Ultrasonic backUltrasonic(B_ECHO, B_TRIG, true);

bool checkingMicrophone = true;
bool hearingStartSound = false;
bool robotOn = false;
unsigned long freqCount;

void moveForward() {
  leftServo.write(180);
  rightServo.write(0);
}

void moveBackward() {
  leftServo.write(0);
  rightServo.write(180);
}

void moveLeft() {
  leftServo.write(180);
  rightServo.write(180);
}

void moveRight() {
  leftServo.write(0);
  rightServo.write(0);
}

void stopRobot() {
  leftServo.write(90);
  rightServo.write(90);
}

boolean detectFire(){
  return digitalRead(IR_PIN);
}

void startExtinguisher(){
  extinguisher.write(180);
}

void stopExtinguisher(){
  extinguisher.write(90);
}

int detectBaby(){return 0;}
int usingCamera(){return 0;}

void extinguishFire(){
  while (detectFire()) {
     if (detectFire()){
      digitalWrite(FLAME_LED, HIGH);
     } else {
     digitalWrite(FLAME_LED, LOW);
     }
    
    if (frontLeftUltrasonic.getDistance() > 3) {
      moveForward();
    } else {
      stopRobot();
      delay(500);
      
      startExtinguisher();
      delay(500);
      
      if (!detectFire()) {
        stopExtinguisher();
      }
    }
    delay(100);
  }
}

void checkMicrophone() {
  // Measure sound:
  if (FreqCount.available()) {
    freqCount = FreqCount.read();
  } else {
    freqCount = 0;
  }

  // If the sound frequency is within start sound bounds, turn on robot:
  if (freqCount > LOW_START && freqCount < HIGH_START) {
    robotOn = true; // Set the robot to on
    hearingStartSound = true;
  } else {
    hearingStartSound = false;
    if (robotOn) {
      checkingMicrophone = false;
      FreqCount.end();
    }
  }
}

void mazeNav() { //MOVE MY MINION
  if(frontLeftUltrasonic.getDistance() < 2 && leftUltrasonic.getDistance() < 2){ //robot has wall in front and to left
    moveRight();
    delay(500);
  }
  else if(frontLeftUltrasonic.getDistance() < 2 && leftUltrasonic.getDistance() >= 2){ //robot has wall in front
    moveLeft();
    delay(500);
  }
  else{ //if(frontLeftUltrasonic.getDistance() >=2 && leftUltrasonic.getDistance() <2), or if (frontLeftUltrasonic.getDistance() >= 2 && leftUltrasonic.getDistance() >= 2): hug the left wall
    moveForward();
    delay(500);
  }
}

void setup() {
  // put your setup code here, to run once:
  leftServo.attach(LEFT_SERVO_PIN);
  rightServo.attach(RIGHT_SERVO_PIN);
  extinguisher.attach(EXTINGUISHER_PIN);
  stopRobot();
  extinguisher.write(90);

  pinMode(IR_PIN, INPUT);
  pinMode(FLAME_LED, OUTPUT);
  
  pinMode(MIC_LED, OUTPUT);
  
  pinMode(BABY_LED, OUTPUT);
  
  pinMode(CAMERA_LED, OUTPUT);

  FreqCount.begin(1000); // Begin measuring sound
}

void loop() {
// put your main code here, to run repeatedly:

  if (checkingMicrophone) {
    checkMicrophone();
  }
  
  mazeNav();
  extinguishFire();
  delay(100);
  
  if (usingCamera()){
    digitalWrite(CAMERA_LED, HIGH);
  } else {
    digitalWrite(CAMERA_LED, LOW);
  }
  
  if(detectBaby()){
    digitalWrite(BABY_LED, HIGH);
  } else {
    digitalWrite(BABY_LED, LOW);
  }
  

  if (robotOn) {
    mazeNav();
    
    extinguishFire();
    
    delay(100);
  
    if (detectFire()){
      digitalWrite(FLAME_LED, HIGH);
    } else {
      digitalWrite(FLAME_LED, LOW);
    }
    
    if (usingCamera()){
      digitalWrite(CAMERA_LED, HIGH);
    } else {
      digitalWrite(CAMERA_LED, LOW);
    }
    
    if(detectBaby()){
      digitalWrite(BABY_LED, HIGH);
    } else {
      digitalWrite(BABY_LED, LOW);
    }
    
    if(hearingStartSound){
      digitalWrite(MIC_LED, HIGH);
    } else {
      digitalWrite(MIC_LED, LOW);
    }
  }
}
