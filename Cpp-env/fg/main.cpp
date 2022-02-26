#include "main.h"
#include "UDPConnect.h"


void launch_fg(const std::string& aircraft, const std::string& rate, 
                const std::string& server, const std::string& port, 
                const std::string& protocol){
    // Start command stringstream
    std::cout << "Starting FlightGear.. please wait\n";
    std::string run_fg;
    run_fg = "fgfs";
    std::stringstream cmd(run_fg);

    // Check if already running
    if (strlen(exec("ps -h | grep '[f]gfs'").c_str())>0){
        std::cout << "Already running.\n";
        return;
    }

    // constructing the command
    // UDP - Native
    // cmd << run_fg;
    // cmd << " --fg-aircraft=/home/willcmc/.fgfs/Aircraft/f18 ";
    // cmd << " --aircraft=";
    // cmd << aircraft;
    // cmd << " --native-fdm=";
    // cmd << "socket,";
    // cmd << "in,";
    // cmd << rate << ",";
    // cmd << server << ",";
    // cmd << port << ",";
    // cmd << protocol;
    // cmd << " --fdm=null";
    // cmd << " --disable-ai-traffic";
    // cmd << " --disable-real-weather-fetch";
    // cmd << " --timeofday=morning";
    // cmd << " --disable-sound &";

    // UDP - Generic
    cmd << run_fg;
    cmd << " --fg-aircraft=/home/willcmc/.fgfs/Aircraft/f18 ";
    cmd << " --aircraft=";
    cmd << aircraft;
    cmd << " --generic=";
    cmd << "socket,";
    cmd << "in,";
    cmd << rate << ",";
    cmd << server << ",";
    cmd << port << ",";
    cmd << "udp" << ",";
    cmd << protocol;
    cmd << " --fdm=null";
    cmd << " --disable-ai-traffic";
    cmd << " --disable-real-weather-fetch";
    cmd << " --timeofday=morning";
    cmd << " --disable-sound &";

    system(cmd.str().c_str()); // Could be replaced by popen
    system("sleep 15"); // Hopefully fg starts in 15 seconds
}


int main()
{
    std::string addr = "127.0.0.1";
    int port = 5000;

    // Launching FlightGear configured for UDP
    launch_fg("f18", "60", addr, std::to_string(port), "generic");

    UDPConnect *udp_connect;
    udp_connect = new UDPConnect((char *) addr.c_str(), port);
    
    GenericPacket pkt;
    size_t pkt_len = sizeof(pkt);

    for(int t = 0; t < 100; t++){
        pkt.throttle = 0.0;
        pkt.aileronl = 1.0;
        pkt.aileronr = t%2;
        pkt.elevator = 0.0;
        pkt.rudder   = 0.0;
        pkt.alt      = 1000;

        udp_connect->send(&pkt, pkt_len);
        std::cout << t << '\n';
        system("sleep 0.01");
    }
    return 0;
}
