#include "include/ServerCon.h"
#include <iostream>
#include <sstream>
#include "include/AVLNode.h"




int main() {
    // set up connection
    ServerCon con {1234};

    while ( true ) {
        int client_fd = con.accpet_request();
        if ( client_fd < 0 ) continue;

        // one client at a time, open a new connection next time
        while ( true ) {
            int err = con.process_request(client_fd);

            if ( err ) break;
        }

        con.close_request(client_fd);
    }
}


