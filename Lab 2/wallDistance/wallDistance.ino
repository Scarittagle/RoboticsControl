#include <MyServos.h>
#include <MyEncoders.h>
#include <MySharpSensor.h>
#include <Adafruit_RGBLCDShield.h>


float Error;
float OutputDistance;
float DesiredDistance = 5.00;
float kP = 5.0; //Proportional Gain
bool firstRunFlag = true;
bool errorReachedFlag = false;
Adafruit_RGBLCDShield _lcd = Adafruit_RGBLCDShield();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
 
  _lcd.begin(16,2);
  _lcd.setCursor(0,0);
  _lcd.print("DESIRED: ");
  _lcd.print(DesiredDistance);
  _lcd.setCursor(0,1);
  

  setSpeeds(0,0);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  takeNewMeasurement(SSFRONT);
  OutputDistance = getCombinedDistance(SSFRONT);
  
  Error = OutputDistance - DesiredDistance;
  
  // Saturation
  Error *= kP;
  
  //Serial.print("Error: ");
  //Serial.println(Error);
  //Serial.print("Average");
  //Serial.print(OutputDistance);

    if(Error > 5.89){
      Error = 5.89;
    }
    if(Error < -5.89){
      Error = -5.89;
    }
  //if(errorReachedFlag == false){
    setSpeedsIPS(Error, Error);
 // }
    
  // First run always outputs 0, so ignore
 
  /*if((int)Error == 0){
    firstRunFlag = false;
  } 
  Serial.println(firstRunFlag);
  if((Error < .40 || Error > -.40) && firstRunFlag == false){
    setSpeeds(0,0);  
    errorReachedFlag = true;
  }*/
  delay(20);
  
  
}
