#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

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

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}