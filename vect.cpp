#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <sys/time.h>
#include "src/str.h"

using namespace std;

template<class T>
void print(vector<T> &v){
	for(unsigned i=0; i<v.size(); i++)
		cout << v[i] << " ";
	cout << endl << endl;
}

template<class T>
class sws{
public:
	unsigned s;
	ifstream gfile;
	ofstream sfile;
	sws(){}
	sws(int _s){
		this->s = _s;
	}

	void gopen(){
		this->gfile = ifstream("v.bin", ios::binary | ios::app);
	}

	void gclose(){
		this->gfile.close();
	}

	void sopen(){
		this->sfile = ofstream("v.bin", ios::in | ios::binary);
	}

	void sclose(){
		this->sfile.close();
	}

	T get(unsigned f){
		gopen();
		T a;
		gfile.seekg(sizeof(T)*f, ios::beg);
		gfile.read((char*)(&a),sizeof(T));
		gclose();
		return a;
	}

	void set(T a){
		sopen();
		sfile.seekp(0, ios::end);
		sfile.write((char*)&a,sizeof(T));
		sclose();
	}

	void update(unsigned i, T a){
		sopen();
		sfile.seekp(sizeof(T)*i, ios::beg);
		sfile.write((char*)&a,sizeof(T));
		sclose();
	}

	unsigned size(){
		ifstream file("v.bin", ios::binary | ios::app);
		file.seekg(0, ios::end);
		file.close();
		return file.tellg();
	}

	void print(){
		unsigned t = size()/sizeof(T);
		for(unsigned i=0; i<t; i++)
			cout << get(i) << " ";
		cout << endl;
	}
};


typedef sws<int> sw;
int main(int argc, char const *argv[]){
	int t = 10;
	sw a(t);
	a.print();

	a.set(0);
	a.print();
	
	a.update(0,9);
	a.print();
	return 0;
}

//du -h v.bin
//sudo dpkg -i fpc_3.0.2-170225_amd64.deb