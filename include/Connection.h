#ifndef HEADER_CONNECTION_H
#define HEADER_CONNECTION_H

#include <sys/socket.h>   
#include <netinet/in.h>   
#include <arpa/inet.h>   
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <cassert>
#include <iostream>
#include <sstream>

class Connection {
    public:    
        int fd;
        sockaddr_in addr;
    
        // return -1 for error or EOF
        int read_full(int fd, char *buf, size_t n);
        int write_full(int fd, const char* buf, size_t n);
};

void die(std::string msg);
const int max_msg = 4096;

class ReadError {};
class WriteError {};
class InputTooLong {};

#endif