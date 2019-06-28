#ifndef _ROS_arduino_hello_world_hello_h
#define _ROS_arduino_hello_world_hello_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace arduino_hello_world
{

  class hello : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef const char* _name_type;
      _name_type name;
      typedef int64_t _age_type;
      _age_type age;

    hello():
      header(),
      name(""),
      age(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      union {
        int64_t real;
        uint64_t base;
      } u_age;
      u_age.real = this->age;
      *(outbuffer + offset + 0) = (u_age.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_age.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_age.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_age.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_age.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_age.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_age.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_age.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->age);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
      union {
        int64_t real;
        uint64_t base;
      } u_age;
      u_age.base = 0;
      u_age.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_age.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_age.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_age.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_age.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_age.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_age.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_age.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->age = u_age.real;
      offset += sizeof(this->age);
     return offset;
    }

    const char * getType(){ return "arduino_hello_world/hello"; };
    const char * getMD5(){ return "51c543072a1cace02c7905d2917c7957"; };

  };

}
#endif
