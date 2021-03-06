#include <MyServos.h>
#include <MyEncoders.h>
#include <MySharpSensor.h>
#include <Adafruit_RGBLCDShield.h>

float frontError;
float kP = 0.6;
float DesiredDistance = 5.00; // Distance we want robot to keep from wall
float rightDistance, frontDistance;
bool turnFlag = 0;
Adafruit_RGBLCDShield _lcd = Adafruit_RGBLCDShield();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  _lcd.begin(16,2);
  _lcd.setCursor(0,0);

  //_lcd.print("WALL FOLLOWING");
}

void loop() {
  takeNewMeasurement(SSFRONT);
  frontDistance = getCombinedDistance(SSFRONT);
  
  takeNewMeasurement(SRIGHT);
  rightDistance = getCombinedDistance(SRIGHT);

  frontError = frontDistance - DesiredDistance;
  frontError *= kP;

  int checkFront = outOfRange[0];
  int checkRight = outOfRange[2];
//  _lcd.clear();
//  _lcd.setCursor(0,0);
//  _lcd.print(checkFront);
//  _lcd.setCursor(3,0);
//   _lcd.print(frontDistance);
//  _lcd.setCursor(0,1);
//  _lcd.print(checkRight);
//  _lcd.setCursor(3,1);
//  _lcd.print(rightDistance);
//
//   _lcd.setCursor(9,1);
//  _lcd.print(frontError);
  

////if Front is Empty:
//if(frontDistance < 0.3 && checkFront == 1){
//  //if there is right Wall:
//  if(checkRight == 0 && rightDistance < 10){
//    //Go Straight
//    setSpeeds(40, 40);
//    //Adjust Distance if too close
//    if(rightDistance < 4.80){
//      setSpeeds(50, 70);
//    }
//    //Adjust Distance if too far
//    else if(rightDistance > 5.80){
//      setSpeeds(70, 50);
//    }
//  }
//  //if Front & Right is Empty
//  else if(checkRight == 1){
//    //turn hard Right
//    setSpeeds(40, 13);
//  }else if(checkRight == 0 && rightDistance > 6){
//    //turn hard Right (self correction)
//    setSpeeds(42,13);
//  }
//  
//}
////if there is front Wall
//else{
//  //if there is right Wall:
//  if(checkRight == 0 && rightDistance < 10){
//    //go Straight
//    setSpeeds(40, 40);
//    //Adjust Distance if too close
//    if(rightDistance < 4.80){
//      setSpeeds(50, 70);
//    }
//    //Adjust Distance if too far
//    else if(rightDistance > 5.80){
//      setSpeeds(70, 50);
//    }
//    //if too close to the front Wall
//    if(frontDistance < 11){
//      //turn hard left
//      setSpeeds(18, 38);
//    }else if(frontDistance > 11 && rightDistance < 6){
//        //turn hard left correction
//        setSpeeds(18,43);
//     }
//  }
//  //if there is no Right Wall:
//  else if(checkRight == 1){
//    //and too close to the front Wall
//    if(frontDistance < 11){
//      //turn hard left
//      setSpeeds(18, 38);
//    }
//  }
//}
//delay(20);  

//Saturation Correction
   // if(frontError > 2.99){
   //   frontError = 5.89;
   // }
   // if(frontError < -2.99){
   //   frontError = -2.99;
   // }

//if Front is Empty:
if(frontDistance < 0.3 && checkFront == 1){
  //if there is right Wall:
  if(checkRight == 0 && rightDistance < 10){
    //Go Straight
    if(frontError < 0){
      frontError *= -1;
    }
    setSpeedsIPS(frontError, frontError);
    //Adjust Distance if too close
    //for Curved Wall
    if(rightDistance < 4.80){
      setSpeedsIPS(frontError, frontError+1.2);
    }
    //Adjust Distance if too far
    else if(rightDistance > 5.80){
      setSpeedsIPS(frontError+1.2, frontError);  
    }  
  
  }
  //if Front & Right is Empty
  else if(checkRight == 1){
    //turn hard Right
    
    setSpeeds(40, 13);
    
  }else if(checkRight == 0 && rightDistance > 6){
    //turn hard Right (self correction)
    setSpeeds(42,13);
  }
  
}
//if there is front Wall
else{
  //if there is right Wall:
  if(checkRight == 0 && rightDistance < 10){
    //go Straight
    setSpeedsIPS(frontError, frontError);
    //Adjust Distance if too close
    if(rightDistance < 5.00){
      setSpeedsIPS(frontError, frontError+1.1);
    }
    //Adjust Distance if too far
    else if(rightDistance > 5.50){
      setSpeedsIPS(frontError+1.1, frontError);
    }
    //if too close to the front Wall
    if(frontError < 3.5){
      //turn hard left
      setSpeeds(18, 38);
    }else if(frontDistance > 11 && rightDistance < 8){
        //turn hard left correction
        setSpeeds(18,43);
     }
  }
  //if there is no Right Wall:
  else if(checkRight == 1){
    //setSpeedsIPS(frontError, frontError);
    //and too close to the front Wall
    if(frontError < 3.5){
      //turn hard left
      setSpeeds(18, 38);
    }
  }
}
delay(20); 

}
