followdirection = 0; //left follow or right follow 
lowerleftroomdistance = 10; //distance to activate Rick's Code 

while(followdirection < 7)
{
  if (frontultrasonic.getdistance() > 2 && rightultrasonic.getdistance() < 2)
  {
    moveslightleft();
    delay(500);         //move left diagnal
    moveslightright().wait(rightultrasonic.getdistance() < 2);
    delay(500);    //move diagnol towards the wall until your close to the wall
  }

  else if(rightultrasonic.getdistance() > 2 && frontultrasonic.getdistance() > 2)
  {
    turn(-90);    //if there is no right wall turn right
    delay(500);
    followdirection = followdirection +1;
  }

  else if(rightultrasonic.getdistance() < 2 && frontultrasonic.getdistance() < 2)
  {
    turn(90);
    delay(500)
    followdirection = followdirection + 1;
  }

  else followdirection = followdirection;
}

while(followdirection >= 7) 
{
  if (frontultrasonic.getdistance() > closeToWall && lefttultrasonic.getdistance() < closeToWall)
  {
    moveslightright();
    delay(500);    //move left diagnal
    moveslightleft().wait(leftultrasonic.getdistance() < closeToWall);
    delay(500);
  }
  
  else if (leftultrasonic.getdistance() > 2)
  {
    moveright();    //if there is no left wall turn left
    delay(500);
    followdirection = followdirection + 1;
  }
  else if (frontultrasonic.getdistance() < lowerleftroomdistance)
  {
    followdirection = followdirection + 1;
  }
}

while(followdirection = 8)
{
  void lowerRightRoom(){
  turn(0); //turn(0) is a way to reset gyro measurements
  
  turn(-20); //turn the robot 45, but since it's so close to the wall, this needs to happen gradually
  moveForward();
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

}

while(followdirection >= 9) 
{
  if (frontultrasonic.getdistance() > closeToWall && lefttultrasonic.getdistance() < closeToWall)
  {
    moveslightright();
    delay(500);    //move left diagnal
    moveslightleft().wait(leftultrasonic.getdistance() < closeToWall);
    delay(500);
  }
  
  else if (leftultrasonic.getdistance() > 2 && frontultrasonic.getdistance() > 2)
  {
    turn(90);    
    delay(500);
    followdirection = followdirection + 1;
  }
  else if (leftultrasonic.getdistance() < 2 && frontultrasonic.getdistance() < 2)
  {
    turn(-90);   
    delay(500);
    followdirection = followdirection + 1;
  }
}

  
