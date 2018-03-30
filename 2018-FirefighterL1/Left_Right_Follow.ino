void levelOneNav() {
  int followDirection = 0; //left follow or right follow
  int lowerleftroomdistance = 10; //distance to activate Rick's Code
  double diagonalMove = 5; //how far the robot should move for its diagonal path
  double lateralMove = 5; //how far the robot should move to exit the lower right room

  while(followDirection < 7)
  {
    if (frontRightUltrasonic.getDistance() > closeToWall && rightUltrasonic.getDistance() < closeToWall)
    {
      moveSlightLeft();
      delay(500);         //move left diagnal
      while(rightUltrasonic.getDistance() > closeToWall) {
        moveSlightRight();
      }
      delay(500);    //move diagnol towards the wall until your close to the wall
    }

    else if(rightUltrasonic.getDistance() > closeToWall && frontRightUltrasonic.getDistance() > closeToWall)
    {
      turn(-90);    //if there is no right wall turn right
      delay(500);
      followDirection = followDirection +1;
    }

    else if(rightUltrasonic.getDistance() < closeToWall && frontRightUltrasonic.getDistance() < closeToWall)
    {
      turn(90);
      delay(500);
      followDirection = followDirection + 1;
    }

    else followDirection = followDirection;
  }

  while(followDirection >= 7)
  {
    if (frontLeftUltrasonic.getDistance() > closeToWall && leftUltrasonic.getDistance() < closeToWall)
    {
      moveSlightRight();
      delay(500);    //move left diagnal
      while(leftUltrasonic.getDistance() < closeToWall){
        moveSlightLeft();
      }
      delay(500);
    }

    else if (leftUltrasonic.getDistance() > closeToWall)
    {
      turn(90);    //if there is no left wall turn left
      delay(500);
      followDirection = followDirection + 1;
    }
    else if (frontRightUltrasonic.getDistance() < lowerleftroomdistance)
    {
      followDirection = followDirection + 1;
    }
  }

  while(followDirection = 8)
  {
    //void lowerRightRoom(){
    turn(0); //turn(0) is a way to reset gyro measurements

    turn(-20); //turn the robot 45, but since it's so close to the wall, this needs to happen gradually
    rollForward();
    delay(1000);
    stopRobot();
    turn(0);
    turn(-25);

    moveForward(diagonalMove);

    turn(0);
    turn(-90);
    delay(1000);  //see if there's fire in the upper corner
    turn(180);
    delay(1000);  //see if there's fire in the lower corner
    turn(0);
    turn(-45);

    while(frontRightUltrasonic.getDistance() > closeToWall && frontLeftUltrasonic.getDistance() > closeToWall){ //roll forward until the robot gets close to the lower wall
      rollForward();
    }
    stopRobot();

    turn(-90);  //turn right towards the exit of the room
    moveForward(lateralMove);
    turn(0);

  }

  while(followDirection >= 9)
  {
    if (frontLeftUltrasonic.getDistance() > closeToWall && leftUltrasonic.getDistance() < closeToWall)
    {
      moveSlightRight();
      delay(500);    //move left diagnal
      while(leftUltrasonic.getDistance() < closeToWall){
        moveSlightLeft();
      }
      delay(500);
    }

    else if (leftUltrasonic.getDistance() > closeToWall && frontLeftUltrasonic.getDistance() > closeToWall)
    {
      turn(90);
      delay(500);
      followDirection = followDirection + 1;
    }
    else if (leftUltrasonic.getDistance() < closeToWall && frontLeftUltrasonic.getDistance() < closeToWall)
    {
      turn(-90);
      delay(500);
      followDirection = followDirection + 1;
    }
  }
}
