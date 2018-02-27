//implement in this document the functions from MyEncoders.h
#include "MyEncoders.h"
#include <PinChangeInt.h>
 unsigned long leftTick = 0;
 unsigned long rightTick = 0;

 float leftPrevTime = 0.00;
 float leftLatestTime = 0.00;
 float rightPrevTime = 0.00;
 float rightLatestTime = 0.00;
 float leftRPS;
 float rightRPS;

 //ENCODERS
 int leftEncPin = 10;
 int rightEncPin = 11;

void resetCounts(){
  leftTick = 0;  // Left tick
  rightTick = 0;  // Right tick
}

void getCounts(unsigned long counts[]){
  counts[0] = leftTick;
  counts[1] = rightTick;
}

void getSpeeds(float speeds[]){
  
  leftRPS = ((float)(1.00/32.00)) / ((leftLatestTime - leftPrevTime)) * 1000;
  rightRPS = ((float)(1.00/32.00)) / ((rightLatestTime - rightPrevTime)) * 1000;
  speeds[0] = leftRPS;
  speeds[1] = rightRPS;
}

void leftFalling(){
  leftTick++;
  leftPrevTime = leftLatestTime;
  leftLatestTime = (float)millis();
}
void rightFalling(){
  rightTick++;
  rightPrevTime = rightLatestTime;
  rightLatestTime = (float)millis();
}
void initEncoders(){
  resetCounts();
  
  //SET ENCODERS
  pinMode(leftEncPin, INPUT_PULLUP);
  pinMode(rightEncPin, INPUT_PULLUP);
  PCintPort::attachInterrupt(leftEncPin, &leftFalling ,FALLING); 
  PCintPort::attachInterrupt(rightEncPin, &rightFalling ,FALLING); 
}

