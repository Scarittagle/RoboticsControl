#include <EllipseParams.h>
#include <MyEncoders.h>
#include <MyServos.h>

#include <Adafruit_RGBLCDShield.h>

Adafruit_RGBLCDShield ellcd = Adafruit_RGBLCDShield();


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ellcd.begin(16, 2);
  //
  ellcd.setCursor(0,0);
  ellcd.print("Calibrating...");
  calibrate();
  setSpeeds(0,0);
  //
  ellcd.clear();
  ellcd.setCursor(0,0);
  ellcd.print("ELLIPSE");
  ellcd.setCursor(0,1);
  ellcd.print("PRESS SLT TO RUN");
  initEncoders();
  //  
}

void loop() {
  // put your main code here, to run repeatedly:

}
