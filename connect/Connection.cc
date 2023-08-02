#include "../include/Connection.h"


int Connection::read_full(int fd, char *buf, size_t n) {
    while ( n > 0) {
        ssize_t rv = read(fd, buf, n);
        if ( rv <= 0 ) {
            return 1;
        }

        assert((size_t)rv <= n);
        n -= (size_t)rv;
        buf += rv;
    }
    return 0;
}

int Connection::write_full(int fd, const char *buf, size_t n) {
    while ( n > 0) {
        ssize_t rv = write(fd, buf, n);
        if ( rv <= 0 ) {
            return 1;
        }

        assert((size_t)rv <= n);
        n -= (size_t)rv;
        buf += rv;
    }
    return 0;
}


void die(std::string msg) {
    std::cerr << "Error: " << std::to_string(errno) << " " << msg << std::endl;
}