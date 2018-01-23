#ifndef __SOCKET_H_
#define __SOCKET_H_

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>

int Socket(const char *host, int clientPort);
#define ERR_EXIT(m) \
    do \
    { \
        perror(m); \
        exit(1); \
    } while(0)

#endif //__SOCKET_H_