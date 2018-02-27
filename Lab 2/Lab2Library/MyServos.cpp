//implement in this document the functions from MyServos.h
#include "MyServos.h"
#include <Adafruit_RGBLCDShield.h>

  Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
  Servo LServo;
  Servo RServo;
  
  float LeftRPS[21];
  float RightRPS[21];
  float LeftIPS[21];
  float RightIPS[21];


void setSpeeds(int microsLeft, int microsRight){
    LServo.attach(2);
    RServo.attach(3);
    LServo.writeMicroseconds(1500 + microsLeft);
    RServo.writeMicroseconds(1500 - microsRight);
}


void calibrate(){
  lcd.begin(16, 2);
  unsigned long leftTickCount;
  unsigned long rightTickCount;
  for(int i = 0; i <= 20; i++){
    lcd.setCursor(0,0);
    lcd.print("Calibrating...");
    setSpeeds(i * 5, i * 5);
    delay(2000);
    initEncoders();
    delay(5000);
    noInterrupts();
    leftTickCount = leftTick;
    rightTickCount = rightTick;
    interrupts();
    LeftRPS[i] = (float)((leftTickCount) / 5.00)/32;
    RightRPS[i] = (float)((rightTickCount) / 5.00)/32;
    LeftIPS[i] = (float)leftTickCount * (((2.61 * 3.14)/32.00) / 5.00);
    RightIPS[i] = (float)rightTickCount * (((2.61 * 3.14)/32.00) / 5.00);
    Serial.print("LeftIPS: ");
    Serial.print(LeftIPS[i]);
    Serial.print("\n");
    Serial.print("RightIPS: ");
    Serial.print(RightIPS[i]);
    Serial.print("\n");
    resetCounts(); 
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Calibration");
  lcd.setCursor(0,1);
  lcd.print("Completed");

}

void setSpeedsRPS(float rpsLeft, float rpsRight){
  bool isLeftNegative = false;
  bool isRightNegative = false;
  int left_RPS;
  int right_RPS;
  if(rpsLeft < 0){
    rpsLeft = (-1) * rpsLeft;
    isLeftNegative = true;
  }

  if(rpsRight < 0){
    rpsRight = (-1) * rpsRight;
    isRightNegative = true;
  }
  
  // finding left RPS
  for(int i = 0; i <= 20; i++){
    if(LeftRPS[i] == rpsLeft){
      left_RPS = i * 5;
 
      break;
    }
    else if(LeftRPS[i] > rpsLeft){
    
      left_RPS = (5 * (i-1)) + 5* ((rpsLeft - LeftRPS[i-1])/(LeftRPS[i-1] + LeftRPS[i]));
      break;
    }
  }

  // finding right RPS
  for(int j = 0; j <= 20; j++){
    if(RightRPS[j] == rpsRight){
      right_RPS = j * 5;
      break;
    }
     else if(RightRPS[j] > rpsRight){
      right_RPS = (5 * (j - 1)) + 5* ((rpsRight - RightRPS[j-1])/(RightRPS[j-1] + RightRPS[j]));
      break;
    }
  }

  if(isLeftNegative){
    left_RPS = left_RPS * (-1);
  }  

  if(isRightNegative){
    right_RPS = right_RPS * (-1);
  }  
  
  setSpeeds(left_RPS, right_RPS);
}

void setSpeedsIPS(float ipsLeft, float ipsRight){
  bool isLeftNegative = false;
  bool isRightNegative = false;
  int left_IPS;
  int right_IPS;
  if(ipsLeft < 0){
    ipsLeft = (-1) * ipsLeft;
    isLeftNegative = true;
  }

  if(ipsRight < 0){
    ipsRight = (-1) * ipsRight;
    isRightNegative = true;
  }

  // finding left RPS
  for(int i = 0; i <= 20; i++){
   
    if(LeftIPS[i] == ipsLeft){
      left_IPS = i * 5;
      break;
    }
    else if(LeftIPS[i] > ipsLeft){
      left_IPS = (5 * i) + (5* (ipsLeft - LeftIPS[i-1])/(LeftIPS[i-1] + LeftIPS[i]));
      break;
    }
  }

  // finding right RPS
  for(int j = 0; j <= 20; j++){
    if(RightIPS[j] == ipsRight){
      right_IPS = j * 5;
      break;
    }
     else if(RightIPS[j] > ipsRight){
      right_IPS = (5 * j) + (5* (ipsRight - RightIPS[j-1])/(RightIPS[j-1] + RightIPS[j]));
      break;
    }
  }

  if(isLeftNegative){
    left_IPS = left_IPS * (-1);
  }  

  if(isRightNegative){
    right_IPS = right_IPS * (-1);
  }  
 
  setSpeeds(left_IPS, right_IPS);
}

void setSpeedsvw(float v, float w){
  float left;
  float right;
  float R = v / w;
  if(w >= 0){
    left = w * (R - 3.95/2.00);
    right = w * (R + 3.95 / 2.00);
  }

  if(w < 0){
    left = (-1)* w * (((-1) * R) + (3.95 / 2.00));
    right = (-1)* w * (((-1) * R) - (3.95 / 2.00));
  }

  setSpeedsIPS(left, right);
}

