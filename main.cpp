#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

//Declare class Mahasiswa
class Mahasiswa {
public:
	struct Data {
		long long int NRP;
		string nama;
		int tugas[3];
		};

	// WRITE
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

	// READ
	void read() {
		ifstream file("data_mahasiswa.txt");
		if (file.is_open()) {
			string line;
			int i = 1;
			while (getline(file, line)) {
				istringstream iss(line);
				Data mhs;
				if (!(iss >> mhs.NRP)) {
					cerr << "Kesalahan parsing NRP untuk mahasiswa nomor " << i << endl;
					continue;
					}
				iss >> ws;
				getline(iss, mhs.nama, ' ');
				for (int j = 0; j < 3; j++) {
					if (!(iss >> mhs.tugas[j])) {
						cerr << "Kesalahan parsing tugas " << j + 1 << " untuk mahasiswa nomor " << i << endl;
						continue;
						}
					}
				cout << i << "\t" << mhs.NRP << "\t" << mhs.nama << "\t\t" << mhs.tugas[0] << "\t" << mhs.tugas[1] << "\t" << mhs.tugas[2] << endl;
				i++;
				}
			if (i == 1) {
				cout << "Data masih kosong!" << endl;
				}
			file.close();
			}
		else {
			cerr << "File tidak dapat diakses!" << endl;
			}
		}

	// DELETE
	void del(long long NRP) {
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
				found = true;
				}
			else {
				file_t << temp.NRP << " " << temp.nama << " ";
				for (int i = 0; i < 3; i++) {
					file_t << temp.tugas[i] << " ";
					}
				file_t << endl;
				}
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
	Mahasiswa mahasiswa;
	int jmlhMahasiswa, pilihan;
	long long NRPterpilih;
	int keluar = 1;

	// Tampilan menu
	do {
#ifdef _WIN32
		system("cls");
#else
		system("clear");
#endif
		cout << "===============================" << endl;
		cout << "Aplikasi Administrasi Kelas" << endl;
		cout << "===============================" << endl;
		cout << "1. Lihat Peserta Kelas" << endl;
		cout << "2. Tambah Mahasiswa" << endl;
		cout << "3. Update Mahasiswa" << endl;
		cout << "4. Hapus Mahasiswa" << endl;
		cout << "0. Keluar dari Aplikasi" << endl;
		cout << "===============================" << endl;
		cout << "Masukkan pilihan aplikasi:";
		cin >> pilihan;
		switch (pilihan) {
                case 0: // keluar dari aplikasi
                    keluar = 0;
                    break;
                case 1: // membaca data mahasiswa
                    cout << "Berikut adalah data peserta kelas:" << endl;
                    cout << "No.\tNRP\tNama\tTugas1\tTugas2\tTugas3" << endl;
                    mahasiswa.read();
                    cout << "Tekan Enter untuk melanjutkan...";
                    cin.ignore();
                    cin.get();
                    break;
		return 0;

		} while (keluar == 1);
	}
