#ifndef I2DICE_H
#define I2DICE_H

#include "MPU9250.h"
#include "SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h"



void initalizeWire();
bool batteryLOW();
double getLipoFuel();
int detectDiceFace();



#endif //I2DICE_H