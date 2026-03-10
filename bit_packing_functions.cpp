#include "bit_packing_functions.hpp"

vector<uint8_t> compressVector(char buffer[], long bytesRead){
    vector<uint8_t> compressed((bytesRead + 7 - 1)/8, 0);
    for(int i = 0; i < bytesRead;i++){
        if(buffer[i] == '1'){
            compressed[i/8] |= (1 << (7 - (i % 8)));
        }
    }
    return compressed;
} 

void decompressVector(vector<uint8_t>& compressed, char restored[], long bytesRead){
    for(int i = 0; i < bytesRead;i++){
        uint8_t byte = compressed[i/8];
        int bit = (byte >> (7 - (i % 8))) & 1;
        restored[i] = bit ? '1' : '0';
    } 
    return;
}