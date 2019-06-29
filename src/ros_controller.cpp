#include "ros_controller.h"

ROSController::ROSController() {
    this->nPublishers = 0;
    this->nSubscribers = 0;
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

int ROSController::subscribe(const char *topicName, ros::Subscriber<std_msgs::String>::CallbackT callback) {
    if (this->nSubscribers > 10) {
        return -1;
    }
    this->subscribers[this->nSubscribers] = new ros::Subscriber<std_msgs::String>(topicName, callback);
    this->nh.subscribe(*(this->subscribers[this->nSubscribers]));
}   

int ROSController::advertisePublisher(const char *topicName, ros::Msg *msg) {
    if (this->nPublishers > 10) {
        return -1;
    }
    this->publishers[this->nPublishers] = new ros::Publisher(topicName, msg);
    this->nh.advertise(*(this->publishers[this->nPublishers]));
    return this->nPublishers++;
}

void ROSController::publish(int handle, ros::Msg *msg) {
    this->publishers[handle]->publish(msg);
}

void ROSController::spinOnce() {
    this->nh.spinOnce();
}