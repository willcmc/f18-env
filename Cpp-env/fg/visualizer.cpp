#include "visualizer.h"

Visualizer::Visualizer(std::string addr="127.0.0.1", 
                        int port=5000, std::string protocol="generic"){
    this->addr = addr;
    this->port = port;
    this->protocol = protocol;

    Visualizer::init();
}

int Visualizer::init(){
            // Launching FlightGear configured for UDP
            this->launch_fg("f18", "60", this->addr, 
                        std::to_string(this->port), 
                        this->protocol);

            UDPConnect *udp_connect;
            udp_connect = new UDPConnect((char *) this->addr.c_str(), this->port);
            
            GenericPacket pkt;
            size_t pkt_len = sizeof(pkt);

            for(int t = 0; t < 10; t++){
                pkt.throttle = 0.0;
                pkt.aileronl = 0.0;
                pkt.aileronr = 0.0;
                pkt.elevator = 0.0;
                pkt.rudder   = 0.0;
                pkt.alt      = 1000;

                udp_connect->send(&pkt, pkt_len);
                std::cout << t << '\n';
                system("sleep 0.01");
            }
            return 0;
}

std::string Visualizer::cmd_exec(const char* cmd) {
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

void Visualizer::launch_fg(const std::string& aircraft, const std::string& rate, 
                        const std::string& server, const std::string& port, 
                        const std::string& protocol){
            // Start command stringstream
            std::cout << "Starting FlightGear.. please wait\n";
            std::string run_fg;
            run_fg = "fgfs";
            std::stringstream cmd(run_fg);

            // Check if already running
            if (strlen(this->cmd_exec("ps -h | grep '[f]gfs'").c_str())>0){
                std::cout << "Already running.\n";
                return;
            }

            // Constructing the command
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