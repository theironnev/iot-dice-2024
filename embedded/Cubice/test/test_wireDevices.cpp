#include <Arduino.h>
#include <Wire.h>

void scanI2C() {
  byte error, address;
  int deviceCount = 0;

  for(address = 1; address < 127; address++ ) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");
      deviceCount++;
    }
    else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (deviceCount == 0) {
    Serial.println("No I2C devices found");
  }
  else {
    Serial.println("Scan complete");
    Serial.print("Found ");
    Serial.print(deviceCount);
    Serial.println(" devices");
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for serial monitor to open
  Serial.println("hello");

  Wire.begin();


  
  
}

void loop() {
  delay(5000);
  Serial.println("Scanning I2C bus...");
  scanI2C();
}


