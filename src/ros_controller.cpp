#include "ros_controller.h"

ROSController::ROSController() {
    this->nPublishers = 0;
}

void ROSController::setMaster(String ip, int port) {
    Serial.println("setMaster");
    this->masterIP.fromString(ip);
    this->masterPort = port;
}

void ROSController::start() {
    Serial.println("start");
    this->nh.getHardware()->setConnection(this->masterIP, this->masterPort);
    this->nh.initNode();
}

ros::Publisher *ROSController::getPublisher(int handle) {
     return this->publishers[handle];
 }

int ROSController::advertisePublisher(const char *topicName, ros::Msg *msg) {
    if (this->nPublishers > 10) {
        return -1;
    }
    ros::Publisher *p = new ros::Publisher(topicName, msg);
    this->publishers[this->nPublishers] = p;
    this->nh.advertise(*(this->publishers[this->nPublishers]));
    return this->nPublishers++;
}

void ROSController::publish(int handle, ros::Msg *msg) {
    this->publishers[handle]->publish(msg);
}

void ROSController::spinOnce() {
    this->nh.spinOnce();
}