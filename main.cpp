#include <iostream>
#include "socket_utils.hpp"
#include "transfer_logic.hpp"
using namespace std;

int main(){
    cout<<"Enter s/c for Server/Client: ";
    char choice;
    cin>>choice;
    int serverSocket, clientSocket, accSocket;
    if(choice == 's'){
        string ip_address;
        cout<<"Enter your IP address: ";
        cin>>ip_address;
        int portno;
        cout<<"Enter the port number: ";
        cin>>portno;
        if(createSocket(serverSocket) == false){
            cout<<"Server Socket Creation failed."<<endl;
            return 0;
        }
        else{
            cout<<"Server Socket created successfully."<<endl;
        }
        
        if(bindSocket(serverSocket, portno, ip_address) == false){
            cout<<"Binding server socket failed"<<endl;
            return 0;
        }
        else{
            cout<<"Binding of server socket completed"<<endl;
        }

        if(listenConnection(serverSocket, 2) == false){
            cout<<"Server failed to listen for connections"<<endl;
            return 0;
        }
        else{
            cout<<"Server is listening for connections: "<<endl;
        }
        
        accSocket = acceptConnection(serverSocket);

        if(accSocket == -1){
            cout<<"Connection failed"<<endl;
            close(accSocket);
            return 0;
        }else{
            cout<<"Connection established"<<endl;
            
        }

    }

    if(choice == 'c'){
        string ip_address;
        cout<<"Enter servers's IP address: ";
        cin>>ip_address;
        int portno;
        cout<<"Enter port number: ";
        cin>>portno;
        if(createSocket(clientSocket) == false){
            cout<<"client Socket Creation failed."<<endl;
            return 0;
        }
        else{
            cout<<"client Socket created successfully."<<endl;
        }        

        if(connectToServer(clientSocket, portno,ip_address) == false){
            cout<<"Client failed to connect to server"<<endl;
            return 0;
        }
        else{
            cout<<"Client has successfully connected to the server"<<endl;

        }
    }
    while(1){
        int t_choice;
        cout<<"Choose what you want to do: "<<endl;
        cout<<"1. Send File"<<endl;
        cout<<"2. Receive File"<<endl;
        cout<<"3. Exit"<<endl;
        cin>>t_choice;
        if(t_choice == 1){
            string filepath;
            cout<<"Enter path of file to send: ";
            cin>>filepath;
            if(choice == 's'){
                if(sendFile(accSocket, filepath)){
                    cout<<"File sent successfuly"<<endl;
                }
            }
            else{
                if(sendFile(clientSocket, filepath)){
                    cout<<"File sent successfuly"<<endl;
                }
            }
        }
        else if(t_choice == 2){
            string filepath;
            cout<<"Enter where you want to store the received file: ";
            cin>>filepath;
            if(choice == 'c'){
                if(receiveFile(clientSocket, filepath)){
                    cout<<"File received succesfully"<<endl;
                }
            }
            else{
                if(receiveFile(accSocket, filepath)){
                    cout<<"File received succesfully"<<endl;
                }
            }
        }
        else if(t_choice == 3){
            if(choice == 'c'){
                close(clientSocket);
            }
            if(choice == 's'){
                close(accSocket);
            }
            return 0;
        }
        else{
            cout<<"Enter 1, 2 or 3"<<endl;
        }
    }
    return 0;
}