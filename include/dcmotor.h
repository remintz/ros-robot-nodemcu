#ifndef DC_MOTOR_H
#define DC_MOTOR_H

#include "Arduino.h"

class DCMotor {
    public:
        DCMotor();
        void attach(int motor, uint8_t pinFwd, uint8_t pinBwd, uint8_t pinEnable);
        void setRange(int range);
        void command(int speed1, int speed2);


    private:
        uint8_t pinFwd1 = 255;
        uint8_t pinBwd1 = 255;
        uint8_t pinSpeed1 = 255;
        uint8_t pinFwd2 = 255;
        uint8_t pinBwd2 = 255;
        uint8_t pinSpeed2 = 255;
        int range = 0;

        int denormalize(int value);

};
#endif
