#include <MyEncoders.h>
#include <MyServos.h>
#include <SShapeParams.h>
#include <Adafruit_RGBLCDShield.h>

Adafruit_RGBLCDShield sslcd = Adafruit_RGBLCDShield();

float Time = PARAM_Y;
float Radius1 = PARAM_R1;
float Radius2 = PARAM_R2;
float RequiredTime[2];
float firstHalf = (3.14 * (Radius1)); //distance with first radius
float secondHalf = (3.14 * (Radius2)); //distance with second radius
const char* erraseString  = "";
bool flag = false;

//wrote a new function to calculate how many times needed to finish each radius
void calculateTime(float totalTime, float firstRadius, float secondRadius, float reqTime[]){
  float R1Time = 0.00;
  float R2Time = 0.00;
  float totalDis = firstRadius + secondRadius;

  R1Time = (firstRadius / totalDis) * totalTime;
  R2Time = (secondRadius / totalDis) * totalTime;

  reqTime[0] = R1Time;
  reqTime[1] = R2Time;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  sslcd.begin(16, 2);
  //
  sslcd.setCursor(0,0);
  sslcd.print("Calibrating...");
  calibrate();
  setSpeeds(0,0);
  //
  sslcd.clear();
  sslcd.setCursor(0,0);
  sslcd.print("S-SHAPE");
  sslcd.setCursor(0,1);
  sslcd.print("PRESS SLT TO RUN");
  initEncoders();
  //  

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(200);
  uint8_t buttons = sslcd.readButtons();

  if(buttons & BUTTON_SELECT){
     //calculate speed, time and distance here
     calculateTime(Time, Radius1, Radius2, RequiredTime);
     float linearV = ((3.14 * Radius1)+(3.14*Radius2))/PARAM_Y; // PARAM_Y
     //float linearV1 = (3.14*Radius1)/RequiredTime[0]; //first radius
     //float linearV2 = (3.14*Radius2)/RequiredTime[1]; //second radius
     float angularV1 = (-1)*(3.14/(RequiredTime[0]/2)); //first angularV (Clockwise)
     float angularV2 = 3.14/(RequiredTime[1]/2); //second angularV (Counter-Clockwise)
     Serial.println(linearV);
     Serial.println(angularV1);
     //
    if(flag == false){
        if((linearV > LeftIPS[20] && linearV > RightIPS[20])){
          sslcd.clear();
          sslcd.setCursor(0,0);
          sslcd.print("S-SHAPE");
          sslcd.setCursor(0,1);
          sslcd.print("ERROR-PARAM HIGH");
        }else if((linearV < 0) || (linearV < 0)){
          sslcd.clear();
          sslcd.setCursor(0,0);
          sslcd.print("S-SHAPE");
          sslcd.setCursor(0,1);
          sslcd.print("ERROR-NO REVERSE");
        }else{
          sslcd.clear();
          sslcd.setCursor(0,0);
          sslcd.print("S-SHAPE -FH");
          sslcd.setCursor(0,1);
          sslcd.print("PROCEED...");
          setSpeedsvw(linearV,angularV1);      
        }    
      }else if(flag == true){
          sslcd.clear();
          sslcd.setCursor(0,0);
          sslcd.print("S-SHAPE -SH");
          sslcd.setCursor(0,1);
          sslcd.print("PROCEED...");
          setSpeedsvw(linearV, angularV2);
      }
     }
     float wheelR = (((leftTick*(2.61*3.14)/32)+(rightTick*(2.61*3.14)/32))/2);
     if((wheelR>firstHalf) && flag == false){
            setSpeeds(0,0);
            flag = true;
            initEncoders();
            sslcd.setCursor(0,0);
            sslcd.print(erraseString);
            sslcd.setCursor(0,1);
            sslcd.print(erraseString);
            sslcd.setCursor(0,0);
            sslcd.print("S-SHAPE -SH");
            sslcd.setCursor(0,1);
            sslcd.print("PRESS SLT TO RUN");
      }    
    if((wheelR>secondHalf) && flag == true){
        flag == false;
        sslcd.clear();
        sslcd.setCursor(0,0);
        sslcd.print("S-SHAPE");
        sslcd.setCursor(0,1);
        sslcd.print("COMPLETED");
        setSpeeds(0,0);
        initEncoders();
      }

}
