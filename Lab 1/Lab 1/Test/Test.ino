#include "MyEncoders.h"
#include "MyServos.h"

void setup() {
  Serial.begin(115200);
  
  calibrate();
  setSpeedsvw(3.00, -1.00);
}

void loop() {      // Main loop auto-repeats
  
}

