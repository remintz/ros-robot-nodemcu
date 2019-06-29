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

#define ROS_MASTER_IP "192.168.3.17" /* ROS Master IP */
#define ROS_MASTER_PORT 11411

ROSController rosControl = ROSController();

std_msgs::String *str_msg = new std_msgs::String();
std_msgs::String *str_msg_rcvd = new std_msgs::String();
arduino_hello_world::hello *hello_msg = new arduino_hello_world::hello();

char hello_str[13] = "hello world!";
char name_str[20] = "Renato";

int handleChatterPublisher;
int handleHelloPublisher;
int handleSubscriber;

void inputCallback(const std_msgs::String& msg) {
  Serial.println(msg.data);
}

void setup_ros() {
  Serial.println("setup_ros");
  rosControl.setMaster(ROS_MASTER_IP, ROS_MASTER_PORT);
  handleChatterPublisher = rosControl.advertisePublisher("chatter", *&str_msg);
  handleHelloPublisher = rosControl.advertisePublisher("hello", *&hello_msg);
  handleSubscriber = rosControl.subscribe("input", inputCallback);
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
  delay(1000);
}
