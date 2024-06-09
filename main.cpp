#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Declare class Mahasiswa
class Mahasiswa {
public:
	struct Data {
		long long int NRP;
		string nama;
		int tugas[3];
		};

	// Operasi CRUD dari class Mahasiswa
	// CREATE / Write
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

	// READ
	void read() {
		cout << "Berikut adalah data peserta kelas:" << endl;
		cout << "No.\tNRP\t\tNama\tTugas1\tTugas2\tTugas3" << endl;
		system("cat -n data_mahasiswa.txt | awk '{print $1 \"\\t\" $2 \"\\t\" $3  \"\\t\" $4 \"\\t\" $5 \"\\t\" $6 \"\\t\" $7}'");
		}

	// UPDATE
	void update(long long int NRP, int newTugas[]) {
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


	// DELETE
	void del(long long int NRP) {
		ifstream file("data_mahasiswa.txt");
		ofstream file_t("datatemp.txt");

		Data temp;
		bool found = false;

		while (file >> temp.NRP >> temp.nama >> temp.tugas[0] >> temp.tugas[1] >> temp.tugas[2]) {
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
	// Declare penggunaan class dan lainnya
	Mahasiswa mahasiswa;
	int jmlhMahasiswa, pilihan;
	long long int NRPterpilih;
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
					mahasiswa.read();
					system("read -n 1 -s -p 'Tekan Key Bebas untuk melanjutkan...'; echo");
					break;
				case 2: // menambah data mahasiswa
					cout << "Masukkan jumlah mahasiswa:";
					cin >> jmlhMahasiswa;
					for (int i = 0; i < jmlhMahasiswa; i++) {
						Mahasiswa::Data mhs;
						cout << "Data Mahasiswa ke-" << i + 1 << ": " << endl;
						cout << "NRP: ";
						cin >> mhs.NRP;
						cout << "Nama: ";
						cin.ignore();
						getline(cin, mhs.nama);
						cout << "Tugas 1: ";
						cin >> mhs.tugas[0];
						cout << "Tugas 2: ";
						cin >> mhs.tugas[1];
						cout << "Tugas 3: ";
						cin >> mhs.tugas[2];
						mahasiswa.write(mhs);
						}
					break;
				case 3: // update data mahasiswa
					cout << "==========================================" << endl;
					mahasiswa.read();
					cout << "==========================================" << endl;
					cout << "Masukkan NRP dari mahasiswa yang dipilih:";
					cin >> NRPterpilih;
					int newTugas[3];
					for (int i = 0; i < 3; i++) {
						cout << "Masukkan Update Nilai Tugas-" << i + 1 << ":";
						cin >> newTugas[i];
						}
					mahasiswa.update(NRPterpilih, newTugas);
					cout << "Data berhasil diupdate!" << endl;
					cout << "Tekan Enter untuk melanjutkan...";
					cin.ignore();
					cin.get();
					break;
				case 4: // hapus data mahasiswa terpilih
					cout << "==========================================" << endl;
					mahasiswa.read();
					cout << "==========================================" << endl;
					cout << "Masukkan NRP dari mahasiswa yang dipilih:";
					cin >> NRPterpilih;
					mahasiswa.del(NRPterpilih);
					cout << "Data berhasil dihapus!" << endl;
					cout << "Tekan Enter untuk melanjutkan...";
					cin.ignore();
					cin.get();
					break;
				default:
					cout << "Pilihan tidak tersedia!" << endl;
					cout << "Tekan Enter untuk melanjutkan...";
					cin.ignore();
					cin.get();
					break;
			}
		} while (keluar == 1);

	return 0;
	}

