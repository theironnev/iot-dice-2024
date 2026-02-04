/*
Author: Theironne Velliam
Time: 2024-02-10
Link: https://github.com/theironnev

This part of code is the main file of the IoT-dice project that receives 
input from the User by MQTT communication and publishes dice data trough MQTT.
The constants variables are not declared in main.h because it is easier to look over this way,
because of the static host IP.

MIT License

Copyright (c) [2024] [Theironne Velliam]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "main.h"


//GLOBALS
/***************************/
volatile bool buttonPressed = false;
// MQTT broker details
const char* mqttServer = "172.20.10.13";
const int mqttPort = 1883;
const char* mqttUsername = "iot-dice";
const char* mqttPassword = "7YKyE8R2AhKzswfN";
const char* mqttSubTopic = "cubice/+/dice/#";
const char* mqttPubTopic = "cubice/+/web/";





//Initializations
/***************************/
CaptivePortal captivePortal;
Preferences preferences;
PiezoPlayer piezo(PIEZO_PIN, PWM_CHANNEL);
WiFiClient espClient;
// WiFiClientSecure espClient;
PubSubClient client(espClient);



//Function prototypes
/***************************/
void setNetwork(Preferences& preferences);
void blink(int numBlinks, int totalDuration);
void buttonInterrupt();

const char* uniqueMqttTopic(const String& macAddress, const char* topicTemplate);
char* mqttReplyTopic(const char* pub_topic, char* subtopic);
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();



void setup() {
  #ifdef LOG
    Serial.begin(BAUD_RATE);
  #endif

    pinMode(BUTTON_PIN, INPUT); // Set button 
    pinMode(LED_PIN, OUTPUT); // Set LED pin

    blink(2, ONE_SECOND); // blink twice in one second

    piezo.melody(START_DICE);// Play the turn on melody

    // If the project is configured to use a web-app, include this part of the code in compilation
    #ifdef USE_WEB
    preferences.begin("network", false); // Open NVS with the namespace "network"

    // Check if button is pressed on start-up, if so clear the stored network settings.
    if (digitalRead(BUTTON_PIN) == LOW) {
        delay(ONE_SECOND/2);
        LOG_PRINTLN("Button pressed for 5 seconds. Clearing network data...");
        preferences.clear(); // Clear all preferences in the "network" namespace
        LOG_PRINTLN("Network data cleared.");
    }

    setNetwork(preferences);

    delay(ONE_SECOND/2); // wait with performing next line

    //Connect to network wifi
    unsigned long startTime = millis(); // Record the start time

    WiFi.begin(preferences.getString("ssid", ""), preferences.getString("password", ""));
    
    LOG_PRINT("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED && millis() - startTime < WAIT_CONNECTION) {
        delay(ONE_SECOND/2);
        LOG_PRINT(".");
    }
     if (WiFi.status() == WL_CONNECTED){
        LOG_PRINTLN("Connected to WiFi");

        
        mqttSubTopic = uniqueMqttTopic(WiFi.macAddress(), mqttSubTopic);
        mqttPubTopic = uniqueMqttTopic(WiFi.macAddress(), mqttPubTopic);
        LOG_PRINT("sub topic: ");
        LOG_PRINTLN(mqttSubTopic);
        LOG_PRINT("pub topic: ");
        LOG_PRINTLN(mqttPubTopic);
        

        client.setServer(mqttServer, mqttPort);
        // setup_mqtt();
       
        client.setCallback(callback);
     }
     else {
        LOG_PRINTLN("Failed to connect to WiFi");
        // play cycle 

     }
    preferences.end(); // Close NVS

    #endif
    //initialize the I2C sensors
    initalizeWire();
    //make a interrupt out of button input
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonInterrupt, FALLING);
}


void loop() {
   
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
/* this function retrieves the network settings from non-volatile storage. 
 And creates a new captive portal if there is no network settings stored.*/
void setNetwork(Preferences& preferences){
    // Check if the SSID and password are not stored in NVS
    if (preferences.getString("ssid", "").length() == 0 && preferences.getString("password", "").length() == 0) {
        captivePortal.begin();
        if (captivePortal.submissionComplete()){
        preferences.putString("ssid", captivePortal.networkName); // Save SSID into NVS
        preferences.putString("password", captivePortal.networkPassword); // Save password into NVS
        }
    }

    //conect to wifi in sta mode
    LOG_PRINTLN("network stored");
    LOG_PRINT("ssid: ");
    LOG_PRINTLN(preferences.getString("ssid", ""));
    LOG_PRINT("password: ");
    LOG_PRINTLN(preferences.getString("password", ""));   
    
}
// callback function of MQTT loop
void callback(char* topic, byte* payload, unsigned int length) {
  LOG_PRINT("Message arrived [");
  LOG_PRINT(topic);
  LOG_PRINT("] ");

  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
 
  // Extract the subtopic from the topic
  String subtopic = topic;
  subtopic = subtopic.substring(subtopic.lastIndexOf('/') + 1);
  LOG_PRINTLN(subtopic);

  // Check which subtopic the message belongs to
   if (subtopic == "areyouthere") {
    //make topic-name, mqttPubTopic = "cubice/+/web/"+"world"
    char replySuffix[] = "world";
    char* replyTopic = mqttReplyTopic(mqttPubTopic, replySuffix);

    // publish hello world on reply
    client.publish(replyTopic, "hello web");
    // piezo.melody(HELLO_IOT); // play hello IOT to let user know there is a web-client
   
  } else if (subtopic == "roll") { 

    ///make topic-name, mqttPubTopic = "cubice/+/web/"+"rolled"
    char replySuffix[] = "rolled";
    char* replyTopic = mqttReplyTopic(mqttPubTopic, replySuffix);

    // piezo.melody(COUNT_DOWN); // play melody countdown 
    blink(10,5000);

    int roll = detectDiceFace(); //get rolled value

    char payloadBuffer[5]; // Buffer to hold the converted string
    sprintf(payloadBuffer, "%d", roll); // Convert dice value to string

    //give dice value to web
    client.publish(replyTopic, payloadBuffer);
    LOG_PRINT("rolled number: ");
    LOG_PRINTLN(roll);
   
  } else if (subtopic == "battery") {
    ///make topic-name, mqttPubTopic = "cubice/+/web/"+"battery"
    char replySuffix[] = "battery";
    char* replyTopic = mqttReplyTopic(mqttPubTopic, replySuffix);
    
    double percentage = getLipoFuel();
    char payloadBuffer[10]; // Buffer to hold the converted string
    sprintf(payloadBuffer, "%.1f", percentage); // Convert battery value to string

    //give dice value to web
    client.publish(replyTopic, payloadBuffer);
    LOG_PRINT(percentage);
    LOG_PRINTLN("%");
    
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    LOG_PRINT("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client", mqttUsername, mqttPassword)) {
      LOG_PRINTLN("connected");
      // Once connected, publish an announcement...
      client.publish(mqttPubTopic, "hello web");
      // ... and resubscribe
      client.subscribe(mqttSubTopic);
    } else {
      LOG_PRINT("failed, rc=");
      LOG_PRINT(client.state());
      LOG_PRINTLN(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(ONE_SECOND*5);
    }
  }
}

// Define the callback function for the interrupt
void buttonInterrupt() {
  buttonPressed = true;
  digitalWrite(0, buttonPressed);
  // char replySuffix[] = "button";
  // char* replyTopic = mqttReplyTopic(mqttPubTopic, replySuffix);
  // client.publish(replyTopic, "true");
}

void blink(int numBlinks, int totalDuration) {
    const int freq = 12000;
    const int resolution = 8;
    const int channel = 0;
    // Calculate the duration of each blink interval
    int blinkInterval = totalDuration / (2 * numBlinks);

    // Set up LEDC for PWM control
    ledcSetup(channel, freq, resolution); // Channel 0, 12 kHz PWM, 8-bit resolution
    ledcAttachPin(LED_PIN, channel); // Attach LED pin to channel 0 *** Notice, Same LEDC-CHANNEL as the piezo buzzer


    // Store the current duty cycle value before changing it. 
    int originalDutyCycle = ledcRead(channel); 

    // Blink the LED for the specified number of times
    for (int i = 0; i < numBlinks; i++) {
        // Turn the LED on
        ledcWrite(channel, (2^resolution) - 1); // 100% duty cycle
        delay(blinkInterval);
        // Turn the LED off
        ledcWrite(channel, 0); // 0% duty cycle
        delay(blinkInterval);
    }
        // Restore the LED's duty cycle to its original value
    ledcWrite(0, originalDutyCycle);

}

// Function to generate MQTT topic with MAC address
const char* uniqueMqttTopic(const String& macAddress, const char* topicTemplate) {
  int topicLength = strlen(topicTemplate) + macAddress.length() - 1; // Subtract 1 to account for the '+' character

  // Allocate memory for the MQTT topic
  char* topic = new char[topicLength + 1]; // Add 1 for null terminator

  // Find the position of '+'
  const char* placeholder = strchr(topicTemplate, '+');
  if (placeholder == NULL) {
    // '+' not found, return the original template
    return topicTemplate;
  }

  // Copy the topicTemplate up to the placeholder
  strncpy(topic, topicTemplate, placeholder - topicTemplate);
  topic[placeholder - topicTemplate] = '\0'; // Null-terminate the string

  // Append the MAC address
  strcat(topic, macAddress.c_str());

  // Append the rest of the template after the placeholder
  strcat(topic, placeholder + 1);
  return topic;
}

char* mqttReplyTopic(const char* pub_topic, char* subtopic){
    // Determine the length of the concatenated string
    int length = strlen(pub_topic) + strlen(subtopic) + 1; // Add 1 for the null terminator
    // Allocate memory for the new string
    char* newPub = new char[length];

    // Copy the contents of mqtt_pub to newPub
    strcpy(newPub, pub_topic);

    // Concatenate " world" to newPub
    strcat(newPub, subtopic);
    return newPub;
}
