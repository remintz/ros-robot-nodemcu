/*
* rosserial Publisher Example
* Prints "hello world!"
*/

#include <ros.h>
#include <std_msgs/String.h>
#include <arduino_hello_world/hello.h>

/* ESP Library */
#include "ESP8266WiFi.h"
#include "ros_controller.h"
#include "dcmotor.h"

#define ROS_MASTER_IP "192.168.3.17" /* ROS Master IP */
#define ROS_MASTER_PORT 11411

ROSController rosControl = ROSController();
DCMotor dcMotor = DCMotor();

std_msgs::String *str_msg = new std_msgs::String();
std_msgs::String *str_msg_rcvd = new std_msgs::String();
arduino_hello_world::hello *hello_msg = new arduino_hello_world::hello();

char hello_str[13] = "hello world!";
char name_str[20] = "Renato";

int handleChatterPublisher;
int handleHelloPublisher;
int handleSubscriber;

int motorMode = 0;

void inputCallback(const std_msgs::String& msg) {
  Serial.println(msg.data);
}

void setup_ros() {
  Serial.println("setup_ros");
  rosControl.setMaster(ROS_MASTER_IP, ROS_MASTER_PORT);
  handleChatterPublisher = rosControl.advertisePublisher("chatter", *&str_msg);
  handleHelloPublisher = rosControl.advertisePublisher("hello", *&hello_msg);
  handleSubscriber = rosControl.subscribe<std_msgs::String>("input", inputCallback);
  rosControl.start();
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting");
  WiFi.begin("dramas_EXT", "seraquenada");
  int wifi_max_tries = 10000 / 100;
  bool wifi_connected = true;
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    if (wifi_max_tries-- <= 0) {
      wifi_connected = false;
      break;
    }
  }
  if (wifi_connected) {
    Serial.println("Wifi Connected");
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Could not connect to WIFI");
    exit(1);
  }
  setup_ros();
  dcMotor.attach(1, D1, D2, D0);
  dcMotor.attach(2, D3, D4, D5);
  dcMotor.setRange(1024);
}

void loop()
{
  Serial.println("loop");
  str_msg->data = hello_str;

  hello_msg->header.frame_id = name_str;
  hello_msg->header.seq = 1234;
  hello_msg->name = name_str;
  hello_msg->age = 60;

  rosControl.publish(handleChatterPublisher, str_msg);
  rosControl.publish(handleHelloPublisher, hello_msg);

  Serial.println("mandou");
  rosControl.spinOnce();

  switch (motorMode) {
    case 0:
      dcMotor.command(0, 0);
      break;
    case 1:
      dcMotor.command(100, 100);
      break;
    case 2:
      dcMotor.command(0, 0);
      break;
    case 3:
      dcMotor.command(-100, -100);
      break;
    case 4:
      dcMotor.command(0, 0);
      break;
    case 5:
      dcMotor.command(0, 100);
      break;
    case 6:
      dcMotor.command(0, 0);
      break;
    case 7:
      dcMotor.command(0, -100);
      break;
    case 8:
      dcMotor.command(0, 0);
      break;
    case 9:
      dcMotor.command(100, 0);
      break;
    case 10:
      dcMotor.command(0, 0);
      break;
    case 11:
      dcMotor.command(-100, 100);
      break;
    case 12:
      dcMotor.command(0, 0);
      break;
    case 13:
      dcMotor.command(100, -100);
      break;
  }
  if (++motorMode > 13) {
    motorMode = 0;
  }
  delay(5000);
}
