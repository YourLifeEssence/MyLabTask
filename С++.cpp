#include <iostream>

using namespace std;

class Encoder {
private:
	int key;
	int size;
	unsigned char const *var;

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
	/*void Encode(char const* iFile, char const* oFile, bool TF) {

	}*/

	//�������
	void ChangeKey(int newkey) {
		key = newkey;
	}
};

void main(){
	setlocale(LC_ALL, "ru");
	unsigned char const b[6] = { 'P', 'i', 'z', 'z', 'a', '\0' };
	Encoder ae(b, 5);
	Encoder mimya(ae);
}