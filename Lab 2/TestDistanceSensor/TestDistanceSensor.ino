//#include <MyEncoders.h>
#include <MyServos.h>
#include <MySharpSensor.h>
#include <Adafruit_RGBLCDShield.h>

Adafruit_RGBLCDShield fwlcd = Adafruit_RGBLCDShield();
int val = 0;

void setup() {
  // put your setup code here, to run once:
    // put your setup code here, to run once:
  Serial.begin(115200);
  fwlcd.begin(16, 2);
  //
  fwlcd.setCursor(0,0);
  //fwlcd.print("Calibrating...");
  //calibrate();
  setSpeeds(0,0);
  //
  fwlcd.clear();
  fwlcd.setCursor(0,0);
  fwlcd.print("TEST SENSOR");
  fwlcd.setCursor(0,1);
  fwlcd.print("PRESS SLT TO RUN");
  //initEncoders();
  //  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(200);
  uint8_t buttons = fwlcd.readButtons();

  if(buttons & BUTTON_SELECT){
      
      takeNewMeasurement(0);
      Serial.println(getCombinedDistance(0));
    }

}
