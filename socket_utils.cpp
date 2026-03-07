#include "socket_utils.hpp"

bool createSocket(int &socket1){
    socket1 = -1;
    socket1 = socket(PF_INET, SOCK_STREAM, 0);
    if(socket1 == -1){
        cout<<"Error while cretaing socket"<<endl;
        return false;
    }
    else{
        cout<<"Socket has been created"<<endl;
        return true;
    }
}

bool bindSocket(int &socket, int portno, string ip_address){
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip_address.c_str());
    addr.sin_port = htons(portno);

    if (::bind(socket, (struct sockaddr *)&addr, sizeof(addr)) == -1){
        cout<<"Error binding socket"<<endl;
        return false;
    }
    else{
        cout<<"Socket Binded Successfully"<<endl;
        return true;
    }
}

bool listenConnection(int &socket, int backlog){
    if (listen(socket, backlog)== -1){
        cout<<"Error while listening for connections"<<endl;
        return false;
    }
    else{
        cout<<"Listening for connections"<<endl;
        return true;
    }
}

int acceptConnection(int &socket){
    int accept_socket = accept(socket, NULL, NULL);
    if(accept_socket == -1){
        cout<<"Accept connection failed for socket"<<endl;
        return -1;
    }
    else{
        cout<<"Accepted connection"<<endl;
        return accept_socket;
    }
}

bool connectToServer(int &socket1, int port, string ip)
{
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());
    server_addr.sin_port = htons(port);

    if (connect(socket1, (sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        cout << "Client connect failed:" << endl;
;
        return false;
    }
    else
    {
        cout << "Client connect() is ok" << endl;
        cout << "Client can start sending and receiving data." << endl;
    }
    return true;
}
