void rightTurn(int timeDelay){
  rightMotor.set(rightSpeed);
  delay(timeDelay);
  rightMotor.set(0);
}

void leftTurn(int timeDelay){
  leftMotor.set(leftSpeed);
  delay(timeDelay);
  leftMotor.set(0);
}
