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
	string path;
	virtual void set(string) = 0;
	virtual string get(unsigned) = 0;
	virtual void update(unsigned, string) = 0;
	virtual void resize(unsigned) = 0;
	virtual unsigned size() = 0;
	virtual void save() = 0;
	virtual void load() = 0;
	virtual bool opr(string,string,char) = 0;
	virtual void clear() = 0;
	virtual void erase(unsigned) = 0;
	virtual void random(unsigned) = 0;
	virtual void refresh(vector<bool> &) = 0;
	virtual ~Column(){	};
};

class Intege: public Column{
private:
	vector<int> v;
public:
	Intege(string _path){	this->path = _path;	}
	void set(string q){	this->v.push_back(stoi(q));	}
	string get(unsigned i){
		/*ifstream file(this->path, ios::binary | ios::app);
		int a;
		file.seekg(sizeof(int)*i, ios::beg);
		file.read((char*)(&a),sizeof(int));
		return to_string(a);*/
		return to_string(this->v[i]);
	}
	void update(unsigned i, string q){	this->v[i] = stoi(q);	}
	unsigned size(){	return this->v.size();	}
	void resize(unsigned i){	this->v.resize(i);	}
	void save(){
		ofstream file(path, ios::binary);
		if(!file.is_open())	cout << "error" << endl;
		else	file.write((char *)&this->v[0],this->v.size()*sizeof(int));
	}
	void load(){
		ifstream file(path, ios::binary | ios::app);
		if(!file.is_open())	cout << "error" << endl;
		else	file.read((char*)&this->v[0],this->v.size()*sizeof(int));
	}
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
	void clear(){	this->v.clear();	}
	void erase(unsigned i){	this->v.erase(this->v.begin()+i);	}
	void random(unsigned n){
		int t = v.size();
		for(unsigned i=0; i<n; i++)
			this->v.push_back(t+i+1);
	}
	void refresh(vector<bool> &a){
		vector<int> tm = this->v;
		this->v.clear();
		for(unsigned i=0; i<a.size(); i++)
			if(a[i])	this->v.push_back(tm[i]);
		tm.clear();
	}
	~Intege(){	};
};



class Double: public Column{
private:
	vector<double> v;
public:
	Double(string _path){	this->path = _path;	}
	void set(string q){	this->v.push_back(stod(q));	}
	string get(unsigned i){	
		/*ifstream file(this->path, ios::binary | ios::app);
		double a;
		file.seekg(sizeof(double)*i, ios::beg);
		file.read((char*)(&a),sizeof(double));
		return to_string(a);*/
		return to_string(this->v[i]);
	}
	void update(unsigned i, string q){	this->v[i] = stod(q);	}
	unsigned size(){	return this->v.size();	}
	void resize(unsigned i){	this->v.resize(i);	}
	void save(){
		ofstream file(path, ios::binary);
		if(!file.is_open())	cout << "error" << endl;
		else	file.write((char *)&this->v[0],this->v.size()*sizeof(double));
	}
	void load(){
		ifstream file(path, ios::binary | ios::app);
		if(!file.is_open())	cout << "error" << endl;
		else	file.read((char*)&this->v[0],this->v.size()*sizeof(double));
	}
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
	void clear(){	this->v.clear();	}
	void erase(unsigned i){	this->v.erase(this->v.begin()+i);	}
	void random(unsigned n){
		for(unsigned i=0; i<n; i++)
			this->v.push_back(double_random(0,n*10));
	}
	void refresh(vector<bool> &a){
		vector<double> tm = this->v;
		this->v.clear();
		for(unsigned i=0; i<a.size(); i++)
			if(a[i])	this->v.push_back(tm[i]);
		tm.clear();
	}
	~Double(){	};
};

class Boolea: public Column{
private:
	vector<char> v;
public:
	Boolea(string _path){	this->path = _path;	}
	void set(string q){	this->v.push_back(stoi(q)+48);	}
	string get(unsigned i){	
		/*ifstream file(this->path, ios::binary | ios::app);
		char a;
		file.seekg(sizeof(char)*i, ios::beg);
		file.read((char*)(&a),sizeof(char));
		return to_string(a-'0');*/
		return to_string(this->v[i]-'0');
	}
	void update(unsigned i, string q){	this->v[i] = stoi(q)+48;	}
	unsigned size(){	return this->v.size();	}
	void resize(unsigned i){	this->v.resize(i);	}
	void save(){
		ofstream file(path, ios::binary);
		if(!file.is_open())	cout << "error" << endl;
		else	file.write((char *)&this->v[0],this->v.size()*sizeof(char));
	}
	void load(){
		ifstream file(path, ios::binary | ios::app);
		if(!file.is_open())	cout << "error" << endl;
		else	file.read((char*)&this->v[0],this->v.size()*sizeof(char));
	}
	bool opr(string a, string b, char op){	return a==b;	}
	void clear(){	this->v.clear();	}
	void erase(unsigned i){	this->v.erase(this->v.begin()+i);	}
	void random(unsigned n){
		for(unsigned i=0; i<n; i++)
			this->v.push_back(48+rand()%2);
	}
	void refresh(vector<bool> &a){
		vector<char> tm = this->v;
		this->v.clear();
		for(unsigned i=0; i<a.size(); i++)
			if(a[i])	this->v.push_back(tm[i]);
		tm.clear();
	}
	~Boolea(){	};
};

class String: public Column{
private:
	vector<string> v;
public:
	String(string _path){	this->path = _path;	}
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
};



class Date: public Column{
private:
	vector<time_t> v;
public:
	Date(string _path){	this->path = _path;	}
	void set(string q){	(q == "0")?this->v.push_back(0) :this->v.push_back(to_time(q));	}
	string get(unsigned i){	
		/*ifstream file(this->path, ios::binary | ios::app);
		time_t a;
		file.seekg(sizeof(time_t)*i, ios::beg);
		file.read((char*)(&a),sizeof(time_t));
		return time_string(a);*/
		return time_string(this->v[i]);
	}
	void update(unsigned i, string q){	this->v[i] = to_time(q);	}
	unsigned size(){	return this->v.size();	}
	void resize(unsigned i){	this->v.resize(i);	}
	void save(){
		ofstream file(path, ios::binary);
		if(!file.is_open())	cout << "error" << endl;
		else	file.write((char *)&this->v[0],this->v.size()*sizeof(time_t));
	}
	void load(){
		ifstream file(path, ios::binary | ios::app);
		if(!file.is_open())	cout << "error" << endl;
		else	file.read((char*)&this->v[0],this->v.size()*sizeof(time_t));
	}
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
	void clear(){	this->v.clear();	}
	void erase(unsigned i){	this->v.erase(this->v.begin()+i);	}
	void random(unsigned n){
		for(unsigned i=0; i<n; i++)
			this->v.push_back(106213762+(rand()%(1506603798-106213762)));
	}
	void refresh(vector<bool> &a){
		vector<time_t> tm = this->v;
		this->v.clear();
		for(unsigned i=0; i<a.size(); i++)
			if(a[i])	this->v.push_back(tm[i]);
		tm.clear();
	}
	~Date(){	};
};

class Age: public Column{
private:
	vector<int8_t> v;
public:
	Age(string _path){	this->path = _path;	}
	void set(string q){	this->v.push_back(stoi(q));	}
	string get(unsigned i){	
		/*ifstream file(this->path, ios::binary | ios::app);
		int8_t a;
		file.seekg(sizeof(int8_t)*i, ios::beg);
		file.read((char*)(&a),sizeof(int8_t));
		return to_string(a);*/
		return to_string(this->v[i]);
	}
	void update(unsigned i, string q){	this->v[i] = (int8_t)stoi(q);	}
	unsigned size(){	return this->v.size();	}
	void resize(unsigned i){	this->v.resize(i);	}
	void save(){
		ofstream file(path, ios::binary);
		if(!file.is_open())	cout << "error" << endl;
		else	file.write((char *)&this->v[0],this->v.size()*sizeof(int8_t));
	}
	void load(){
		ifstream file(path, ios::binary | ios::app);
		if(!file.is_open())	cout << "error" << endl;
		else	file.read((char*)&this->v[0],this->v.size()*sizeof(int8_t));
	}
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
	void clear(){	this->v.clear();	}
	void erase(unsigned i){	this->v.erase(this->v.begin()+i);	}
	void random(unsigned n){
		for(unsigned i=0; i<n; i++)
			this->v.push_back(rand()%100);
	}
	void refresh(vector<bool> &a){
		vector<int8_t> tm = this->v;
		this->v.clear();
		for(unsigned i=0; i<a.size(); i++)
			if(a[i])	this->v.push_back(tm[i]);
		tm.clear();
	}
	~Age(){	};
};

#endif