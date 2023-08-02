#ifndef HEADER_SERVERCONNECTION_H
#define HEADER_SERVERCONNECTION_H

#include "Connection.h"
#include "../include/Scanner.h"
#include "../include/Parser.h"

class ServerCon: public Connection {
    public:
        ServerCon(int port);

        int accpet_request();
        int process_request(int connfd);
        void close_request(int connfd);
};





#endif