#include <ForwardParams.h>
#include <MyEncoders.h>
#include <MyServos.h>
#include <Adafruit_RGBLCDShield.h>

Adafruit_RGBLCDShield fwlcd = Adafruit_RGBLCDShield();


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  fwlcd.begin(16, 2);
  //
  fwlcd.setCursor(0,0);
  fwlcd.print("Calibrating...");
  calibrate();
  setSpeeds(0,0);
  //
  fwlcd.clear();
  fwlcd.setCursor(0,0);
  fwlcd.print("FORWARD");
  fwlcd.setCursor(0,1);
  fwlcd.print("PRESS SLT TO RUN");
  initEncoders();
  //  

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(200);
  uint8_t buttons = fwlcd.readButtons();

  if(buttons & BUTTON_SELECT){
    float checkSpeed = PARAM_X/PARAM_Y;
    if(checkSpeed > LeftIPS[10] || checkSpeed > RightIPS[10]){
      fwlcd.clear();
      fwlcd.setCursor(0,0);
      fwlcd.print("FORWARD");
      fwlcd.setCursor(0,1);
      fwlcd.print("ERROR-PARAM HIGH");
    }else if(checkSpeed < 0){
      fwlcd.clear();
      fwlcd.setCursor(0,0);
      fwlcd.print("FORWARD");
      fwlcd.setCursor(0,1);
      fwlcd.print("ERROR-NO REVERSE");
    }else{
      fwlcd.clear();
      fwlcd.setCursor(0,0);
      fwlcd.print("FORWARD");
      fwlcd.setCursor(0,1);
      fwlcd.print("PROCEED...");
      setSpeedsIPS(checkSpeed,checkSpeed);
    }
  }

  //STOP if the robot completed target distance.
  int leftDis = leftTick * ((2.61*3.14)/32);
  int rightDis = rightTick * ((2.61*3.14)/32);
  if(leftDis >= PARAM_X || rightDis >= PARAM_X){
    fwlcd.clear();
    fwlcd.setCursor(0,0);
    fwlcd.print("FORWARD");
    fwlcd.setCursor(0,1);
    fwlcd.print("COMPLETED");
    setSpeeds(0,0);
    initEncoders();
  }
  
}
