#ifndef VISUALIZER_H
#define VISUALIZER_H
#pragma once

#include <iostream>
#include <sstream>
#include <memory>
#include <string.h>
#include "UDPConnect.h"

class Visualizer{
    private:
        std::string addr;  
        std::string protocol;
        int port;
        
        int init();

        void launch_fg(const std::string& aircraft, const std::string& rate, 
                        const std::string& server, const std::string& port, 
                        const std::string& protocol);
    public:
        Visualizer(std::string addr, int port, std::string protocol);
        std::string cmd_exec(const char* cmd);
};

#pragma pack(push, 1)
struct GenericPacket{
    double throttle;
    double aileronl;
    double aileronr;
    double elevator;
    double rudder;
    double lat;
    double lon; // long is reserved :)
    double alt;
    double roll;
    double pitch;
    double hdg;
    double p;
    double q;
    double r;
    double beta;
    double alpha;
    double v;
};
#pragma pack(pop)

#endif