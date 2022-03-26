#include "visualizer.h"

Visualizer::Visualizer(std::string addr="127.0.0.1", 
                        int port=5000, std::string protocol="generic", bool NO_FG=false){
    this->addr = addr;
    this->port = port;
    this->protocol = protocol;

    if(!NO_FG) Visualizer::init();
}

int Visualizer::init(){
            // Launching FlightGear configured for UDP
            this->launch_fg("f18", "60", this->addr, std::to_string(this->port), this->protocol);
            this->udp_connect = new UDPConnect((char *) this->addr.c_str(), this->port);
            this->pkt_len = sizeof(this->pkt);
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
            cmd << " --fg-aircraft=/home/`whoami`/.fgfs/Aircraft/f18 ";
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

int Visualizer::send_fg(const double* x, const double* cntl){
    this->pkt.v     = x[0];
    this->pkt.alpha = x[1]*180/M_PI;
    this->pkt.beta  = x[2]*180/M_PI;
    this->pkt.p     = x[3]*180/M_PI;
    this->pkt.q     = x[4]*180/M_PI;
    this->pkt.r     = x[5]*180/M_PI;
    this->pkt.roll  = x[6]*180/M_PI;
    this->pkt.pitch = x[7]*180/M_PI;
    this->pkt.hdg   = x[8]*180/M_PI;
    this->pkt.lat   = x[9]/111139;
    this->pkt.lon   = x[10]/111139;
    this->pkt.alt   = x[11];

    this->pkt.elevator = cntl[0];
    // this->pkt.elevator = cntl[1];
    this->pkt.aileronl = cntl[2];
    this->pkt.aileronr = cntl[2]*-1;
    this->pkt.rudder   = cntl[3];
    this->pkt.throttle = cntl[4];
    // this->pkt.elevator = cntl[5];

    int ret = this->udp_connect->send(&this->pkt, this->pkt_len);
    // system("sleep 0.01");
    return ret;
}