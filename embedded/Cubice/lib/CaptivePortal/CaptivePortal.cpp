/*
    Author: Theironne Velliam
    This is a class file created for the Captive portal. To set up WiFi connection on the IoT device
*/

#include "CaptivePortal.h"
// #include <iostream>
#include <string>
// This is a character array of html elements stored in the program memory.
// This is the html txt  for the captive portal page.
const char CaptivePortal::captiveHtml[] PROGMEM = R"rawliteral(
    <!DOCTYPE html>
    <head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <style>
            body{
                background-color: black;
                color: aliceblue;
                font-family: monospace;
                }

            form { 
                width: 300px;
                padding: 20px;
                border: 3px solid rgb(159, 143, 225);
                border-radius: 10px;
                background-color: black;
                box-shadow: 0 0 20px rgba(91, 125, 248, 0.781);
            }

            input[type="text"]
            {
                width: 100%;
                padding: 10px;
                margin-bottom: 10px;
                box-sizing: border-box;
                border-radius: 5px;
                border: 1px solid  rgb(159, 143, 225);
                background-color: white;
                
            }

            input[type="submit"] {
                width: 40%;
                padding: 10px;
                box-sizing: border-box;
                border: none;
                border-radius: 5px;
                background-color:  rgb(159, 143, 225);
                color: black;
                cursor: pointer;
            }

            input[type="submit"]:hover {
                background-color:rgba(91, 125, 248, 0.781);
            }
    </style>
  </head>
<body>
    <p>Connect to your Wifi network</p>
    <form id="form-connect" action="/connect">
        <label for="ssid">Wifi network name</label>
        <br>
        <input type="text" name="ssid" placeholder="Name of wifi access point" required> 
        <br> <br>
        <label for="password">Password</label> 
        <br>
        <input  type="text" name="password" placeholder="Password" required> 
        <br> <br>
        <input type="submit" value="submit">
    </form><br>
    <p>Copy the device address <strong>%MAC%</strong></p>
</body>
)rawliteral";



//Contructors for portal and request handler 
CaptivePortal::CaptivePortal() : server(80), nameReceived(false), passwordReceived(false) {}
CaptiveRequestHandler::CaptiveRequestHandler() {}

// // Setup WiFi AP and server
void CaptivePortal::begin() {
    // To create a captive portal the Wifi mode is set to Acces point
    WiFi.mode(WIFI_AP);
    // AP network name
    WiFi.softAP("esp-captive");
    MAC =WiFi.macAddress().c_str();             //Get Unique device ID  ?not ideal, have to search for better ID for security¿
    // MAC.replace(":", "-");

    //handle requests
    setupServer();
    //Any request on this network gets redirected to APIP 
    dnsServer.start(53, "*", WiFi.softAPIP());
    //Create request handler object
    setupHandlers();
    //Start ESPAsyncWebServer
    server.begin();
}
// Keep looking for requests
bool CaptivePortal::submissionComplete() {
    while(!completedSubmission){
            dnsServer.processNextRequest();
    
        if (nameReceived && passwordReceived) {
            //Submission complete. Closing AP and server
            closeAPAndServer();
            completedSubmission = true;
            break;
        }
    }
    return completedSubmission; 
}
// setup a AsyncWeb server 
void CaptivePortal::setupServer() {
    //On first connect redirect to index page
    server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", captiveHtml);
        // Client Connected
    });
    // On GET request to /connect read parameters
    server.on("/connect", HTTP_GET, [this](AsyncWebServerRequest *request) {
        String inputMessage; 
        String inputParam; 
        if (request->hasParam("ssid")) { 
            inputMessage = request->getParam("ssid")->value();
            inputParam = "ssid"; 
            this->networkName = inputMessage; // Capture 'this' explicitly
            // Serial.println(inputMessage); 
            this->nameReceived = true; // Capture 'this' explicitly
        }
        if (request->hasParam("password")) { 
            inputMessage = request->getParam("password")->value();
            inputParam = "password"; 
            this->networkPassword = inputMessage; // Capture 'this' explicitly
            // Serial.println(inputMessage); 
            this->passwordReceived = true; // Capture 'this' explicitly
        } 

        request->send(200, "text/html",  "<head><style> body{background-color: black;color: aliceblue;font-family: monospace;font-size: 30px;}</style></head><body>The ssid and password entered by you have been successfully sent to the device <br> <br>1. Copy this device Id:<br><strong>"+ MAC+"</strong> <br> <br> 2. Go to <strong>https://velliat.loca.lt/</strong> and put the device ID in the form");
    });
}

bool CaptiveRequestHandler::canHandle(AsyncWebServerRequest *request) {
    request->addInterestingHeader("ANY");
    return true;
}

void CaptiveRequestHandler::handleRequest(AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", CaptivePortal::captiveHtml);
}



void  CaptivePortal::setupHandlers() {
        // Create an instance of CaptiveRequestHandler
        CaptiveRequestHandler* captiveHandler = new CaptiveRequestHandler();

        // Add the handler to the server and set the filter
        server.addHandler(captiveHandler).setFilter(ON_AP_FILTER);
}

void CaptivePortal::closeAPAndServer() {
    dnsServer.stop();  // Stop the DNS server
    server.end();      // Stop the web server
    delay(1000);
    WiFi.softAPdisconnect(true);
}

