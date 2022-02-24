#include "UDPConnect.h"

// Save the IP Address and Port number
// And execute some magic to get everything
// ready for the first connection
UDPConnect::UDPConnect(char* ip_addr, int port) {
    this->ip_addr = ip_addr;
    this->port = port;
    this->boot();
}

// Close the Socket stream on destroy
UDPConnect::~UDPConnect() {
    this->closeStream();
}

// This is just a wrapper to sendto(), so I don't
// have to type the same code over and over again
int UDPConnect::send(const void* message, int size) {
    return sendto(
        this->socket_fd,
        message,
        size,
        MSG_CONFIRM,
        this->socket_addr,
        this->socket_addr_size
    ); 
}

// Close the Socket stream
int UDPConnect::closeStream() {
    return close(this->socket_fd);
}

// Get everything ready for a UDP Connectio 
void UDPConnect::boot() {
    // Creating a socket: AF_INET Family (IPv4) and Datagram (for UDP)
    this->socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    // Create the sockaddr_in struct
    this->socket_addr_in.sin_family = AF_INET;
    this->socket_addr_in.sin_port = htons(this->port);
    this->socket_addr_in.sin_addr.s_addr = inet_addr(this->ip_addr);

    // Determinate the size of the sockaddr_in struct
    this->socket_addr_size = sizeof(this->socket_addr_in);

    // Initialize a sockaddr struct pointer from sockaddr_in struct
    this->socket_addr = (struct sockaddr*)&this->socket_addr_in;
}