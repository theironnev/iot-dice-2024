#ifndef CAPTIVEPORTAL_H
#define CAPTIVEPORTAL_H

#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
// #include "SPIFFS.h"


class CaptivePortal {
public:
    CaptivePortal();

    static const char network_html[];
    String  MAC;
    String networkName;
    String networkPassword;
   
    void begin();
    bool submissionComplete();
    void setupHandlers();
    void closeAPAndServer();


private:
    DNSServer dnsServer; 
    AsyncWebServer server;
    bool nameReceived;
    bool passwordReceived;
    bool completedSubmission = false;

    void setupServer();
};

class CaptiveRequestHandler : public AsyncWebHandler {
public:
    CaptiveRequestHandler();
    bool canHandle(AsyncWebServerRequest *request);
    void handleRequest(AsyncWebServerRequest *request);
};


#endif
