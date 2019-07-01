#include "nonvolatile.h"
#include "const.h"

NonVolatile* NonVolatile::instance = nullptr;

NonVolatile *NonVolatile::getInstance() {
    if (!instance) {
        instance = new NonVolatile;
    }
    return instance;
}

void NonVolatile::init(bool reset) {
    if (reset) {
        this->configuration.robotId = 0;
        strcpy(this->configuration.robotDesc, "Robot0");
        strcpy(this->configuration.rosMasterAddress, ROS_MASTER_IP);
        this->configuration.rosMasterPort = 11411;
        strcpy(this->configuration.wifiSSID, WIFI_SSID);
        strcpy(this->configuration.wifiPass, WIFI_PASSWORD);
        this->configuration.isAPMode = false;
        this->save();
        // this->configuration.robotId = -1;
        // strcpy(this->configuration.robotDesc, "");
        // strcpy(this->configuration.rosMasterAddress, "");
        // this->configuration.rosMasterPort = 11411;
        // strcpy(this->configuration.wifiSSID, "");
        // strcpy(this->configuration.wifiPass, "");
        // this->configuration.isAPMode = false;
        // this->save();
    }
}

void NonVolatile::save() {
    // EEPROM.begin(this->size);
    // EEPROM.put(this->initPos, this->configuration);
    // EEPROM.end();
}

NonVolatile::ConfigData NonVolatile::getConfigData() {
    this->configuration.robotId = 0;
    strcpy(this->configuration.robotDesc, "Robot0");
    strcpy(this->configuration.rosMasterAddress, ROS_MASTER_IP);
    this->configuration.rosMasterPort = 11411;
    strcpy(this->configuration.wifiSSID, WIFI_SSID);
    strcpy(this->configuration.wifiPass, WIFI_PASSWORD);
    this->configuration.isAPMode = false;

    // if (this->configuration.robotId != -1) {
    //     // EEPROM.begin(this->size);
    //     // EEPROM.get(this->initPos, this->configuration);
    //     // EEPROM.end();
    // }
    return this->configuration;
}
