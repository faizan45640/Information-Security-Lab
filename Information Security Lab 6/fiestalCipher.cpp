#include<iostream>
#include<string>
#include<ctime>
using namespace std;

string randomKey(int p) {
    string key = "";
    for(int i = 0; i < p; i++) {
        key += (rand() % 2) ? '1' : '0';
    }
    return key;
}

string exor(string a, string b) {
    string result = "";
    for(int i = 0; i < a.length(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

string stringToBinary(string text) {
    string binary = "";
    for(int i = 0; i < text.length(); i++) {
        int ascii = int(text[i]);
        string bin = "";
        for(int j = 6; j >= 0; j--) {
            bin += ((ascii >> j) & 1) ? '1' : '0';
        }
        binary += bin;
    }
    return binary;
}

string binaryToString(string binaryText) {
    string result = "";
    for(int i = 0; i < binaryText.length(); i += 7) {
        string byte = binaryText.substr(i, 7);
        int val = 0;
        for(char bit : byte) {
            val = val * 2 + (bit - '0');
        }
        result += char(val);
    }
    return result;
}


string fiestelEncrypt(string L, string R, string K) {
    string f = exor(R, K);
    string newR = exor(L, f);
    return R + newR;  
}


string fiestelDecrypt(string L, string R, string K) {
    string f = exor(L, K);
    string newL = exor(R, f);
    return newL + L; 
}

int main() {
    srand(time(0));
    string plainText;
    cout << "Enter Plaintext: ";
    getline(cin, plainText);

   
    string binaryText = stringToBinary(plainText);
    cout << "Binary Plaintext: " << binaryText << endl;

   
    if(binaryText.length() % 2 != 0) {
        binaryText += "0";  // Pad at end instead of beginning
    }

   
    int n = binaryText.length() / 2;
    string L = binaryText.substr(0, n);
    string R = binaryText.substr(n);
    string key1 = randomKey(n);
    string key2 = randomKey(n);

   
    cout << "\nEncryption Process:" << endl;
    string encrypted;
    
    encrypted = fiestelEncrypt(L, R, key1);
    L = encrypted.substr(0, n);
    R = encrypted.substr(n);
    
    encrypted = fiestelEncrypt(L, R, key2);

    string cipherText = encrypted;
    cout << "Cipher Text (binary): " << cipherText << endl;
    cout << "Cipher Text: " << binaryToString(cipherText) << endl;

    
    cout << "\nDecryption Process:" << endl;
    string Ld = cipherText.substr(0, n);
    string Rd = cipherText.substr(n);
    string decrypted;
    
    
    decrypted = fiestelDecrypt(Ld, Rd, key2);
    Ld = decrypted.substr(0, n);
    Rd = decrypted.substr(n);
    
    decrypted = fiestelDecrypt(Ld, Rd, key1);

    cout << "Decrypted Binary: " << decrypted << endl;
    cout << "Decrypted Text: " << binaryToString(decrypted) << endl;

    return 0;
}