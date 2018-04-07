void rightTurn(int delay){
  rightMotor.set(rightSpeed);
  delay(delay);
  rightMotor.set(0);
}

void leftTurn(int delay){
  leftMotor.set(leftSpeed);
  delay(delay);
  leftMotor.set(0);
}
