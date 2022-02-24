#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <memory.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "UDPConnect.h"


void launch_fg(const std::string& aircraft, const std::string& rate, const std::string& server, const std::string& port, const std::string& protocol){
    std::string run_fg;
    run_fg = "fgfs";
    std::stringstream cmd(run_fg);

    // constructing the command
    cmd << run_fg;
    cmd << " --fg-aircraft=/home/willcmc/.fgfs/Aircraft/f18 ";
    cmd << " --aircraft=";
    cmd << aircraft;
    cmd << " --native-fdm=";
    cmd << "socket,";
    cmd << "in,";
    cmd << rate << ",";
    cmd << server << ",";
    cmd << port << ",";
    cmd << protocol;
    cmd << " --fdm=null";
    cmd << " --disable-ai-traffic";
    cmd << " --disable-real-weather-fetch";
    cmd << " --timeofday=morning";
    cmd << " --disable-sound &";

    // std::cout << cmd.str();
    system(cmd.str().c_str());
}

struct Controls{
    float aileron, elevator, rudder, throttle;
};

struct States{
    float x, y;
};


int main()
{
    std::string addr = "127.0.0.1";
    int port = 5000;

    // Launching FlightGear configured for UDP
    launch_fg("f18", "60", addr, std::to_string(port), "udp");
    system("sleep 10");

    UDPConnect *udp_connect;
    udp_connect = new UDPConnect((char *) addr.c_str(), port);
    
    Controls ctrl;

    ctrl.aileron  = 1.0;
    ctrl.elevator = 0.0;
    ctrl.rudder   = 0.0;
    ctrl.throttle = 0.0;

    size_t msg_length = sizeof(ctrl);

    for(int t = 0; t < 1000; t++){
        udp_connect->send(&ctrl, msg_length);
        std::cout << t << '\n';
        system("sleep 0.1");
    }

    return 0;
}
