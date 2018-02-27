#include <MyEncoders.h>
#include <MyServos.h>
#include <Adafruit_RGBLCDShield.h>
#define MAX 400

Adafruit_RGBLCDShield t2lcd = Adafruit_RGBLCDShield();
float wheelSpeed[2];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  t2lcd.begin(16, 2);
  initEncoders();
  //
  t2lcd.setCursor(0,0);
  t2lcd.print(F("Task 2 RUNNING"));
  setSpeeds(0,0);
  t2lcd.setCursor(0,1);
  t2lcd.print(F("Delaying..."));
  delay(1000); //delay 1 sec

  //Task 2
  //measure from -200 to 200 micros?
  int ci = 0;
  for(int i = -200; i <= 200; i = i + 10){
    t2lcd.setCursor(0,1);
    t2lcd.print(F("Measuring..."));
    setSpeeds(i,i);
    delay(1000); //1 second to stablize
    getSpeeds(wheelSpeed);
    //Serial.println(wheelSpeed[1]);//Right
    Serial.println(wheelSpeed[0]);//Left  
  }
  //STOPPED
  t2lcd.clear();
  t2lcd.setCursor(0,1);
  t2lcd.print(F("STOPPED"));
  setSpeeds(0,0);
}

void loop() {
  // put your main code here, to run repeatedly:

}
