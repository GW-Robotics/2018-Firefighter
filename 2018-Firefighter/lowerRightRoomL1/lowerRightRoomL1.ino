void lowerRightRoom(){
  turn(0); //turn(0) is a way to reset gyro measurements
  
  turn(-20); //turn the robot 45, but since it's so close to the wall, this needs to happen gradually
  moveForward();
  delay(1000);
  stopRobot();
  turn(0);
  turn(-25);

  moveForward();  //CHANGE THIS BLOCK WHEN WE HAVE A BETTER MOVE FUNCTION
  delay(5000);
  stopRobot();
  
  turn(0);
  turn(-90);
  delay(1000);  //see if there's fire in the upper corner
  turn(180);
  delay(1000);  //see if there's fire in the lower corner
  turn(0);
  turn(-45);

  while(frontRightUltrasonic.getDistance() > closeToWall && frontLeftUltrasonic.getDistance() > closeToWall){ //roll forward until the robot gets close to the lower wall
    moveForward();
  }
  stopRobot();

  turn(-90);  //turn right towards the exit of the room
  moveForward();  //AGAIN, CHANGE THIS WHEN WE HAVE A BETTER MOVE FUNCTION
  delay(3000);
  stopRobot();
  turn(0);
}

