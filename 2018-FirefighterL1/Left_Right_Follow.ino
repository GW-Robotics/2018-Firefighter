int followDirection = 0; //left follow or right follow
int lowerleftroomdistance = 10; //distance to activate Rick's Code
double diagonalMove = 26; //how far the robot should move for its diagonal path
double lateralMove = 23.875; //how far the robot should move to exit the lower right room

void upperRightRoom()
{
  if(!dog1){
    rollForward();
    while(frontRightUltrasonic.getDistance() > closeToWall && rightUltrasonic.getDistance() < closeToWall){
      delay(50);
    }
    stopRobot();

    flashLED(MIC_LED, 500, 3);

    right90();    // if there is no right wall turn right
    moveForward(8);
    turn(30);
    turn(-210);

    flashLED(MIC_LED, 500, 4);

    moveForward(8);
    right90();
    rollForward();
    while(frontRightUltrasonic.getDistance() > closeToWall){
      delay(50);
    }
    stopRobot();
    right90();
    stopRobot();

    flashLED(MIC_LED, 500, 5);
  }else{
    rollForward();
    while(frontRightUltrasonic.getDistance() > closeToWall && leftUltrasonic.getDistance() < closeToWall){
      delay(50);
    }
    stopRobot();
    moveForward(2);
    left90();
    moveForward(5);
    rollForward();
    while(frontRightUltrasonic.getDistance() > closeToWall && leftUltrasonic.getDistance() < closeToWall){
      delay(50);
    }
    stopRobot();
    moveForward(3);
    right90();
  }
}

void secondDogCheck() { //robot is facing downward where the second dog could potentially be
  double dogDistance = 3;
  if(frontRightUltrasonic.getDistance() < dogDistance){
    dog2 = true;
  }
  delay(50);
}

void lowerRightRoom(){
  turn(-45);

  moveForward(diagonalMove);

  right90();
  delay(1000);  //see if there's fire in the upper corner
  turn(180);
  delay(1000);  //see if there's fire in the lower corner
  turn(-45);

  while(frontRightUltrasonic.getDistance() > closeToWall){ //roll forward until the robot gets close to the lower wall
    rollForward();
    delay(50);
  }
  stopRobot();

  right90();  //turn right towards the exit of the room
  moveForward(lateralMove);
  turn(0);
}

void foreverLeftFollow() {
  while (true) {
    while(frontRightUltrasonic.getDistance() > closeToWall){
      rollForward();
      delay(400);
      stopRobot();
      if(leftUltrasonic.getDistance() > (closeToWall/2)){
        moveSlightLeft();
      }
      delay(400);
    }
    right90();
  }
}

void levelOneNav() {

  upperRightRoom();
  if(!dog1){
    secondDogCheck();
  }

  if(dog2) {
    right90(); //turn towards start
    moveForward(60); //move back to start
    left90(); //turn downward
    moveForward(36);  //move down past upperRightRoom
    left90(); //turn left
    moveForward(60); //move back into position for lowerRightRoom
    right90();
    rollForward();
    while(rightUltrasonic.getDistance() < closeToWall) {
      delay(50);
    }
    stopRobot();
    lowerRightRoom();
  } else {
    rollForward();
    while (rightUltrasonic.getDistance() < closeToWall) {
      delay(50);
    }
    stopRobot();
    lowerRightRoom();
    foreverLeftFollow();
  }
  // while(followDirection >= 7)
  // {
  //   if (frontRightUltrasonic.getDistance() > closeToWall && leftUltrasonic.getDistance() < closeToWall)
  //   {
  //     moveSlightRight();
  //     delay(500);    //move left diagnal
  //     while(leftUltrasonic.getDistance() < closeToWall){
  //       moveSlightLeft();
  //     }
  //     delay(500);
  //   }
  //
  //   else if (leftUltrasonic.getDistance() > closeToWall)
  //   {
  //     turn(90);    // if there is no left wall turn left
  //     delay(500);
  //     followDirection = followDirection + 1;
  //   }
  //   else if (frontRightUltrasonic.getDistance() < lowerleftroomdistance)
  //   {
  //     followDirection = followDirection + 1;
  //   }
  // }

  //previously, this was where the lowerRightRoom code tripped

//   while(followDirection >= 9)
//   {
//     if (frontRightUltrasonic.getDistance() > closeToWall && leftUltrasonic.getDistance() < closeToWall)
//     {
//       moveSlightRight();
//       delay(500);    //move left diagnal
//       while(leftUltrasonic.getDistance() < closeToWall){
//         moveSlightLeft();
//       }
//       delay(500);
//     }
//
//     else if (leftUltrasonic.getDistance() > closeToWall && frontRightUltrasonic.getDistance() > closeToWall)
//     {
//       turn(90);
//       delay(500);
//       followDirection = followDirection + 1;
//     }
//     else if (leftUltrasonic.getDistance() < closeToWall && frontRightUltrasonic.getDistance() < closeToWall)
//     {
//       turn(-90);
//       delay(500);
//       followDirection = followDirection + 1;
//     }
//   }
 }
