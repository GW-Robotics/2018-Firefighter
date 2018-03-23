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
  // run Rick's Code 
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

  
