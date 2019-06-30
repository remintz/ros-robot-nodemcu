#include "dcmotor.h"

DCMotor::DCMotor() {
}

void DCMotor::attach(int motorId, uint8_t pinFwd, uint8_t pinBwd, uint8_t pinEnable) {
    if (motorId == 1) {
        this->pinFwd1 = pinFwd;
        this->pinBwd1 = pinBwd;
        this->pinSpeed1 = pinEnable;
    } else {
        this->pinFwd2 = pinFwd;
        this->pinBwd2 = pinBwd;
        this->pinSpeed2 = pinEnable;
    }
    pinMode(pinFwd, OUTPUT);
    pinMode(pinBwd, OUTPUT);
    pinMode(pinEnable, OUTPUT);
    analogWrite(pinEnable, 0);
}

int DCMotor::denormalize(int value) {
    int result = round(value / 100.0 * this->range * 1.0);
    Serial.printf("denormalize: %d -> %d range: %d\n", value, result, this->range);
    return result;
}

void DCMotor::command(int speed1, int speed2) {
    Serial.printf("motor command 1: %d 2: %d\n", speed1, speed2);
    if (this->pinFwd1 == 255 || this->pinFwd2 == 255) {
        return;
    }
    if (speed1 > 0) {
        digitalWrite(this->pinFwd1, HIGH);
        digitalWrite(this->pinBwd1, LOW);
    } else {
        digitalWrite(this->pinFwd1, LOW);
        digitalWrite(this->pinBwd1, HIGH);
    }
    analogWrite(this->pinSpeed1, abs(this->denormalize(speed1)));

    if (speed2 > 0) {
        digitalWrite(this->pinFwd2, HIGH);
        digitalWrite(this->pinBwd2, LOW);
    } else {
        digitalWrite(this->pinFwd2, LOW);
        digitalWrite(this->pinBwd2, HIGH);
    }
    analogWrite(this->pinSpeed2, abs(this->denormalize(speed2)));
}

void DCMotor::setRange(int range) {
    this->range = range;
}
