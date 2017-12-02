#ifndef _COL_H
#define _COL_H

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "str.h"

using namespace boost;

class Column{
public:
	unsigned nsize;
	string path;
	virtual void set(string) = 0;
	virtual string get(unsigned) = 0;
	virtual void update(unsigned, string) = 0;
	virtual unsigned size() = 0;
	virtual bool opr(string,string,char) = 0;
	virtual void random(unsigned) = 0;
	string get_path(){	return this->path;	}
	virtual vector<unsigned> scan(string, vector<bool> &, char) = 0;
	virtual vector<pair<int,int>> scan_index(string, vector<bool> &, char) = 0;
	virtual ~Column(){	};
};

class Intege: public Column{
public:
	Intege(string _path, unsigned _size){	this->path = _path;	this->nsize = _size;	}

	vector<unsigned> scan(string a, vector<bool> &v, char op){
		ifstream file(this->path, ios::binary | ios::app);
		int b;
		vector<unsigned> np;
		file.seekg(0, ios::beg);
		for(unsigned i=0; i<this->nsize; i++){
			file.read((char*)(&b),sizeof(int));
			if(v[i] and this->opr(to_string(b),a,op))	np.push_back(i);
		}
		file.close();
		return np;
	}

	vector<pair<int,int>> scan_index(string a, vector<bool> &v, char op){
		ifstream file(this->path, ios::binary | ios::app);
		int b;
		vector<pair<int,int>> np;
		file.seekg(0, ios::beg);
		for(unsigned i=0; i<this->nsize; i++){
			file.read((char*)(&b),sizeof(int));
			if(v[i] and this->opr(to_string(b),a,op))	np.push_back(pair<int,int>(b,i));
		}
		file.close();
		return np;
	}

	void set(string q){
		int a = stoi(q);
		ofstream file(this->path, ios::in | ios::binary);
		file.seekp(0, ios::end);
		file.write((char*)&a,sizeof(int));
		this->nsize++;
		file.close();
	}
	string get(unsigned i){
		ifstream file(this->path, ios::binary | ios::app);
		int a;
		file.seekg(sizeof(int)*i, ios::beg);
		file.read((char*)(&a),sizeof(int));
		file.close();
		return to_string(a);
	}
	void update(unsigned i, string q){
		int a = stoi(q);
		ofstream file(this->path, ios::in | ios::binary);
		file.seekp(sizeof(int)*i, ios::beg);
		file.write((char*)&a,sizeof(int));
		file.close();
	}
	unsigned size(){	return this->nsize;	}
	bool opr(string a, string b, char op){
		switch(op){
			case '=':
				return a==b;
				break;
			case '<':
				return stoi(a)<stoi(b);
				break;
			case '>':
				return stoi(a)>stoi(b);
				break;
		}
	}
	void random(unsigned n){
		int t = this->nsize;
		this->nsize += n;
		ofstream file(this->path, ios::in | ios::binary);
		file.seekp(0, ios::end);
		for(unsigned i=0; i<n; i++){
			int a = t+i+1;
			file.write((char*)&a,sizeof(int));
		}
		file.close();
	}
	~Intege(){	};
};



class Double: public Column{
public:
	Double(string _path, unsigned _size){	this->path = _path;	this->nsize = _size;	}

	vector<unsigned> scan(string a, vector<bool> &v, char op){
		ifstream file(this->path, ios::binary | ios::app);
		double b;
		vector<unsigned> np;
		file.seekg(0, ios::beg);
		for(unsigned i=0; i<this->nsize; i++){
			file.read((char*)(&b),sizeof(double));
			if(v[i] and this->opr(to_string(b),a,op))	np.push_back(i);
		}
		file.close();
		return np;
	}

	vector<pair<int,int>> scan_index(string a, vector<bool> &v, char op){
		vector<pair<int,int>> np;
		return np;
	}

	void set(string q){
		double a = stod(q);
		ofstream file(this->path, ios::in | ios::binary);
		file.seekp(0, ios::end);
		file.write((char*)&a,sizeof(double));
		file.close();
		this->nsize++;
	}
	string get(unsigned i){	
		ifstream file(this->path, ios::binary | ios::app);
		double a;
		file.seekg(sizeof(double)*i, ios::beg);
		file.read((char*)(&a),sizeof(double));
		file.close();
		return to_string(a);
	}
	void update(unsigned i, string q){
		double a = stod(q);
		ofstream file(this->path, ios::in | ios::binary);
		file.seekp(sizeof(double)*i, ios::beg);
		file.write((char*)&a,sizeof(double));
		file.close();
	}
	unsigned size(){	return this->nsize;	}
	bool opr(string a, string b, char op){
		switch(op){
			case '=':
				return a==b;
				break;
			case '<':
				return stod(a)<stod(b);
				break;
			case '>':
				return stod(a)>stod(b);
				break;
		}
	}

	void random(unsigned n){
		this->nsize += n;
		ofstream file(this->path, ios::in | ios::binary);
		file.seekp(0, ios::end);
		for(unsigned i=0; i<n; i++){
			double a = double_random(0,n*10);
			file.write((char*)&a,sizeof(double));
		}
		file.close();
	}
	~Double(){	};
};

class Boolea: public Column{
public:
	Boolea(string _path, unsigned _size){	this->path = _path;	this->nsize = _size;	}

	vector<unsigned> scan(string a, vector<bool> &v, char op){
		ifstream file(this->path, ios::binary | ios::app);
		int b, at = stoi(a)+48;
		string bt;
		vector<unsigned> np;
		file.seekg(0, ios::beg);
		for(unsigned i=0; i<this->nsize; i++){
			file.read((char*)(&b),sizeof(char));
			bt = ""+b;
			if(v[i] and this->opr(bt,a,op))	np.push_back(i);
		}
		file.close();
		return np;
	}

	vector<pair<int,int>> scan_index(string a, vector<bool> &v, char op){
		vector<pair<int,int>> np;
		return np;
	}

	void set(string q){
		int a = stoi(q)+48;
		ofstream file(this->path, ios::in | ios::binary);
		file.seekp(0, ios::end);
		file.write((char*)&a,sizeof(char));
		file.close();
		this->nsize++;
	}
	string get(unsigned i){	
		ifstream file(this->path, ios::binary | ios::app);
		char a;
		file.seekg(sizeof(char)*i, ios::beg);
		file.read((char*)(&a),sizeof(char));
		file.close();
		return to_string(a-'0');
	}
	void update(unsigned i, string q){
		int a = stoi(q)+48;
		ofstream file(this->path, ios::in | ios::binary);
		file.seekp(sizeof(char)*i, ios::beg);
		file.write((char*)&a,sizeof(char));
		file.close();
	}
	unsigned size(){	return this->nsize;	}
	bool opr(string a, string b, char op){	return a==b;	}
	void random(unsigned n){
		this->nsize += n;
		ofstream file(this->path, ios::in | ios::binary);
		file.seekp(0, ios::end);
		for(unsigned i=0; i<n; i++){
			int a = 48+rand()%2;
			file.write((char*)&a,sizeof(char));
		}
		file.close();
	}
	~Boolea(){	};
};

/*class String: public Column{
private:
	vector<string> v;
public:
	String(string _path, unsigned _size){	this->path = _path;	}
	void set(string q){	this->v.push_back(q);	}
	string get(unsigned i){	return this->v[i];	}
	void update(unsigned i, string q){	this->v[i] = q;	}
	unsigned size(){	return this->v.size();	}
	void resize(unsigned i){	this->v.resize(i);	}
	void save(){
		path[path.size()-3] = 'o';	path[path.size()-2] = 'u';	path[path.size()-1] = 't';		
	    ofstream file(path);
	    for (const auto &e : this->v) file << e << "|";
	}
	void load(){
		if(this->v.size()==0)	return;
		path[path.size()-3] = 'o';	path[path.size()-2] = 'u';	path[path.size()-1] = 't';		
		string cd;

		ifstream file(path);
		getline(file, cd);	cd.resize(cd.size()-1);
		split(this->v,cd,is_any_of("|"));
	}
	bool opr(string a, string b, char op){
		char ca[a.length()], cb[b.length()];
		strcpy(ca, a.c_str());	strcpy(cb, b.c_str());
		switch(op){
			case '=':
				return a==b;
				break;
			case '<':
				return (strcmp(ca,cb)<=0)? true: false;
				break;
			case '>':
				return (strcmp(ca,cb)>0)? true: false;
				break;
		}
	}
	void clear(){	this->v.clear();	}
	void erase(unsigned i){	this->v.erase(this->v.begin()+i);	}
	void random(unsigned n){
		for(unsigned i=0; i<n; i++)
			this->v.push_back(string_random());
	}
	void refresh(vector<bool> &a){
		vector<string> tm = this->v;
		this->v.clear();
		for(unsigned i=0; i<a.size(); i++)
			if(a[i])	this->v.push_back(tm[i]);
		tm.clear();
	}
	~String(){	};
};*/



class Date: public Column{
public:
	Date(string _path, unsigned _size){	this->path = _path;	this->nsize = _size;	}

	vector<unsigned> scan(string a, vector<bool> &v, char op){
		ifstream file(this->path, ios::binary | ios::app);
		time_t b;
		vector<unsigned> np;
		file.seekg(0, ios::beg);
		for(unsigned i=0; i<this->nsize; i++){
			file.read((char*)(&b),sizeof(time_t));
			if(v[i] and this->opr(time_string(b),a,op))	np.push_back(i);
		}
		file.close();
		return np;
	}

	vector<pair<int,int>> scan_index(string a, vector<bool> &v, char op){
		vector<pair<int,int>> np;
		return np;
	}

	void set(string q){
		time_t a;
		(q == "0")? a = 0: a = to_time(q);
		ofstream file(this->path, ios::in | ios::binary);
		file.seekp(0, ios::end);
		file.write((char*)&a,sizeof(time_t));
		file.close();
		this->nsize++;
	}
	string get(unsigned i){	
		ifstream file(this->path, ios::binary | ios::app);
		time_t a;
		file.seekg(sizeof(time_t)*i, ios::beg);
		file.read((char*)(&a),sizeof(time_t));
		file.close();
		return time_string(a);
	}
	void update(unsigned i, string q){
		time_t a = to_time(q);
		ofstream file(this->path, ios::in | ios::binary);
		file.seekp(sizeof(time_t)*i, ios::beg);
		file.write((char*)&a,sizeof(time_t));
		file.close();
	}
	unsigned size(){	return this->nsize;	}
	bool opr(string a, string b, char op){
		switch(op){
			case '=':
				return a==b;
				break;
			case '<':
				return to_time(a)<to_time(b);
				break;
			case '>':
				return to_time(a)>to_time(b); 
				break;
		}
	}
	void random(unsigned n){
		this->nsize += n;
		ofstream file(this->path, ios::in | ios::binary);
		file.seekp(0, ios::end);
		for(unsigned i=0; i<n; i++){			
			time_t a = 106213762+(rand()%(1506603798-106213762));
			file.write((char*)&a,sizeof(time_t));
		}
		file.close();
	}
	~Date(){	};
};

class Age: public Column{
public:
	Age(string _path, unsigned _size){	this->path = _path;	this->nsize = _size;	}

	vector<unsigned> scan(string a, vector<bool> &v, char op){
		ifstream file(this->path, ios::binary | ios::app);
		int8_t b;
		vector<unsigned> np;
		file.seekg(0, ios::beg);
		for(unsigned i=0; i<this->nsize; i++){
			file.read((char*)(&b),sizeof(int8_t));
			if(v[i] and this->opr(to_string(b),a,op))	np.push_back(i);
		}
		file.close();
		return np;
	}

	vector<pair<int,int>> scan_index(string a, vector<bool> &v, char op){
		vector<pair<int,int>> np;
		return np;
	}
	
	void set(string q){
		int8_t a = stoi(q);
		ofstream file(this->path, ios::in | ios::binary);
		file.seekp(0, ios::end);
		file.write((char*)&a,sizeof(int8_t));
		file.close();
		this->nsize++;
	}
	string get(unsigned i){	
		ifstream file(this->path, ios::binary | ios::app);
		int8_t a;
		file.seekg(sizeof(int8_t)*i, ios::beg);
		file.read((char*)(&a),sizeof(int8_t));
		file.close();
		return to_string(a);
	}
	void update(unsigned i, string q){
		int8_t a = stoi(q);
		ofstream file(this->path, ios::in | ios::binary);
		file.seekp(sizeof(int8_t)*i, ios::beg);
		file.write((char*)&a,sizeof(int8_t));
		file.close();
	}
	unsigned size(){	return this->nsize;	}
	bool opr(string a, string b, char op){
		switch(op){
			case '=':
				return a==b;
				break;
			case '<':
				return stoi(a)<stoi(b);
				break;
			case '>':
				return stoi(a)>stoi(b);
				break;
		}
	}

	void random(unsigned n){
		this->nsize += n;
		ofstream file(this->path, ios::in | ios::binary);
		file.seekp(0, ios::end);
		for(unsigned i=0; i<n; i++){
			int8_t a = rand()%100;
			file.write((char*)&a,sizeof(int8_t));
		}
		file.close();
	}
	~Age(){	};
};

#endif