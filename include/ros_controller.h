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
        int subscribe(const char *topicName, ros::Subscriber<std_msgs::String>::CallbackT callback);
        ros::Publisher *getPublisher(int handle);
        ros::Subscriber<ros::Msg> *getSubscriber(int handle);
        void publish(int handle, ros::Msg *msg);
        void spinOnce(void);

    private:
        ros::NodeHandle nh;
        IPAddress masterIP;
        int masterPort;
        ros::Publisher *publishers[10];
        ros::Subscriber<std_msgs::String> *subscribers[10];
        int nPublishers;
        int nSubscribers;
};

#endif
