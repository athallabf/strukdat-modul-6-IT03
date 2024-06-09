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

		// UPDATE
    void update(long long NRP, int newTugas[]) {
        ifstream file("data_mahasiswa.txt");
        ofstream file_t("datatemp.txt");

        Data temp;
        bool found = false;

        while (file >> temp.NRP) {
            file >> ws;
            getline(file, temp.nama, ' ');
            for (int i = 0; i < 3; i++) {
                file >> temp.tugas[i];
                }
            if (temp.NRP == NRP) {
                for (int i = 0; i < 3; i++) {
                    temp.tugas[i] = newTugas[i];
                    }
                found = true;
                }
            file_t << temp.NRP << " " << temp.nama << " ";
            for (int i = 0; i < 3; i++) {
                file_t << temp.tugas[i] << " ";
                }
            file_t << endl;
            }

        if (!found) {
            cerr << "Data dari NRP: " << NRP << " tidak ditemukan!" << endl;
            }

        file.close();
        file_t.close();

        remove("data_mahasiswa.txt");
        rename("datatemp.txt", "data_mahasiswa.txt");
        }
	};
	

int main() {
	cout << "init";
	return 0;
	}
