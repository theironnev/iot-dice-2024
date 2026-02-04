#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h> // Include the Arduino core library

#include <WiFi.h>
#include <PubSubClient.h>
#include <Preferences.h>

#include "CaptivePortal.h" //self-made libs/helper
#include "PiezoPlayer.h"

#include "i2dice.h" // helper


// Defined Macros
#define BUTTON_PIN 2 // BUTTON PIN
#define PIEZO_PIN 0  // PIEZO SOUND PIN
#define LED_PIN 4  // LED PIN
#define PWM_CHANNEL 0 // channel of the piezo buzzer on ledc
#define WAIT_CONNECTION 5000 // 5 seconds in milliseconds
#define ONE_SECOND 1000

// Uncomment the line below to enable printing mode
#define LOG

// Define LOG_PRINT 
#ifdef LOG
#define BAUD_RATE 115200
#define LOG_PRINT(x) Serial.print(x)
#define LOG_PRINTLN(x) Serial.println(x)
#else
#define LOG_PRINT(x)
#define LOG_PRINTLN(x)
#endif

// Uncomment this line to disable Web communication
#define USE_WEB



enum States{
    AP_START,
    STA_SWITCH,
    CONNECTING_WIFI,
    READY,
    ROLLED,
    LOST_CONNECTION,
};
// States state = AP_START;



#endif //MAIN_H