#include "transfer_logic.hpp"
#include "bit_packing_functions.hpp"
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
    long presentBytes = 0;
    while(file){
        file.read(buffer, sizeof(buffer));
        streamsize bytesRead = file.gcount();
        if(bytesRead> 0){
            vector<uint8_t> compressed = compressVector(buffer, bytesRead);
            int sent = send(socket, compressed.data(), compressed.size(), 0);
            if(sent == -1){
                file.close();
                cout<<"File failed to send"<<endl;
                return false;
            }
            presentBytes += bytesRead;
            float percentage = ((float)presentBytes / (float)fileSize) * 100.0f;
            cout<<"\rSent: " << (int)percentage << "%"<<flush;
        }
    }
    cout<<endl;
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
    long totalReceived = 0;

    while((totalReceived < fileSize)){
        long toRead = min((long)sizeof(buffer), fileSize - totalReceived);
        vector<uint8_t> compressed(toRead);        
        long bytesReceived = recv(socket, (char*)compressed.data(), toRead, 0);
        long decompressedSize = bytesReceived * 8;
        if(decompressedSize + totalReceived > fileSize){
            decompressedSize = fileSize - totalReceived;
        }
        char decompressed_Buffer[decompressedSize];
        decompressVector(compressed, decompressed_Buffer, bytesReceived);
        file.write(decompressed_Buffer, decompressedSize);
        totalReceived += decompressedSize;
        float percentage = ((float)totalReceived / (float)fileSize) * 100.0f;
        cout<<"\rReceived: " << (int)percentage << "%"<<flush;
        if(totalReceived == fileSize)
            break;
    }
    cout<<endl;
    file.close();
    return true;
}