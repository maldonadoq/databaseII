#ifndef _TB_H
#define _TB_H

#include "col.h"
#include "../../../Algoritmos/aed/src/cmp.h"
#include "redblack.h"
using namespace std;

class cold{
public:
	int nc;
	string name, type;
	bool idx, ins;
	rbtree<int,cmg<int>> *ix;
	cold(int _c, string _name, string _type, bool _idx){
		this->nc = _c;
		this->name = _name;
		this->type = _type;
		this->idx = _idx;
		this->ins = false;
		this->ix = NULL;
	}
	friend ostream& operator<< (ostream & out, const cold &c){
		out << "[" << c.nc << "|" << c.name << "|" << c.type << "|" << c.idx << "]  ";
		return out;
   	}
};

class table{
public:
	vector<cold> c;
	string name, date, query;
	vector<Column *> tb1;
	vector<bool> vd;
	unsigned st;
	table(string _query, string _name, vector<cold> _c, string _date, unsigned _st){
		this->name = _name;
		this->c = _c;
		this->date = _date;
		this->st = _st;
		this->query = _query;
		this->vd = vector<bool>(this->st,true);
		string sw, nm;
		for(unsigned i=0; i<this->c.size(); i++){
			nm = "table/" + this->name + "_" + c[i].name + ".bin";
			sw = this->c[i].type;
			if(sw == "integer")	this->tb1.push_back(new Intege(nm));
			else if(sw == "boolean")	this->tb1.push_back(new Boolea(nm));
			else if(sw == "double")	this->tb1.push_back(new Double(nm));
			else if(sw == "varchar") this->tb1.push_back(new String(nm));
			else if(sw == "date") this->tb1.push_back(new Date(nm));
			else if(sw == "age") this->tb1.push_back(new Age(nm));
		}
	}

	void info(){
		cout << "    table name: " << this->name << "\t\tsize:\t" << this->tb1[0]->size() << endl << "    column:\t\t";
		for(unsigned i=0; i<this->c.size(); i++)
			cout << this->c[i];
		cout << endl << "    date:\t\t" << this->date << endl << endl;
	}

	friend ostream& operator<< (ostream & out, const table &c){
		out << "    " << c.name << endl << "    ";
		for(unsigned i=0; i<c.c.size(); i++)
			out << c.c[i].name << "\t";
		out << endl;

		for(unsigned i=0; i<c.tb1[0]->size(); i++){
			if(c.vd[i]==true){
				cout << "    ";
				for(unsigned j=0; j<c.tb1.size(); j++)
					out << c.tb1[j]->get(i) << "\t";
				out << endl;
			}
		}
       	return out;
   	}

   	int position(string a){
   		for(int i=0; i<(int)this->c.size(); i++){
   			if(c[i].name == a)	return i;
   		}
   		return -1;
   	}

   	void pv(){
   		for(unsigned i=0; i<this->c.size(); i++)
   			this->c[i].ins = false;
   	}

   	void rows_data(unsigned i){
   		cout << "    ";
   		for(unsigned j=0; j<this->tb1.size(); j++)
   			cout << this->tb1[j]->get(i) << "\t";
   		cout << endl;
   	}

   	void rows_erase(unsigned i){
   		for(unsigned j=0; j<this->tb1.size(); j++)
   			this->tb1[j]->erase(i);
   	}

   	void clear(){
   		this->vd.clear();
   		for(unsigned j=0; j<this->tb1.size(); j++)
   			this->tb1[j]->clear();
   	}
   	
   	void random(unsigned n){
   		for(unsigned i=0; i<n; i++)	this->vd.push_back(true);
   		for(unsigned j=0; j<this->tb1.size(); j++)
   			this->tb1[j]->random(n);
   	}

   	void refresh(){
   		for(unsigned j=0; j<this->tb1.size(); j++)
   			this->tb1[j]->refresh(this->vd);
   		this->vd = vector<bool>(this->tb1[0]->size(),true);
   	}
};

class res{
public:
    string name;
    vector<pair<string,string>> ve;
    res(string _name, vector<pair<string,string>> _ve){
        this->name = _name;
        this->ve = _ve;
    }
};

#endif


//CREATE USER 'maldonado'@'localhost' IDENTIFIED WITH mysql_native_password AS '***';GRANT ALL PRIVILEGES ON *.* TO 'maldonado'@'localhost' REQUIRE SSL WITH GRANT OPTION MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0 MAX_UPDATES_PER_HOUR 0 MAX_USER_CONNECTIONS 0;
//>time scan: 31.54000000 s
//>rows: 99