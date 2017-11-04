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
	vector<T> v;
	sws(){}
	sws(int _s){
		this->s = _s;
	}

	void info(){
		cout << "s: " << this->s << endl;
		print(this->v);
	}

	void save(){
		string path = "v.bin";
		ofstream file(path, ios::binary);
		if(!file.is_open())	cout << "error" << endl;
		else	file.write((char *)&this->v[0],v.size()*sizeof(T));

		this->s = this->v.size();
		this->v.clear();
	}

	void load(){
		string path = "v.bin";
		this->v = vector<T>(this->s);
		ifstream file(path, ios::binary | ios::app);
		if(!file.is_open())	cout << "error" << endl;
		else	file.read((char*)&this->v[0],v.size()*sizeof(T));
	}

	T get(unsigned f){
		string path = "v.bin";
		ifstream file(path, ios::binary | ios::app);
		T a;

		if(!file.is_open())	cout << "error" << endl;
		else{
			file.seekg(sizeof(T)*f, ios::beg);
			file.read((char*)(&a),sizeof(T));
		}
		file.close();
		return a;
	}

	void set(T a, unsigned et){
		string path = "v.bin";
		ofstream file(path, ios::binary);
		if(!file.is_open())	cout << "error" << endl;
		else{
			file.seekp(40, ios::beg);
			file.write((char *)&a,sizeof(T));
		}
	}

	unsigned size(){
		string path = "v.bin";
		ifstream file(path, ios::binary | ios::app);
		file.seekg(0, ios::end);
		return file.tellg();
	}

	void print(){
		set(1,size());
		set(2,size());
		set(3,size());
		unsigned t = size()/sizeof(T);
		for(unsigned i=0; i<t; i++)
			cout << get(i) << " ";
		cout << endl;
	}
};


template<class T>
void change(sws<T> &a, unsigned t){
	srand(time(NULL));
	a.v.clear();
	for(unsigned i=0; i<t; i++)
		a.v.push_back(i);	
}

template<class T>
void pull(vector<T> &v, unsigned t){
	for(unsigned i=0; i<t; i++)
		v.push_back(i);
}


typedef sws<int> sw;
int main(int argc, char const *argv[]){
	int t = 10;
	sw a(t);	sw b(t);
	change(a,t);
	a.save();
	//print(a.v);
	a.print();
	/*unsigned r,i;

	struct timeval ti, tf;
    double tiempo;
    for(i=1; i<7; i++){
    	change(a,t);
		a.save();
		pull(tm,t);
		r = t-1;

	    gettimeofday(&ti, NULL);
		cout << a.get(r) << " |";
		gettimeofday(&tf, NULL);
	    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
	    printf("[binary]: %.8lf\t",tiempo/1000);

	    gettimeofday(&ti, NULL);
		cout << tm[r] << " |";
		gettimeofday(&tf, NULL);
	    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
	    printf("[vector]: %.8lf\n",tiempo/1000);
	    tm.clear();
	}*/

	return 0;
}

//du -h v.bin
//sudo dpkg -i fpc_3.0.2-170225_amd64.deb
//sudo ln -s /opt/sts-bundle/sts-3.9.0.RELEASE/STS /usr/local/bin/sts
//sudo gedit /usr/share/applications/stslauncher.desktop
//0.4*exp(-power(x,2)/2)
//Wed Sep 27 23:34:55 2017 