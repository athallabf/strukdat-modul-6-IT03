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
};

int main() {
  cout << "init";
  return 0;
  }
