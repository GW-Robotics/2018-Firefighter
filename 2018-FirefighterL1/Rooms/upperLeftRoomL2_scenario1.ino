void upperLeftRoomL2_scenario1(){
  turn(45);
  moveFoward(upperLeftLevel2_diagonalLength/2);
  turn(-90);
  delay(1000); //see if there's fire in the upperLeft corner of the room
  turn(180);
  delay(1000); //see if there's fire in the bottomRight corner of the room
  turn(-135); //face the upper wall now
  while(frontRightUltrasonic.getDistance() > closeToWall && frontLeftUltrasonic.getDistance() > closeToWall){ //roll forward until the robot gets close to the upper wall
    rollForward();
  }
  stopRobot();
  
  turn(90) //turn right towards the exit of the room
  moveFoward(lateralMove);
  turn(0); //to make sure robot is oriented after the move
}