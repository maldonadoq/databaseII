#ifndef _TB_H
#define _TB_H

#include "col.h"
#include "../../../Algoritmos/aed/src/cmp.h"
#include "redblack.h"
#include <vector>
#include <fstream>

using namespace std;

class cold{
public:
	int nc;
	string name, type, name_idx;;
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

   	void set_name(string _name){
   		this->idx = true;
   		this->name_idx = _name;
   	}

   	void set_idx(string tname){
   		if(!this->idx){
   			this->idx = true;
	   		this->name_idx = "index/"+tname+"_"+this->name+".bin";

	   		ofstream file(this->name_idx, ios::out | ios::binary);		
			file.seekp(0);
			vector<int> v(1000,-1);
			for(unsigned i=0; i<2; i++){
				file.write(reinterpret_cast<const char*>(&v[0]), v.size()*sizeof(int));
			}

			file.close();
		}
		else	cout << "      error! index in column " << this->name << " exist!" << endl;
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
			if(sw == "integer")	this->tb1.push_back(new Intege(nm,this->st));
			else if(sw == "boolean")	this->tb1.push_back(new Boolea(nm,this->st));
			else if(sw == "double")	this->tb1.push_back(new Double(nm,this->st));
			else if(sw == "date") this->tb1.push_back(new Date(nm,this->st));
			else if(sw == "age") this->tb1.push_back(new Age(nm,this->st));
			//else if(sw == "varchar") this->tb1.push_back(new String(nm));
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

		for(unsigned i=0; i<c.tb1[0]->size()-1; i++){
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

   	void random(unsigned n){
   		for(unsigned i=0; i<n; i++)	this->vd.push_back(true);
   		for(unsigned j=0; j<this->tb1.size(); j++)
   			this->tb1[j]->random(n);
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
