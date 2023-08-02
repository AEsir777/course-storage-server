#include "../include/ClientCon.h"

ClientCon::ClientCon(int port) {
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if ( fd < 0 ) {
        die("socket()");
    }


    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(port);
    addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK);

    // connect to server
    int rv = connect(fd, (const sockaddr *) &addr, sizeof(addr));

    if ( rv ) {
        die("connect()");
    }
}

int ClientCon::send_query(const char * text) {
    // print the query
    std::cout << "Query is: " << text << std::endl;

    int len = strlen(text);
    if ( len > max_msg ) return 1;

    // write buffer
    char wbuf[4 + max_msg];
    memcpy(wbuf, &len, 4); // first 4 bytes length
    memcpy(&wbuf[4], text, len); // then 4 bytes content
    
    int err = write_full(fd, wbuf, 4 + len);
    if ( err ) throw WriteError{};

    // read from server
    char rbuf[4 + max_msg + 1];
    errno = 0;
    
    // read 4 bytes length
    err = read_full(fd, rbuf, 4);
    if ( err ) throw ReadError{};
    
    memcpy(&len, rbuf, 4); 
    if ( len > max_msg ) throw InputTooLong{};

    // body
    err = read_full(fd, &rbuf[4], len);
    if ( err ) throw ReadError{};

    rbuf[4 + len] = '\0';
    std::cout << "Received from Server: "  << &rbuf[4] << std::endl;

    return 0;
}

void ClientCon::close_con() {
    close(fd);
}
