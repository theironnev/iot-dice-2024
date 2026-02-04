// #include <Arduino.h> // Include the Arduino core library

// #include "MPU9250.h"
// #include "SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h"
// // #include "MAX17043.h"

// //IMU
// /***************************/
// struct Accelerometer {
//     float x;
//     float y;
//     float z;
// };
// Accelerometer acc; // This is the 3-Axis IMU data
// MPU9250 mpu; // You can also use MPU9255 as is

// SFE_MAX1704X lipo;

// double voltage = 0; // Variable to keep track of LiPo voltage
// double soc = 0; // Variable to keep track of LiPo state-of-charge (SOC)
// bool alert; // Variable to keep track of whether alert has been triggered

// int detectDiceFace() {

//     if (mpu.update()) {
//         acc.x = mpu.getAccX();
//         acc.y = mpu.getAccY();
//         acc.z = mpu.getAccZ();
//     }

//     // This function returns the local maximum which is the constant gravitational pull when standing still
//     float max = fmaxf(fabsf(acc.x), fmaxf(fabsf(acc.y), fabsf(acc.z)));

//     //This part check on which axis the constant gravitational pull lies and returns the face.
//     // if the gravitational pull is on the x-axis it can either be -1 or 1, 
//     // so if a.x is higher then 0 the dice face thrown is 3, else 4 etc.
//     if (fabsf(acc.x) == max) {
//         return acc.x > 0 ? 3 : 4;
//     } else if (fabsf(acc.y) == max) {
//         return acc.y > 0 ? 2 : 5;
//     } else {
//         return acc.z > 0 ? 1 : 6;
//     }

// }
// void printLipo(){
//       // lipo.getVoltage() returns a voltage value (e.g. 3.93)
//   voltage = lipo.getVoltage();
//   // lipo.getSOC() returns the estimated state of charge (e.g. 79%)
//   soc = lipo.getSOC();
//   // lipo.getAlert() returns a 0 or 1 (0=alert not triggered)
//   alert = lipo.getAlert();

//   // Print the variables:
//   Serial.print("Voltage: ");
//   Serial.print(voltage);  // Print the battery voltage
//   Serial.println(" V");

//   Serial.print("Percentage: ");
//   Serial.print(soc); // Print the battery state of charge
//   Serial.println(" %");

//   Serial.print("Alert: ");
//   Serial.println(alert);
//   Serial.println();
// }

// void print_roll_pitch_yaw() {
//     Serial.print("Yaw, Pitch, Roll: ");
//     Serial.print(mpu.getMagX(), 2);
//     Serial.print(", ");
//     Serial.print(mpu.getMagY(), 2);
//     Serial.print(", ");
//     Serial.println(mpu.getMagZ(), 2);
// }
// // void displayReading()
// // {
// //   //
// //   // Get the voltage, battery percent
// //   // and other properties.
// //   //
// //   Serial.println("Device Reading:");
// //   Serial.print("Address:       0x"); Serial.println(FuelGauge.address(), HEX);
// //   Serial.print("Version:       "); Serial.println(FuelGauge.version());
// //   Serial.print("ADC:           "); Serial.println(FuelGauge.adc());
// //   Serial.print("Voltage:       "); Serial.print(FuelGauge.voltage()); Serial.println(" mV");
// //   Serial.print("Percent:       "); Serial.print(FuelGauge.percent()); Serial.println("%");
// //   Serial.print("Is Sleeping:   "); Serial.println(FuelGauge.isSleeping() ? "Yes" : "No");
// //   Serial.print("Alert:         "); Serial.println(FuelGauge.alertIsActive() ? "Yes" : "No");
// //   Serial.print("Threshold:     "); Serial.print(FuelGauge.getThreshold()); Serial.println("%");
// //   Serial.print("Compensation:  0x"); Serial.println(FuelGauge.compensation(), HEX);
// //   Serial.println();
// //   delay(1000);
// // }

// void setup() {
//     Serial.begin(115200);
//     Wire.begin();
//     delay(500);
//     mpu.setup(0x68); 
//     // delay(2000);

//     // Check if MPU9250 is connected
//     if (mpu.isConnected()) {
//         Serial.println("MPU9250 is connected!");
//     } else {
//         Serial.println("MPU9250 is NOT connected!");
//     }

//   // Set up the MAX17043 LiPo fuel gauge:
//   if (lipo.begin() == false) // Connect to the MAX17043 using the default wire port
//   {
//     Serial.println(F("MAX17043 not detected. Please check wiring. Freezing."));
//     // while (1)
//     //   ;
//   }

// 	// Quick start restarts the MAX17043 in hopes of getting a more accurate
// 	// guess for the SOC.
// 	lipo.quickStart();

// 	// We can set an interrupt to alert when the battery SoC gets too low.
// 	// We can alert at anywhere between 1% - 32%:
// 	lipo.setThreshold(20); // Set alert threshold to 20%.
// }

// void loop(){

//     // Serial.println("mpu is ");
//     // Serial.println(mpu.isConnected());
//     // print_roll_pitch_yaw();
//     printLipo();
//     delay(500);
    
//     Serial.println(detectDiceFace());
//     delay(500);
// }