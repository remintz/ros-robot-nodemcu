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

        template <class A, class B>
        int subscribe(const char *topicName, A callback) {
            if (this->nSubscribers > 10) {
                return -1;
            }
            this->subscribers[this->nSubscribers] = new ros::Subscriber<B>(topicName, callback);
            this->nh.subscribe(*(this->subscribers[this->nSubscribers]));
            return this->nSubscribers++;
        }

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
