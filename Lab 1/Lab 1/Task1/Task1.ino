#include <MyEncoders.h>
#include <MyServos.h>
#include <Adafruit_RGBLCDShield.h>

Adafruit_RGBLCDShield t1lcd = Adafruit_RGBLCDShield();
float wheelSpeed[2];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  t1lcd.begin(16, 2);
  initEncoders();
  //
  t1lcd.setCursor(0,0);
  t1lcd.print("Task 1 RUNNING");
  setSpeeds(0,100);
  delay(1000); //delay 1 sec

  //Task 1:
  //Note: 10 seconds = 10000 ms
  //to take measurement for each 30 ms in 10 seconds
  int MsmtCount = 10000 / 30; //approx 333 times
  for(int i = 0; i < MsmtCount; i++){
    t1lcd.setCursor(0,1);
    t1lcd.print("Measuring...");
    getSpeeds(wheelSpeed);
    Serial.println(wheelSpeed[1]);//print right
    delay(30);
  }
  t1lcd.clear();
  t1lcd.setCursor(0,1);
  t1lcd.print("STOPPED");
  setSpeeds(0,0);
}

void loop() {
  // put your main code here, to run repeatedly:

}
