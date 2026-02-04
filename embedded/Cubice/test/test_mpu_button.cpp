#include <Arduino.h>
#include "MPU9250.h"

enum States{
    AP_START,
    STA_SWITCH,
    CONNECTING_WIFI,
    READY,
    ROLLED,
    LOST_CONNECTION,
};

struct Accelerometer {
    float x;
    float y;
    float z;
};



// Define the pin for the button
const int buttonPin = 4;
// Define a variable to store the state of the button
volatile bool buttonPressed = false;

States state = States::AP_START;
MPU9250 mpu; // You can also use MPU9255 as is
Accelerometer acc; // This is the 3-Axis IMU data

int detectDiceFace(Accelerometer a);
void buttonInterrupt();




void setup() {
    Serial.begin(115200);
    Wire.begin();
    delay(2000);

    mpu.setup(0x68);  // change to your own address
    
    // delay(5000);

    // // calibrate anytime you want to
    // mpu.calibrateAccelGyro();
    // mpu.calibrateMag();

      // Set the button pin as input
    pinMode(buttonPin, INPUT);
    pinMode(0, OUTPUT);
  
    // Attach the interrupt to the button pin, triggering on falling edge
    attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, FALLING);
    Serial.println("Setup done ..");
}

void loop() {
    if (mpu.update()) {
        acc.x = mpu.getAccX();
        acc.y = mpu.getAccY();
        acc.z = mpu.getAccZ();
    }
    int a = detectDiceFace(acc);
   
    if (buttonPressed) {
    // Do something when the button is pressed
    Serial.print("face rolled: ");
    Serial.println(a);
     
    
    // Reset the buttonPressed flag
    buttonPressed = false;
  }
  digitalWrite(0, buttonPressed);
  delay(1000);

}

int detectDiceFace(Accelerometer a) {
    // This function returns the local maximum which is the constant gravitational pull when standing still
    float max = fmaxf(fabsf(a.x), fmaxf(fabsf(a.y), fabsf(a.z)));

    //This part check on which axis the constant gravitational pull lies and returns the face.
    if (fabsf(a.x) == max) {
        return a.x > 0 ? 3 : 4;
    } else if (fabsf(a.y) == max) {
        return a.y > 0 ? 2 : 5;
    } else {
        return a.z > 0 ? 1 : 6;
    }
}


// Define the callback function for the interrupt
void buttonInterrupt() {
  buttonPressed = true;
  Serial.println("hoi");
  digitalWrite(0, buttonPressed);
}
