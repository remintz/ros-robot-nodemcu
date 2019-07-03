#ifndef WEBCONFIG_H
#define WEBCONFIG_H

#include <const.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <nonvolatile.h>

// WiFi Definitions

class WebConfig {
    const char WiFiAPPSK[] = "ABC"; //WIFI_AP_PASSWORD;
    NonVolatile *storage;
    public:
        WebConfig();
    private:
        ESP8266WebServer *server;
        void handleRoot();
        void handleSaveParameters();
        void handleCSS();
        void handleResetEEPROM();
        void handleNotFound();
}

#endif