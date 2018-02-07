#ifndef __SOCKET_H_
#define __SOCKET_H_

#include "common.h"

int Socket(const char *host, int clientPort);
#define ERR_EXIT(m) \
    do \
    { \
        perror(m); \
        exit(1); \
    } while(0)

#endif //__SOCKET_H_