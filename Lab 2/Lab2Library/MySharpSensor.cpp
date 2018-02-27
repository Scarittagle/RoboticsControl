
#include "MySharpSensor.h"
#include "Arduino.h"

#define N 10

float RawDataBuffer[N * 4] = {0};
bool Range = false;
int outOfRange[4] = {0};

float shortSensorVoltChart[18] = {  // Y-AXIS
    3.04, 3.01, 2.75, 2.37, 2.01, 1.78, 1.57, 1.40, 1.27, 1.06, 0.93,
    0.81, 0.74, 0.65, 0.53, 0.42, 0.38, 0.30
    };
float longSensorVoltChart[15] = {
    2.75, 2.51, 2.00, 1.51, 1.25, 1.05, 0.90, 0.80, 0.70, 0.65, 0.60,
    0.55, 0.50, 0.49, 0.46
    };
float shortSensorDistChart[18] = {  // X-AXIS
    2.90, 3.50, 4.00, 4.90, 6.00, 7.00, 8.00, 9.00, 10.00, 12.00, 14.00,
    16.00, 18.00, 20.00, 25.00, 30.00, 35.00, 40.00

};
float longSensorDistChart[15] = {
    10.00, 20.00, 30.00, 40.00, 50.00, 60.00, 70.00, 80.00, 90.00, 100.00,
    110.00, 120.00, 130.00, 140.00, 150.00
};

float shortToInches(int value){
	float distance_CM;
    float volt = (float)value * 0.0049;
	//Serial.println(volt);
    if(volt > shortSensorVoltChart[0] || volt < shortSensorVoltChart[17]){
        Range = true;
        return 0.01;
    }
	else{
        Range = false; 
		for(int i = 0; i < 18; i++){
			if(volt < shortSensorVoltChart[i] && volt > shortSensorVoltChart[i+1]){
				distance_CM = shortSensorDistChart[i] + (((volt - shortSensorVoltChart[i]) / (shortSensorVoltChart[i + 1] - shortSensorVoltChart[i]) ) * (shortSensorDistChart[i + 1] - shortSensorDistChart[i]));
				return distance_CM / 2.54; // return value in inches
			}
		}
	}
}

float longToInches(int value){
    float distance_CM;
	float volt = (float)value * 0.0049;
	// Serial.println(volt);
    if(volt > longSensorVoltChart[0] || volt < longSensorVoltChart[14]){
        return 920;
    }
	else{
		for(int i = 0; i < 15; i++){
			if(volt < longSensorVoltChart[i] && volt > longSensorVoltChart[i+1]){
				distance_CM = longSensorDistChart[i] + (((volt - longSensorVoltChart[i]) / (longSensorVoltChart[i + 1] - longSensorVoltChart[i]) ) * (longSensorDistChart[i + 1] - longSensorDistChart[i]));
				return distance_CM / 2.54;
			}
		}
	}
}




void takeNewMeasurement(int sensor){
    //Take measurement if Table is Empty
	if(sensor < 0 || sensor > 3){
		Serial.println("Must be sensor 1-4");
	}
	
	if(sensor < SLONG && RawDataBuffer[N * sensor] == 0){
		for(int i = 0; i < N; i++){
            int measurement = analogRead(sensor);
            RawDataBuffer[sensor * N + i] = shortToInches(measurement);
            if(Range == true){
                outOfRange[sensor] = 1;
                Range = false;
            }else{
                outOfRange[sensor] = 0;
                Range = false;
            }
            delay(20);
        }
	}
	else if(sensor == SLONG && RawDataBuffer[N * sensor] == 0){
		for(int i = 0; i < N; i++){
            int measurement = analogRead(sensor);
            RawDataBuffer[sensor * N + i] = longToInches(measurement);
            if(Range == true){
                outOfRange[sensor] = 1;
                Range = false;
            }else{
                outOfRange[sensor] = 0;
                Range = false;
            }
            delay(50);
        }
	}
	
	//Renew the first index of the corresponding sensor with new data every cycle.
	if(sensor < SLONG && RawDataBuffer[N * sensor] != 0){
		for(int i =  N - 1; i > 0; i--){ // Move everything -> one index
            RawDataBuffer[sensor * N + i] = RawDataBuffer[sensor * N + i - 1];
            delay(20);
        }
		// Replace value in first index
		int measurement = analogRead(sensor);
        RawDataBuffer[sensor * N] = shortToInches(measurement);
        if(Range == true){
            outOfRange[sensor] = 1;
            Range = false;
        }else{
            outOfRange[sensor] = 0;
            Range = false;
        }
	}
	
	else if(sensor == SLONG && RawDataBuffer[N * sensor] != 0){
		for(int i = N - 1; i > 0; i--){ 
            RawDataBuffer[sensor * N + i] = RawDataBuffer[sensor * N + i - 1];
            delay(50);
        }
		int measurement = analogRead(sensor);
        RawDataBuffer[sensor * N] = longToInches(measurement);
        if(Range == true){
            outOfRange[sensor] = 1;
            Range = false;
        }else{
            outOfRange[sensor] = 0;
            Range = false;
        }
	}
	
	for(int i = 0; i < N; i++){
		Serial.print(RawDataBuffer[sensor * N + i]);
		Serial.print(" ");
	}
	Serial.print("\n");
}



float getCombinedDistance(int sensor){
    float total;
    float avg;

    if(sensor < SLONG){
        for(int i = 0; i < N; i++){
            total += RawDataBuffer[sensor * N + i];
            avg = total / N;
		}
		return avg;
	}
        //Measurement for Long Range Sensor
    else if(sensor == SLONG){
        for(int i = 0; i < N; i++){
            total += RawDataBuffer[sensor * N + i];
            avg = total / N;
        }
		return avg;
    }

}


void initDistanceSensors(){
  //I'm not sure if the Sensor itself is actually can be initialize.
  //I might just initialize the table then.
  for (int i = 0; i < (N*4); i++){
      RawDataBuffer[i] = 0;
  }


}
