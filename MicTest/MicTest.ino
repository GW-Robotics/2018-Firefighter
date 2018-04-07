#include "FreqCount.h"
#define LED_PIN_1 30
#define LED_PIN_2 31

unsigned long freqCount;
#define LOW_START 3000
#define HIGH_START  4000

long getFreqCount() {
  return freqCount;
}

void checkMicrophone() {
  //bool robotOn = false;
  //bool checkingMicrophone = true;
  //bool hearingStartSound = false;

  // Measure sound:
  while (true) {
    if (FreqCount.available()) {
      freqCount = FreqCount.read();
      Serial.println(String(getFreqCount()));
    } else {
      freqCount = 0;
    }

    // If the sound frequency is within start sound bounds, turn on robot:
    if (LOW_START < freqCount && freqCount < HIGH_START) {
      //robotOn = true; // Set the robot to on
      break;
    //   hearingStartSound = true;
    // } else {
    //   hearingStartSound = false;
    //   if (robotOn) {
    //     checkingMicrophone = false;
    //     FreqCount.end();
    //   }
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  FreqCount.begin(1000);
  Serial.begin(9600);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);

  // Hold robot in setup state until microphone is found
  checkMicrophone();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_PIN_1, HIGH);
  digitalWrite(LED_PIN_2, HIGH);
  delay(500);
  digitalWrite(LED_PIN_1, LOW);
  digitalWrite(LED_PIN_2, LOW);
  delay(500);
}
