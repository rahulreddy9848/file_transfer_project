#ifndef TRANSFER_LOGIC_HPP
#define TRANSFER_LOGIC_HPP

#include <iostream>
#include <string>
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <unistd.h>     
#include <netdb.h>
#include<fstream>
using namespace std;

bool sendFile(int socket, string filepath);
bool receiveFile(int socket, string filepath);

#endif
