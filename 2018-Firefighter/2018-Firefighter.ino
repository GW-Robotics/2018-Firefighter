#include <Servo.h>

#include <Ultrasonic.h>

#define LEFT_SERVO_PIN  4
#define RIGHT_SERVO_PIN 5
#define IR_PIN 6
#define EXTINGUISHER_PIN 7
#define MIC_PIN 43 
#define FLAME_LED 9
#define MIC_LED 11
#define BABY_LED 17
#define CAMERA 15
#define CAMERA_LED 16

#define FRONT_US_ECHO   2
#define FRONT_US_TRIG   3
#define LEFT_US_ECHO   18
#define LEFT_US_TRIG   19

Servo leftServo;
Servo rightServo;
Servo extinguisher;

Ultrasonic frontUltrasonic(FRONT_US_ECHO, FRONT_US_TRIG, true);
Ultrasonic leftUltrasonic(LEFT_US_ECHO, LEFT_US_TRIG, true);

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

void extinguishFire(){
  while (detectFire()) {
    if (frontUltrasonic.getDistance() > 3) {
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
  int detectSound(){return 0;}
  int detectBaby(){return 0;}
  int usingCamera(){return 0;)
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
  
  pinMode(MIC_PIN, INPUT);
  pinMode(MIC_LED, OUTPUT);
  
  pinMode(BABY_LED, OUTPUT);
  
  pinMode(CAMERA_LED, OUTPUT);
}

void loop() {
// put your main code here, to run repeatedly:
  
  extinguishFire();
  
  delay(100);

  if (detectfire()){
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
  
  if(detectSound()){
    digitalWrite(MIC_LED, HIGH);
  } else {
    digitalWrite(MIC_LED, LOW);
  }
 } 
}
  
