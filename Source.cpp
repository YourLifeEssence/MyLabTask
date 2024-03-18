#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Encoder {
private:
    vector<unsigned char> key;

    // RC4 Algorithm functions
    void RC4(vector<unsigned char>& S) {
        int j = 0;
        for (int i = 0; i < 256; ++i) {
            j = (j + S[i] + key[i % key.size()]) % 256;
            swap(S[i], S[j]);
        }
    }

    unsigned char PRGA(vector<unsigned char>& S, int& i, int& j) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        int t = (S[i] + S[j]) % 256;
        return S[t];
    }

public:
    Encoder(const unsigned char* keyData, int keySize) : key(keyData, keyData + keySize) {}

    Encoder(const Encoder& other) : key(other.key) {}

    ~Encoder() {}

    void encode(const char* inputFile, const char* outputFile, bool encrypt) {
        ifstream input(inputFile, ios::binary);
        ofstream output(outputFile, ios::binary);

        if (!input || !output) {
            cout << "Error: Cannot open file\n";
            return;
        }

        // Initialize S vector for RC4 Algorithm
        std::vector<unsigned char> S(256);
        for (int i = 0; i < 256; ++i) {
            S[i] = i;
        }
        RC4(S);

        int i = 0, j = 0;
        unsigned char t;

        // Process each byte of the input file
        char ch;
        while (input.get(ch)) {
            t = PRGA(S, i, j);
            if (encrypt) {
                output.put(ch ^ t); // Encrypt
            }
            else {
                output.put(ch ^ t); // Decrypt
            }
        }
    }

    // Mutator for key
    void setKey(const unsigned char* keyData, int keySize) {
        key.assign(keyData, keyData + keySize);
    }
};

int main() {
    const char* inputFile = "input.txt";
    const char* encryptedFile = "encrypted.txt";
    const char* decryptedFile = "decrypted.txt";

    const unsigned char key[] = { 's', 'e', 'c', 'r', 'e', 't' };
    int keySize = sizeof(key) / sizeof(key[0]);

    Encoder encoder(key, keySize);

    // Encrypt the input file
    encoder.encode(inputFile, encryptedFile, true);

    // Decrypt the encrypted file
    encoder.encode(encryptedFile, decryptedFile, false);

    return 0;
}
