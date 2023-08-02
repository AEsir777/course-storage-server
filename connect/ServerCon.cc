#include "../include/ServerCon.h"

ServerCon::ServerCon(int port) {
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if ( fd < 0 ) {
        die("socket()");
    }

    // server
    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(port);
    addr.sin_addr.s_addr = ntohl(0);
    int rv = bind(fd, (const sockaddr *) &addr, sizeof(addr));

    if ( rv ) {
        die("bind()");
    }

    // listen to connections from client
    rv = listen(fd, SOMAXCONN);
    if ( rv ) {
        die("listen()");
    }
    std::cout << "Listening query on porte " << std::to_string(port) << std::endl;
}

int ServerCon::accpet_request() {
    sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    int connfd = accept(fd, (sockaddr *) &client_addr, &len);
    
    return connfd;
}


int ServerCon::process_request(int connfd) {
    // 4 = int size
    // read in len
    char rbuf[4 + max_msg + 1];
    errno = 0;

    int err = read_full(connfd, rbuf, 4);
    if ( err ) {
        if ( errno == 0 ) std::cerr << "EOF" << std::endl;
        else throw ReadError{};
        return err;
    }

    int len = 0;
    memcpy(&len, rbuf, 4); // copy first 4 bytes into len
    if ( len > max_msg ) {
        throw InputTooLong{};
    }

    // read in body
    err = read_full(connfd, &rbuf[4], len);
    if ( err ) throw ReadError{};

    // print the read words
    rbuf[4 + len] = '\0';
    std::cout << "Input Query: "  << &rbuf[4] << std::endl;

    // scan the query
    Dfa scanner{};
    std::vector<std::pair<Dfa::State, std::string>> tokens = scanner.simplifiedMaximalMunch(&rbuf[4]);
    
    #ifdef DEBUG
        printToken(tokens);
    #endif

    // parse the query
    Parser parser {tokens};

    
    #ifdef DEBUG
        parser.printParseTree();
    #endif


    // reply stuff
    const char reply[] = "Input received";
    char wbuf[4 + sizeof(reply)];
    len = strlen(reply);
    memcpy(wbuf, &len, 4); 
    memcpy(&wbuf[4], reply, len); 
    return write_full(connfd, wbuf, 4 + len);
}


void ServerCon::close_request(int connfd) {
    close(connfd);
}