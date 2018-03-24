#include <Servo.h>

#include <Ultrasonic.h>

#include "FreqCount.h"

#define LEFT_SERVO_PIN  4
#define RIGHT_SERVO_PIN 5
#define IR_PIN_LEFT 6
#define IR_PIN_RIGHT 20
#define EXTINGUISHER_PIN 7
#define FLAME_LED 9
#define MIC_LED 11
#define BABY_LED 17
#define CAMERA 15
#define CAMERA_LED 16
#define GYRO_INPUT_PIN 18

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

//Gyroscope controls
float gyroStartAngle;
float gyroTargetAngle = 0;

bool checkingMicrophone = true;
bool hearingStartSound = false;
bool robotOn = false;
unsigned long freqCount;
double closeToWall = 2;   //defines how close the robot should be (inches) to the wall to register as being "too close"

void rollForward() {
  leftServo.write(180);
  rightServo.write(0);
}

void rollBackward() {
  leftServo.write(0);
  rightServo.write(180);
}

void moveSlightLeft() {
  leftServo.write(135);
  rightServo.write(20); //Half power plus additional 25
  delay(100);
}

void moveSlightRight() {
  leftServo.write(160); //Half power plus additional 25
  rightServo.write(45);
  delay(100);
}

void stopRobot() {
  leftServo.write(90);
  rightServo.write(90);
}

boolean detectFire(){
  if(digitalRead(IR_PIN_RIGHT || IR_PIN_RIGHT)){
    return true;
  } else {
    return false;
  }
}

void startExtinguisher(){
  extinguisher.write(180);
}

void stopExtinguisher(){
  extinguisher.write(90);
}

//Gyro functions
//Resets the gyro so that the current positioning is angle "0"
void resetGyro(){
  gyroStartAngle = digitalRead(GYRO_PIN);
  gyroTargetAngle = 0;
}

//Returns the current angle of the robot relative to its starting angle
float getGyroAngle(){
  return digitalRead(GYRO_PIN)-gyroStartAngle;
}

//adjusts the target angle based on how much we want to turn and turns the robot until that target is reached
//use turn(0) to simply get the gyro back on track if it's off target
void turn(int angle){
  gyroTargetAngle += angle;
  if(gyroTargetAngle > 360){
    gyroTargetAngle = 360 - gyroTargetAngle;
  }
  if(gyroTargetAngle < 0){
    gyroTargetAngle = 360 + gyroTargetAngle
  }
  if(gyroTargetAngle < getGyroAngle()){
    leftServo.write(180);
    rightServo.write(180);
    while(gyroTargetAngle < getGyroAngle()){
      delay(50);
    }
    stopRobot();
  }else if(gyroTargetAngle > getGyroAngle()){
    leftServo.write(0);
    rightServo.write(0);
    while(gyroTargetAngle > getGyroAngle()){
      delay(50);
    }
    stopRobot();
  }
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
      rollForward();
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

float calcAvg(float x,float y){
  float avg=(x+y)/2;
  return avg;
}


void startUp(){
  //ping ultrasonics twice and average the values to get (hopefully) accurate values
  float right=calcAvg(rightUltrasonic.getDistance(),rightUltrasonic.getDistance());
  float left=calcAvg(leftUltrasonic.getDistance(),leftUltrasonic.getDistance());
  float front=calcAvg(frontLeftUltrasonic.getDistance(),frontRightUltrasonic.getDistance());
  float back=calcAvg(backUltrasonic.getDistance(),backUltrasonic.getDistance());

  if(right < closeToWall && back < closeToWall){  //robot is facing downward
    turn(90);
  }
  else if(right < closeToWall && front < closeToWall){  //robot is facing backward
    turn(180);
  }
  else if(front < closeToWall && left < closeToWall){ //robot is facing upward
    turn(-90);
  }
  else{   //robot is facing the correct direction
    turn(0);
  }

  while(rightUltrasonic.getDistance() > closeToWall){   //roll forward until the first room is encountered, then kick out of function
    rollForward();
  }
}

void setup() {
  // put your setup code here, to run once:
  leftServo.attach(LEFT_SERVO_PIN);
  rightServo.attach(RIGHT_SERVO_PIN);
  extinguisher.attach(EXTINGUISHER_PIN);
  stopRobot();
  extinguisher.write(90);


  pinMode(IR_PIN_LEFT, INPUT);
  pinMode(IR_PIN_RIGHT, INPUT);

  attachInterrupt(digitalPinToInterrupt(IR_PIN_LEFT), extinguishFire, RISING);
  attachInterrupt(digitalPinToInterrupt(IR_PIN_RIGHT), extinguishFire, RISING);

  pinMode(FLAME_LED, OUTPUT);

  pinMode(MIC_LED, OUTPUT);

  pinMode(BABY_LED, OUTPUT);

  pinMode(CAMERA_LED, OUTPUT);

  pinMode(GYRO, INPUT);

  FreqCount.begin(1000); // Begin measuring sound
}

void loop() {
// put your main code here, to run repeatedly:

  if (checkingMicrophone) {   //Robot doesn't start until it hears the start frequency
    checkMicrophone();
  }

  startUp();
  extinguishFire();
  delay(100);

  /* if (usingCamera()){
    digitalWrite(CAMERA_LED, HIGH);
  } else {
    digitalWrite(CAMERA_LED, LOW);
  }

  if(detectBaby()){
    digitalWrite(BABY_LED, HIGH);
  } else {
    digitalWrite(BABY_LED, LOW);
  } */


  /* if (robotOn) {

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
  } */
}
