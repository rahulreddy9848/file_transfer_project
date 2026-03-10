#ifndef BIT_PACKING_FUNCTIONS
#define BIT_PACKING_FUNCTIONS

#include <iostream>
#include <random>
#include <vector>
using namespace std;

vector<uint8_t> compressVector(char buffer[], long bytesRead);
void decompressVector(vector<uint8_t>& compressed, char restored[], long bytesRead);


#endif