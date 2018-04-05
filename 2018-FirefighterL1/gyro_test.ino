

void setup_test() {
  setup_gyro();
}

void loop_test() {
  float yaw = getRotation();
  Serial.println(String(yaw));

  delay(50);
}
