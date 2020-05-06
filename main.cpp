#include <iostream>
#include <fstream>

using namespace std;

class film {	
	string tytul;
	string rezyser;
	string rok;
	
	public:
		ifstream plik1;
		ofstream plik2;	
		
		film();
		~film();
		void wczytaj();
		void zapisJson();
};

film::film() {
	plik1.open("we.txt");
	plik2.open("wy.txt");
}

void film::wczytaj() {
	getline(plik1, tytul);
	getline(plik1, rezyser);
	getline(plik1, rok);
}

void film::zapisJson() {
	cout<<"{\"tytul\":"+tytul+",\"rezyser\":"+rezyser+",\"rok\":"+rok+",";
	plik2<<"{\"tytul\":"+tytul+",\"rezyser\":"+rezyser+",\"rok\":"+rok+",";
}

film::~film() {	
	plik1.clear();
	plik2.close();
}

class filmDok:public film {
	string opis;
	
	public:
		void wczytaj();	
		void zapisJson();	
};

void filmDok::wczytaj() {
	cout<<"[\n";
	plik2<<"[\n";
	if(plik1.good()) {
		while(!plik1.eof()) {
			film::wczytaj();
			getline(plik1, opis);
			this->zapisJson();
		}
	}
	cout<<"]";
	plik2<<"]";
}

void filmDok::zapisJson() {
	film::zapisJson();
	cout<<"\"opis\":"+opis+"},\n";
	plik2<<"\"opis\":"+opis+"},\n";
}

int main(int argc, char** argv) {
	film f1;
	filmDok fd1;
	
	fd1.wczytaj();	
	return 0;
}
