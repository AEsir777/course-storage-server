#ifndef HEADER_CLIENTCONNECTION_H
#define HEADER_CLIENTCONNECTION_H

#include "Connection.h"

class ClientCon: public Connection {
    public:
        ClientCon(int port);

        int send_query(const char * text);
        void close_con();
};



#endif