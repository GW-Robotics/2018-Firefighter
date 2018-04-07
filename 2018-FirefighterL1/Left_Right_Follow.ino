void upperRightRoom()
{
  if (frontRightUltrasonic.getDistance() > closeToWall && rightUltrasonic.getDistance() < closeToWall)
  {
    moveSlightLeft();
    delay(500);         // move left diagonal
    while(rightUltrasonic.getDistance() > closeToWall) {
      moveSlightRight();
    }
    delay(500);    // move diagnol towards the wall until your close to the wall
  }
  else if(rightUltrasonic.getDistance() > closeToWall && frontRightUltrasonic.getDistance() > closeToWall)
  {
    turn(-90);    // if there is no right wall turn right
    moveForward(4);
    turn(30);
    turn(-210);
    moveForward(4);
    turn(-90);
    rollForward();
    while(frontRightUltrasonic.getDistance() > closeToWall){
      delay(50);
    }
    turn(-90);
    stopRobot();
    delay(500);
  }
}

void secondDogCheck() { //robot is facing downward where the second dog could potentially be
  double dogDistance = 3;
  if(frontRightUltrasonic.getDistance() < dogDistance){
    dog2 = true;
  }
}

void levelOneNav() {
  int followDirection = 0; //left follow or right follow
  int lowerleftroomdistance = 10; //distance to activate Rick's Code
  double diagonalMove = 5; //how far the robot should move for its diagonal path
  double lateralMove = 5; //how far the robot should move to exit the lower right room

  upperRightRoom();
  secondDogCheck();

  if(dog2){
    //turn around and get to the lower right room the long way
  } else {
    //proceed forward and get to the lower right room the short way
  }
  while(followDirection >= 7)
  {
    if (frontRightUltrasonic.getDistance() > closeToWall && leftUltrasonic.getDistance() < closeToWall)
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
      turn(90);    // if there is no left wall turn left
      delay(500);
      followDirection = followDirection + 1;
    }
    else if (frontRightUltrasonic.getDistance() < lowerleftroomdistance)
    {
      followDirection = followDirection + 1;
    }
  }

  while(followDirection == 8)
  {
    //void lowerRightRoom(){
    //ADD TURN(0) TO MOVE FUNCTION

    turn(-45);

    //moveForward(diagonalMove);  //this function is located on Alex's laptop, which is currently dead

    turn(-90);
    delay(1000);  //see if there's fire in the upper corner
    turn(180);
    delay(1000);  //see if there's fire in the lower corner
    turn(-45);

    while(frontRightUltrasonic.getDistance() > closeToWall){ //roll forward until the robot gets close to the lower wall
      rollForward();
    }
    stopRobot();

    turn(-90);  //turn right towards the exit of the room
    //moveForward(lateralMove); //see above
    turn(0);

  }

  while(followDirection >= 9)
  {
    if (frontRightUltrasonic.getDistance() > closeToWall && leftUltrasonic.getDistance() < closeToWall)
    {
      moveSlightRight();
      delay(500);    //move left diagnal
      while(leftUltrasonic.getDistance() < closeToWall){
        moveSlightLeft();
      }
      delay(500);
    }

    else if (leftUltrasonic.getDistance() > closeToWall && frontRightUltrasonic.getDistance() > closeToWall)
    {
      turn(90);
      delay(500);
      followDirection = followDirection + 1;
    }
    else if (leftUltrasonic.getDistance() < closeToWall && frontRightUltrasonic.getDistance() < closeToWall)
    {
      turn(-90);
      delay(500);
      followDirection = followDirection + 1;
    }
  }
}
