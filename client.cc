#include "include/ClientCon.h"   
#include <iostream>

int main() {
    // set up connection
    ClientCon con {1234};

    std::string line;
    while ( std::getline(std::cin, line) ) {
        int err = con.send_query(line.c_str());
        
        if ( err ) {
            std::cerr << "Error" << std::endl;
            break;
        }
    }


    // Close the socket after all queries are sent or on error
    con.close_con();
    return 0;
}


