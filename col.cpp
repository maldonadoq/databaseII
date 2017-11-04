#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include "src/str.h"

using namespace std;

template<class _I, class _F, class _D, class _S, class _B>
class box_type{
public:
	typedef box_type<_I,_F,_D,_S,_B>	self;
	typedef _I							I;
	typedef _F							F;
	typedef _D							D;
	typedef _S							S;
	typedef _B							B;
};

template<class Bx>
class Column{
public:
	virtual void set(string) = 0;
	virtual string get(unsigned) = 0;
	virtual void print()=0;
protected:
	string name, type;
	friend ostream& operator<< (ostream & out, const Column &c){
		out << "[" << c.name << " | " << c.type << "]";
		return out;
   	}
   	virtual ~Column(){	};
};

template<class Bx>
class Integer: public Column<Bx>{
private:
	typedef typename Bx::I 	I;
	vector<I> v;
public:
	Integer(string _name, string _type){
		this->name = _name;
		this->type = _type;
	}

	void set(string q){	this->v.push_back(stoi(q));	}
	string get(unsigned i){	return to_string(this->v[i]);	}

	void print(){
		for(unsigned i=0; i<this->v.size(); i++)	cout << this->v[i] << " ";
		cout << endl;
   	}

	~Integer(){	};
};

template<class Bx>
class Double: public Column<Bx>{
private:
	typedef typename Bx::D 	D;
	vector<D> v;
public:
	Double(string _name, string _type){
		this->name = _name;
		this->type = _type;
	}

	void set(string q){	this->v.push_back(stod(q));	}
	string get(unsigned i){	return to_string(this->v[i]);	}

	void print(){
		for(unsigned i=0; i<this->v.size(); i++)	cout << this->v[i] << " ";
		cout << endl;
   	}

	~Double(){	};
};

template<class Bx>
class String: public Column<Bx>{
private:
	typedef typename Bx::S 	S;
	vector<S> v;
public:
	String(string _name, string _type){
		this->name = _name;
		this->type = _type;
	}

	void set(string q){	this->v.push_back(q);	}
	string get(unsigned i){	return this->v[i];	}

	void print(){
		for(unsigned i=0; i<this->v.size(); i++)	cout << this->v[i] << " ";
		cout << endl;
   	}

	~String(){	};
};

template<class Bx>
class Boolean: public Column<Bx>{
private:
	typedef typename Bx::B 	B;
	vector<B> v;
public:
	Boolean(string _name, string _type){
		this->name = _name;
		this->type = _type;
	}

	void set(string q){	this->v.push_back(stoi(q));	}
	string get(unsigned i){	return to_string(this->v[i]);	}

	void print(){
		for(unsigned i=0; i<this->v.size(); i++)	cout << this->v[i] << " ";
		cout << endl;
   	}

	~Boolean(){	};
};

typedef box_type<int,float,double,string,bool>	types;
int main(int argc, char const *argv[]){
	
	vector<Column<types> *> vec;
	vec.push_back(new Integer<types>("id_user","Integer"));
	vec.push_back(new Double<types>("money","Double"));
	vec.push_back(new Boolean<types>("state","Boolean"));
	vec.push_back(new String<types>("name","String"));

	vec[0]->set("12");
	vec[0]->set("2");
	vec[0]->set("132322");

	vec[1]->set("1.2323");
	vec[1]->set("0.210323");
	vec[1]->set("12.2324");
	vec[1]->set("0.000312");

	vec[2]->set("1");
	vec[2]->set("0");

	vec[3]->set("Hello");
	vec[3]->set("World");


	for(unsigned i=0; i<vec.size(); i++)
		vec[i]->print();

	cout << vec[1]->get(1) << endl;
	return 0;
}
