#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Encoder {
private:
	vector<unsigned char> key;
	int size;
	unsigned char const *var;

	void KSA() {
		vector<unsigned char> S(256);
		for (int i = 0; i < 256; ++i) {
			S[i] = i;
		}

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
	Encoder(const unsigned char* b, int size) {
		var = b;
		this->size = size;
	}

	Encoder(const Encoder &Meow) {
		cout << "\n�������� ����������� �����������!\n";
		size = Meow.size;
		var = Meow.var;
	}

	~Encoder() {
		cout << "\n�������� ����������\n";
	}

	//���� ������
	static void Encode(const char* inputFile, const char* outputFile, bool encrypt) {
		ifstream input(inputFile, ios::binary);
		ofstream output(outputFile, ios::binary);

		if (!input || !output) {
			cout << "������: �� ������� ������� ����\n";
			return;
		}

		vector<unsigned char> data(istreambuf_iterator<char>(input), {});

		vector<unsigned char> S(256);
		int i = 0, j = 0;
		for (int k = 0; k < 256; ++k) {
			S[k] = k;
		}
		for (int k = 0; k < key.size(); ++k) {
			j = (j + S[k] + key[k]) % 256;
			swap(S[k], S[j]);
		}

		for (int k = 0; k < data.size(); ++k) {
			unsigned char t = PRGA(S, i, j);
			if (encrypt) {
				// ����������
				data[k] ^= t;
			}
			else {
				// ������������
				data[k] ^= t;
			}
		}

		copy(data.begin(), data.end(), ostreambuf_iterator<char>(output));
	}

	//�������
	void ChangeKey(const vector<unsigned char>& newKey) {
		key = newKey;
	}
};

int main(){
	setlocale(LC_ALL, "ru");

	vector<unsigned char> key = { 'k', 'e', 'y' }; // ������ �����

	//Encoder ae(reinterpret_cast<unsigned const char *>("Pizza\0"), 6); //����� �������������� ���� �� ��������� ����������� ���� � �����, ���� ����, �� ��� ��������� �������
	//Encoder mimya(ae);

	Encoder encoder(nullptr, 0); // �������� ���������� ������

	encoder.ChangeKey(key); // ��������� �����

	encoder.Encode("input.txt", "encrypted.txt", true); // ����������
	// ���
	encoder.Encode("encrypted.txt", "decrypted.txt", false); // ������������

	return 0;
}


