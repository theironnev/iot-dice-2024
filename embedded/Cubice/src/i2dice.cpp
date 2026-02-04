/*
    Author: Theironne Velliam
    Link: https://github.com/theironnev

    This part of code is specifically for the I2C components, that are used in the IoT-device.
    Functions and declarations used for the I2C modules are stated in this file.
*/
#include "main.h"
#include "i2dice.h"

SFE_MAX1704X lipo(MAX1704X_MAX17043);

double voltage = 0; // Variable to keep track of LiPo voltage
double soc = 0; // Variable to keep track of LiPo state-of-charge (SOC)
bool alert; // Variable to keep track of whether alert has been triggered


struct Accelerometer {
    float x;
    float y;
    float z;
};
Accelerometer acc; // This is the 3-Axis IMU data

MPU9250 mpu; // You can also use MPU9255 as is

void initalizeWire(){
    Wire.begin();
    delay(500);
    mpu.setup(0x68); 
    // delay(2000);

    // Check if MPU9250 is connected
    if (mpu.isConnected()) {
        LOG_PRINTLN("MPU9250 is connected!");
        // Serial.println("MPU9250 is connected!");
    } else {
        LOG_PRINTLN("MPU9250 is NOT connected!");
        // Serial.println("MPU9250 is NOT connected!");
    }

  // Set up the MAX17043 LiPo fuel gauge:
  if (lipo.begin() == false) // Connect to the MAX17043 using the default wire port
  {
    LOG_PRINTLN(F("MAX17043 not detected. Please check wiring. Freezing."));
    // Serial.println(F("MAX17043 not detected. Please check wiring. Freezing."));
    // while (1)
    //   ;
  }

	// Quick start restarts the MAX17043 in hopes of getting a more accurate
	// guess for the SOC.
	lipo.quickStart();

	// We can set an interrupt to alert when the battery SoC gets too low.
	// We can alert at anywhere between 1% - 32%:
	lipo.setThreshold(20); // Set alert threshold to 20%.
}


bool batteryLOW() {
    alert = lipo.getAlert() ? true :false ; 
    lipo.clearAlert();
    return alert; 
}

double getLipoFuel(){
    return lipo.getSOC();
}

void updateAccelerometer(){
    if (mpu.update()) {
        acc.x = mpu.getAccX();
        acc.y = mpu.getAccY();
        acc.z = mpu.getAccZ();
    }
}

int detectDiceFace() {
    updateAccelerometer();
    // This function returns the local maximum which is the constant gravitational pull when standing still
    float max = fmaxf(fabsf(acc.x), fmaxf(fabsf(acc.y), fabsf(acc.z)));

    //This part check on which axis the constant gravitational pull lies and returns the face.
    if (fabsf(acc.x) == max) {
        return acc.x > 0 ? 3 : 4;
    } else if (fabsf(acc.y) == max) {
        return acc.y > 0 ? 2 : 5;
    } else {
        return acc.z > 0 ? 1 : 6;
    }
}