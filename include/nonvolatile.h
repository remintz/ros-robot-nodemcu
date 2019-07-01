#ifndef NONVOLATILE_H
#define NONVOLATILE_H

#include <EEPROM.h>

// between 4 and 4096bytes
#define MEM_ALOC_SIZE 512
#define MEM_INIT_POS 0

class NonVolatile {
    private:
        static NonVolatile* instance;
        long size = MEM_ALOC_SIZE;
        long initPos = MEM_INIT_POS;
    public:
        struct ConfigData {
            int robotId;
            char robotDesc[20];
            char rosMasterAddress[20];
            int rosMasterPort;
            char wifiSSID[20];
            char wifiPass[20];
            bool isAPMode;
            bool isFirstTime;
        };
        NonVolatile() {};
        static NonVolatile* getInstance();
        void reset();
        ConfigData getConfigData();
        void save();
        ConfigData configuration;

};

#endif
