#include <Servo.h>
#include <WemosInit.h>
#define rightpin D8
#define leftpin D9

Servo right, left;
int leftSensor = ultrasonicPing(D7,D6);
int frontSensor = ultrasonicPing(D2,D3);
int rightSensor = ultrasonicPing(D5,D4);
int state = 0;

/*
 * time = milli(); is a function that reads the time
 * currentTime = milli() - time;
 */

//right is right wheel
//left is left wheel
//D2 and D3 for the front sensor
//D6 and D7 for side sensor

void setup()
{
  right.attach(rightpin);
  left.attach(leftpin);
  
  Serial.begin(115200);

  //right sensor
  pinMode(D4,INPUT);//D4 is echo
  pinMode(D5,OUTPUT);//D5 is trig

  //front sensor
  pinMode(D2,OUTPUT);//D2 is trig
  pinMode(D3,INPUT);//D3 is echo

  //left sensor
  pinMode(D7, OUTPUT);//D7 is trig
  pinMode(D6, INPUT);//D6 is echo

  //stops the motors
  right.write(90);
  left.write(90);
  delay(11000);
}

void leftTurn(int time){
    right.write(90);
    left.write(90);//stops motors again
    left.write(102);
    right.write(83);
    delay(time); 
}

void rightTurn(int time){
   right.write(90);//right
   left.write(80);//left
   delay(time);
}

void followWallLeftForward(int distance){
int leftSensor = ultrasonicPing(D7,D6);
  right.write(80);
  left.write(81);
  
  if(leftSensor <= distance){
    right.write(85);
    delay(10);
  }
  
  if(leftSensor >= distance){
    left.write(83);
    delay(10);
  }
}

void followWallRightForward(int distance){

int rightSensor = ultrasonicPing(D5,D4);
 
  right.write(80);
  left.write(81);
  
  if(rightSensor <= distance){
    left.write(83);
    delay(10);
  }
  
  if(rightSensor >= distance){
    right.write(85);
    delay(10);
  }
}

void loop() {
int leftSensor = ultrasonicPing(D7,D6);
int frontSensor = ultrasonicPing(D2,D3);
int rightSensor = ultrasonicPing(D5,D4);
delay(100);

    //Serial.println(frontSensor);

//follows the wall, starts at position 
  if (state == 0){
  followWallRightForward(540);
  if (frontSensor <= 700){state = 1;}
  }
  
  else if (state == 1) {
    leftTurn(1000);
    right.write(90);
    left.write(90);
    delay(500);
    state = 2;
  }

  else if (state == 2){
    followWallRightForward(1100);
    if(frontSensor <= 2400 ) { //was 2300
      right.write(90);
      left.write(90);
      state = 3;
      }
  }
  
  else if (state == 3){
    rightTurn(1000);
    state = 4;
  }

//hits  B and C
  else if (state == 4){
    followWallLeftForward(2350);
    delay(700);
    right.write(105);
    left.write(107);
    delay(2500);

   /*right.write(107);
    left.write(105);
    delay(1300);*/
    
    right.write(90);
    left.write(90);
    delay(500);
    state = 6;
  } 
  
  else if (state == 6) {
   followWallLeftForward(2350);
   if (frontSensor <= 760) 
    state = 7;
  }

  else if (state == 7){
    rightTurn(1000);
    right.write(90);
    left.write(90);
    delay(500);
    state = 8;
  }
  
   else if (state == 8){
    followWallLeftForward(1100);
    if (frontSensor <= 2000) 
      state = 9;
  }

//hits D and A
  else if (state == 9) {
    leftTurn(700);
    right.write(80);
    left.write(81);
    delay(600);
    
    right.write(90);
    left.write(90);
    delay(500);
    
    right.write(105);
    left.write(107);
    delay(2500);
   
    right.write(90);
    left.write(90);
    delay(500);
    state = 10;
  }

  else if (state == 10) {
    rightTurn(900);
    followWallRightForward(630);
    delay(700);
    
      right.write(90);
      left.write(90);
      delay(15000);
  }

}
