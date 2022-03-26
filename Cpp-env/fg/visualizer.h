#ifndef VISUALIZER_H
#define VISUALIZER_H
#pragma once

#include <bits/stdc++.h>
#include <sstream>
#include <memory>
#include <string.h>
#include "UDPConnect.h"


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

class Visualizer{
    private:
        std::string addr;  
        std::string protocol;
        int port;
        UDPConnect* udp_connect;
        GenericPacket pkt;
        size_t pkt_len;
        
        int init();

        void launch_fg(const std::string& aircraft, const std::string& rate, 
                        const std::string& server, const std::string& port, 
                        const std::string& protocol);
    public:
        Visualizer(std::string addr, int port, std::string protocol, bool NO_FG);
        int send_fg(const double* x, const double* cntl);
        std::string cmd_exec(const char* cmd);
};

#endif