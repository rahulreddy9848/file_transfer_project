#ifndef SOCKET_UTILS_HPP
#define SOCKET_UTILS_HPP

#include <iostream>
#include <string>
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <unistd.h>     
#include <netdb.h>
#include <fstream>
using namespace std;

bool createSocket(int &socket1);
bool bindSocket(int &socket1, int portno, std::string ip_address);
bool listenConnection(int &socket1, int backlog);
int acceptConnection(int &socket1);
bool connectToServer(int &socket1, int port, std::string ip);

#endif