#include "transfer_logic.hpp"
char buffer[4096];

bool sendFile(int socket, string filepath){
    ifstream file(filepath, ios::binary | ios:: ate);
    long fileSize = file.tellg();
    file.seekg(0, ios::beg);
    
    if (send(socket, (char*)&fileSize, sizeof(fileSize), 0) == -1) {
        cout<<"File failed to send"<<endl;
        file.close();
        return false;
    }

    while(file){
        file.read(buffer, sizeof(buffer));
        streamsize bytesRead = file.gcount();
        int presentBytes = 0;
        if(bytesRead> 0){
            int sent = send(socket, buffer, bytesRead, 0);
            if(sent == -1){
                file.close();
                cout<<"File failed to send"<<endl;
                return false;
            }
            presentBytes += bytesRead;
            float percentage = (float)((presentBytes / fileSize) * 100);
            cout<<"\rSent: " << percentage << "%"<<flush;
        }
    }

    return true;
}

bool receiveFile(int socket, string filepath){
    ofstream file(filepath, ios::binary);
    if(!file.is_open())
        return false;
    long fileSize;
    if(recv(socket, (char*)&fileSize, sizeof(fileSize), 0) == -1){
        file.close();
        cout<<"Failed to receive file"<<endl;
        return false;
    }
    char buffer[4096];
    int totalReceived;

    while((totalReceived < fileSize)){
        int toRead = min((long)sizeof(buffer), fileSize - totalReceived);
        int bytesReceived = recv(socket, buffer, toRead, 0);
        file.write(buffer, bytesReceived);
        totalReceived += bytesReceived;
        float percentage = (float)((totalReceived / fileSize) * 100);
        cout<<"\rReceived: " << percentage << "%"<<flush;
    }
    file.close();
    return true;
}