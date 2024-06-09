#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Declare class Mahasiswa
class Mahasiswa {
public:
	struct Data {
		long long int NRP;
		string nama;
		int tugas[3];
		};

	void write(Data mhs) {
		ofstream file("data_mahasiswa.txt", ios::app);
		if (!file.is_open()) {
			cout << "File tidak dapat diakses" << endl;
			}
		else {
			file << mhs.NRP << " " << mhs.nama << " ";
			for (int i = 0; i < 3; i++) {
				file << mhs.tugas[i] << " ";
				}
			file << endl;
			file.close();
			cout << "Data berhasil dimasukkan!" << endl;
			}
		}
	};

int main() {
	cout << "init";
	return 0;
	}
