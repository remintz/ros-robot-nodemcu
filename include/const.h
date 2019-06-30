#ifndef CONST_H
#define CONST_H

#include "Arduino.h"

// Motor Pins
#define LEFT_MOTOR_FWD D1
#define LEFT_MOTOR_BWD D2
#define LEFT_MOTOR_PWM D0

#define RIGHT_MOTOR_FWD D3
#define RIGHT_MOTOR_BWD D4
#define RIGHT_MOTOR_PWM D5

#define LEFT_MOTOR  1
#define RIGHT_MOTOR 2

#define PWM_RANGE 1024  // for the NODEMCU

#define ROS_MASTER_IP "192.168.3.17" /* ROS Master IP */
#define ROS_MASTER_PORT 11411

#define WIFI_TRY_TIMEOUT    10000
#define WIFI_SSID           "dramas_EXT"
#define WIFI_PASSWORD       "seraquenada"
#endif