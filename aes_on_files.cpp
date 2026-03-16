#include "rijndael.hpp"
#include <fstream>

bool encrypt_file(string filepath, string new_filepath, string key){
    vector<char> buffer(1048576 * 8);
    ifstream file_read(filepath, ios :: binary|ios::ate);
    ofstream file_write(new_filepath, ios::binary | ios::beg);
    long filesize = file_read.tellg();
    file_write.write((char*)&filesize, sizeof(filesize));   
    file_read.seekg(0, ios::beg);
    long long buffer_encrypted = 0;
    long long pres = 0;
    while(file_read){
        file_read.read(buffer.data(), buffer.size());
        streamsize bytes_read = file_read.gcount();
        char temp[16];
        int n = bytes_read;
        int iter = (n + 15)/16;
        buffer_encrypted = 0;
        pres = 0;
        while(buffer_encrypted < n){
            long long block = min((long long)16, (long long)(bytes_read - buffer_encrypted));
            memcpy(temp, &buffer[pres], block);
            buffer_encrypted += block;
            string temp_string(temp, block);
            string ct = AES128_Encrytpion(temp_string, key);
            file_write.write(ct.c_str(), ct.size());
            pres += block;
        }

    }
    file_read.close();
    file_write.close();
    return true;
}

bool decrypt_file(string filepath, string new_filepath, string key){
    vector<char> buffer(1048576 * 8);
    ifstream file_read(filepath, ios :: binary|ios::ate);
    ofstream file_write(new_filepath, ios::binary | ios::beg);
    long filesize;
    file_read.seekg(0, ios::beg);
    file_read.read((char*)&filesize, sizeof(filesize));
    long long buffer_encrypted = 0;
    long long written = 0;
    long long pres = 0;
    while(file_read){
        file_read.read(buffer.data(), buffer.size());
        streamsize bytes_read = file_read.gcount();
        char temp[16];
        int n = bytes_read;
        int iter = (n + 15)/16;
        buffer_encrypted = 0;
        pres = 0;
        while(buffer_encrypted < n){
            long long block = min((long long)16, (long long)(bytes_read - buffer_encrypted));
            memcpy(temp, &buffer[pres], block);
            buffer_encrypted += block;
            string temp_string(temp, block);
            string ct = AES128_Decrytpion(temp_string, key);
            long long to_write = min((long long)ct.size(), filesize - written);
            file_write.write(ct.c_str(), to_write);
            written += to_write;
            pres += block;
        }


    }
    file_read.close();
    file_write.close();
    return true;
}

int main(){
    string filepath;
    string encrypted_filepath, decrypted_filepath;
    string key;
    cout<<"Enter filename to encrypt: ";
    cin>>filepath;
    cout<<"Enter path to store encrypted file: ";
    cin>>encrypted_filepath;
    cout<<"Enter 16 character key for encryption and decryption: ";
    cin>>key;
    cout<<"Encrypting.";
    if(encrypt_file(filepath, encrypted_filepath, key)){
        cout<<"File encrypted!!"<<endl;
    }
    cout<<"Enter filepath to store decrypted file: ";
    cin>>decrypted_filepath;
    cout<<"Decrypting."<<endl;
    if(decrypt_file(encrypted_filepath, decrypted_filepath, key)){
        cout<<"File decrypted.";
    }
    return 0;
}
