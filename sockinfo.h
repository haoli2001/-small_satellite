#ifndef SOCKINFO_H
#define SOCKINFO_H
#include <windows.h>
#include <winsock2.h>
struct sockinfo
{
    struct sockaddr_in addr;
    SOCKET clientsocket;

};
#endif // SOCKINFO_H
