#include <iostream>
#include <vector>
using namespace std;

const unsigned char sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

const unsigned char inv_sbox[256] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

uint8_t matrix[4][4] = {
    {2,3,1,1},
    {1,2,3,1},
    {1,1,2,3},
    {3,1,1,2}
};

void peform_xor(vector<vector<uint8_t>>& state, vector<vector<uint8_t>> key_state){
    for(int i = 0; i < 4;i++){
        for(int j = 0; j < 4;j++){
            state[j][i] ^= key_state[i][j];
        }
    }
}

void sbox_substitution(vector<vector<uint8_t>>& state){
    for(int i = 0; i < 4;i++){
        for(int j = 0; j < 4;j++){
            state[i][j] = sbox[state[i][j]];
        }
    }
}

void shift_rows(vector<vector<uint8_t>>& state){
    vector<vector<uint8_t>> copy = state;
    state[1][0] = copy[1][1];
    state[1][1] = copy[1][2];
    state[1][2] = copy[1][3];
    state[1][3] = copy[1][0];
    state[2][0] = copy[2][2];
    state[2][1] = copy[2][3];
    state[2][2] = copy[2][0];
    state[2][3] = copy[2][1];
    state[3][0] = copy[3][3];
    state[3][1] = copy[3][0];
    state[3][2] = copy[3][1];
    state[3][3] = copy[3][2];
}

int multiplyElement(uint8_t num1, uint8_t num2){
    if(num2 == 1)
        return num1;
    else if(num2 == 2){
        uint8_t msb = num1 & 0x80;
        num1 = num1 << 1;
        if(msb){
            num1 = num1 ^ 0x1B;
        }
        return num1;
    }
    else if(num2 == 3){
        uint8_t temp = num1;
        uint8_t msb = num1 & 0x80;
        num1 = num1 << 1;
        if(msb){
            num1 = num1 ^ 0x1B;
        }
        num1 = num1 ^ temp;
        return num1;
    }
    return 0;
}


void mix_columns(vector<vector<uint8_t>>& state){
    uint8_t temp[4];
    for(int i = 0; i < 4;i++){
        temp[0] = multiplyElement(state[0][i], 2) ^ multiplyElement(state[1][i], 3) ^ state[2][i] ^ state[3][i];
        temp[1] = state[0][i] ^ multiplyElement(state[1][i], 2) ^ multiplyElement(state[2][i], 3) ^ state[3][i];
        temp[2] = state[0][i] ^ state[1][i] ^ multiplyElement(state[2][i], 2) ^ multiplyElement(state[3][i], 3);
        temp[3] = multiplyElement(state[0][i], 3) ^ state[1][i] ^ state[2][i] ^ multiplyElement(state[3][i], 2);
        for(int j = 0; j < 4;j++){
            state[j][i] = temp[j];
        }
    }
}

const uint8_t Rcon[10] = { 
    0x01,0x02,0x04,0x08,0x10,
    0x20,0x40,0x80,0x1B,0x36
};

vector<uint8_t> rotWord(vector<uint8_t> w){
    return {w[1], w[2], w[3], w[0]};
}

vector<uint8_t> subWord(vector<uint8_t> w){
    for(int i = 0; i < 4; i++)
        w[i] = sbox[w[i]];
    return w;
}

vector<vector<uint8_t>> keyExpansion(const vector<uint8_t>& key){
    
    vector<vector<uint8_t>> w(44, vector<uint8_t>(4));

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            w[i][j] = key[4*i + j];

    for(int i = 4; i < 44; i++){
        
        vector<uint8_t> temp = w[i-1];

        if(i % 4 == 0){
            temp = rotWord(temp);
            temp = subWord(temp);
            temp[0] ^= Rcon[i/4 - 1];
        }

        for(int j = 0; j < 4; j++)
            w[i][j] = w[i-4][j] ^ temp[j];
    }

    return w;
}

void addRoundKey(vector<vector<uint8_t>>& state, vector<vector<uint8_t>> roundKey){
    for(int i = 0; i < 4;i++){
        for(int j = 0; j < 4;j++){
            state[i][j] ^= roundKey[i][j];
        }
    }
}

vector<vector<uint8_t>> getRoundKey(const vector<vector<uint8_t>>& expandedKeys, int round) {
    vector<vector<uint8_t>> roundKey(4, vector<uint8_t>(4));
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            roundKey[row][col] = expandedKeys[round * 4 + col][row];
        }
    }
    return roundKey;
}

string AES128_Encrytpion(string pt, string key){
    if(pt.size() < 16){
        int n = 16 - pt.size();
        for(int i = pt.size(); i < 16;i++){
            pt.push_back(n);
        }
    }
    vector<uint8_t> pt_matrix(pt.begin(), pt.end());
    vector<uint8_t> key_matrix(key.begin(), key.end());

    vector<vector<uint8_t>> state(4, vector<uint8_t>(4));
    vector<vector<uint8_t>> key_state(4, vector<uint8_t>(4));
    int x = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            state[j][i] = pt[x++];
        }
    }
    x = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            key_state[j][i] = key[x++];
        }
    }

    vector<vector<uint8_t>> expandedKeys = keyExpansion(key_matrix);
    addRoundKey(state, key_state);
    for(int round = 1; round <= 9;round++){
        sbox_substitution(state);
        shift_rows(state);
        mix_columns(state);
        vector<vector<uint8_t>> roundKey(4, vector<uint8_t>(4));
        for(int c = 0; c < 4; c++) {
            for(int r = 0; r < 4; r++) {
                roundKey[r][c] = expandedKeys[round * 4 + c][r];
            }
        }
        addRoundKey(state, roundKey);
    }

    sbox_substitution(state);
    shift_rows(state);
    vector<vector<uint8_t>> finalKey(4, vector<uint8_t>(4));
    for(int c = 0; c < 4; c++) {
        for(int r = 0; r < 4; r++) {
            finalKey[r][c] = expandedKeys[40 + c][r];
        }
    }
    addRoundKey(state, finalKey);
    string s;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            s.push_back(state[j][i]);
        }
    }
    return s;
}

//DECRYPTION
void inverse_sub_bytes(vector<vector<uint8_t>>& state){
    for(int i = 0; i < 4;i++){
        for(int j = 0; j < 4;j++){
            state[i][j] = inv_sbox[state[i][j]];
        }
    }
}

void inverse_shift_rows(vector<vector<uint8_t>>& state){
    vector<vector<uint8_t>> copy = state;
    state[1][0] = copy[1][3];
    state[1][1] = copy[1][0];
    state[1][2] = copy[1][1];
    state[1][3] = copy[1][2];

    state[2][0] = copy[2][2];
    state[2][1] = copy[2][3];
    state[2][2] = copy[2][0];
    state[2][3] = copy[2][1];

    state[3][0] = copy[3][1];
    state[3][1] = copy[3][2];
    state[3][2] = copy[3][3];
    state[3][3] = copy[3][0];

}

uint8_t gf_multiplication(uint8_t a, uint8_t b){
        uint8_t p = 0;

    for (int i = 0; i < 8; i++) {
        if (b & 1)
            p ^= a;

        bool hi = a & 0x80;
        a <<= 1;

        if (hi)
            a ^= 0x1B;   

        b >>= 1;
    }

    return p;
}

void inverse_mix_columns(vector<vector<uint8_t>>& state){
    uint8_t temp[4];
    for(int i = 0; i < 4;i++){
        temp[0] = (gf_multiplication(14, state[0][i]) ^ gf_multiplication(11 ,state[1][i]) ^ gf_multiplication(13, state[2][i]) ^ gf_multiplication(9 , state[3][i]));
        temp[1] = (gf_multiplication(9, state[0][i]) ^ gf_multiplication(14, state[1][i]) ^ gf_multiplication(11, state[2][i]) ^ gf_multiplication(13, state[3][i]));
        temp[2] = (gf_multiplication(13, state[0][i]) ^ gf_multiplication(9, state[1][i]) ^ gf_multiplication(14, state[2][i]) ^ gf_multiplication(11, state[3][i]));
        temp[3] = (gf_multiplication(11, state[0][i]) ^ gf_multiplication(13, state[1][i]) ^ gf_multiplication(9, state[2][i]) ^ gf_multiplication(14, state[3][i]));  
        for(int j = 0; j < 4;j++){
            state[j][i] = temp[j];
        }
    }
}

string AES128_Decrytpion(string ct, string key){
    vector<uint8_t> key_matrix(key.begin(), key.end());
    vector<vector<uint8_t>> state(4, vector<uint8_t>(4));

    int x = 0;
    for(int i = 0; i < 4; i++){      
        for(int j = 0; j < 4; j++){  
            state[j][i] = (uint8_t)ct[x++];
        }
    }

    vector<vector<uint8_t>> expandedKeys = keyExpansion(key_matrix);
    vector<vector<uint8_t>> roundKey = getRoundKey(expandedKeys, 10);
    addRoundKey(state, roundKey);

    for(int i = 9; i >= 1; i--){
        inverse_shift_rows(state);
        inverse_sub_bytes(state);

        roundKey = getRoundKey(expandedKeys, i);
        addRoundKey(state, roundKey);

        inverse_mix_columns(state);  
    }

    inverse_shift_rows(state);
    inverse_sub_bytes(state);

    roundKey = getRoundKey(expandedKeys, 0);
    addRoundKey(state, roundKey);

    string pt = "";
    for (int i = 0; i < 4; i++) {      
        for (int j = 0; j < 4; j++) {  
            pt.push_back(state[j][i]); 
        }
    }
    return pt;
}




