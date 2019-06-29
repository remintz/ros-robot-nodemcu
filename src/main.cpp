/*
* rosserial Publisher Example
* Prints "hello world!"
*/

#include <ros.h>
#include <std_msgs/String.h>
#include <arduino_hello_world/hello.h>

/* ESP Library */
#include "ESP8266WiFi.h"

#define ROS_MASTER_IP "192.168.3.17" /* ROS Master IP */
#define ROS_MASTER_PORT 11411

ros::NodeHandle  nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

arduino_hello_world::hello hello_msg;
ros::Publisher hello("hello", &hello_msg);

char hello_str[13] = "hello world!";
char name_str[20] = "Renato";

void setup_ros() {
  Serial.println("setup_ros");
  IPAddress ROSMasterAddress;
  ROSMasterAddress.fromString(ROS_MASTER_IP);
  nh.getHardware()->setConnection(ROSMasterAddress, ROS_MASTER_PORT);
  nh.initNode();
  nh.advertise(chatter);
  nh.advertise(hello);
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
  str_msg.data = hello_str;

  hello_msg.header.frame_id = name_str;
  hello_msg.header.seq = 1234;
  hello_msg.name = name_str;
  hello_msg.age = 60;

  chatter.publish( &str_msg );
  hello.publish( &hello_msg );
  Serial.println("mandou");
  nh.spinOnce();
  delay(1000);
}
