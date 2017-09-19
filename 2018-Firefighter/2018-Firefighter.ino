#include <Servo.h>

#include <Ultrasonic.h>

#define LEFT_SERVO_PIN  4
#define RIGHT_SERVO_PIN 5

#define FRONT_US_ECHO   2
#define FRONT_US_TRIG   3

Servo leftServo;
Servo rightServo;

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

void setup() {
  // put your setup code here, to run once:
  leftServo.attach(LEFT_SERVO_PIN);
  rightServo.attach(RIGHT_SERVO_PIN);

  // pinMode(5, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // int value = digitalRead(5);
  
  if (frontUltrasonic.getDistance() > 3) {
    moveForward();
  } else {
    moveBackward();
  }
  
  delay(100);
}
