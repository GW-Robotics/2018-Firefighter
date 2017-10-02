#include <Servo.h>

#include <Ultrasonic.h>

#define LEFT_SERVO_PIN  4
#define RIGHT_SERVO_PIN 5
#define IR_PIN 6
#define EXTINGUISHER_PIN 7

#define FRONT_US_ECHO   2
#define FRONT_US_TRIG   3

Servo leftServo;
Servo rightServo;
Servo extinguisher;

Ultrasonic frontUltrasonic(FRONT_US_ECHO, FRONT_US_TRIG, true);

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
  if (detectFire()) {
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
  }
}

void setup() {
  // put your setup code here, to run once:
  leftServo.attach(LEFT_SERVO_PIN);
  rightServo.attach(RIGHT_SERVO_PIN);
  extinguisher.attach(EXTINGUISHER_PIN);

  pinMode(IR_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (frontUltrasonic.getDistance() > 3) {
    moveForward();
  } else {
    moveBackward();
  }
  
  extinguishFire();
  
  delay(100);
}
