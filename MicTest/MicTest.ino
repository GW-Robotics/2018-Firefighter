#include "FreqCount.h"
#define LED_PIN_1 9
#define LED_PIN_2 11

unsigned long freqCount;
#define LOW_START 3000
#define HIGH_START  4000
bool robotOn = false;
bool checkingMicrophone = true;
bool hearingStartSound = false;

void checkMicrophone() {
  // Measure sound:
  if (FreqCount.available()) {
    freqCount = FreqCount.read();
    Serial.println(String(freqCount);
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

void setup() {
  // put your setup code here, to run once:
  FreqCount.begin(1000);
  Serial.begin(9600);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (checkingMicrophone) {   //Robot doesn't start until it hears the start frequency
    checkMicrophone();
  }
  digitalWrite(LED_PIN_1, HIGH);
  digitalWrite(LED_PIN_2, HIGH);
  delay(500);
  digitalWrite(LED_PIN_1, LOW);
  digitalWrite(LED_PIN_2, LOW);
  delay(500);
}
