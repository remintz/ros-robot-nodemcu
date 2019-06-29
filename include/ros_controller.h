#ifndef ROS_CONTROLLER_H
#define ROS_CONTROLLER_H

#include <ros.h>
#include <std_msgs/String.h>
#include <arduino_hello_world/hello.h>

class ROSController {
    public:
        ROSController();
        void setMaster(String ip, int port);
        void start();
        int advertisePublisher(const char *topicName, ros::Msg *msg); 
        ros::Publisher *getPublisher(int handle);
        void publish(int handle, ros::Msg *msg);
        void spinOnce(void);

    private:
        ros::NodeHandle nh;
        IPAddress masterIP;
        int masterPort;
        ros::Publisher *publishers[10];
        int nPublishers;
};

#endif
