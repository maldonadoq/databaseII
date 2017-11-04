#ifndef _DB_H_
#define _DB_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <utility>
#include <unistd.h>
#include <sys/time.h>
#include "str.h"
#include "tb.h"

#define sc "create table "
#define si "insert into "
#define ss "select * from "
#define ssidx "select| * from "
#define sw "where"
#define sd "drop table "
#define su "update table "
#define sdd "delete from "
#define sidx "create| index on "

using namespace std;

class db{
private:
	FILE *nt, *nts;			  // tables
public:
	vector<table> table_name;	//numero de tablas
	vector<string> vcr;
	db(){	};

	vector<cold> create(vector<pair<string,string>>);
	res * partition(string);
	void create_table(string);
	void create_index(string);
	void insert_into(string);
	void select_from(string);
	void select_from_index(string);
	void delete_from(string);
	void drop_table(string);
	void update_where(string);
	void load_table();
	void save_table();
	void show_table();
	void load_a();
	void save_a();
	void random(string);
	table* find_(string);
	~db(){		};
};

res * db::partition(string wr){
    string nam = "";
    vector<pair<string, string>> v;
    vector<string> vs;

    unsigned i=0, j, ct=0, k;
    string tm = "";
    for(; i<=12; i++)    tm += wr[i];
    if(tm != sc){
    	cout << "      error!! query like this! \"create table table_name(...\"" << endl;
    	return NULL;
    }

    for(j=i; j<wr.size(); j++)  if(wr[j]==',')  	ct++;
    nam  = partial_partition(wr,i,'(');   // name
    for(k=0; k<ct; k++)
        vs.push_back(partial_partition(wr,i,','));
    vs.push_back(partial_partition(wr,i,')'));

    if(!partial_pair(v,vs))	return NULL;

    return new res(nam,v);
}

// read .sql to create tables!
void db::load_table(){
	this->nt = fopen("nt.sql","r");
	char c;
	int i=0, j=0;
	unsigned size;
	string t="";
	string nam = "", crtb = "", dat="", tm="";
	res *tmp;
	while((c=getc(this->nt))!=EOF){
		if(j==0 and c!='\n')	t+=c;
		else if(j==1 and c!='\n')	t+=c;
		else if(c=='\n'){
			if(i==0){
				j++;
				crtb = t;
				t = "";
				i++;
			}
			else if(i==1){
				dat = t;
				t = "";
				i++;
			}
			else if(i==2){
				size = stoi(t);
				tmp = partition(crtb);   							//pair <name, tpe>
				if(tmp!=NULL)
					table_name.push_back(table(crtb,tmp->name,create(tmp->ve),dat,size)); 	//create table
				i++;
			}
			else if(i==3){
				t="";
				j=0;
				i=0;
			}
		}
	}
	fclose(this->nt);
}

void db::show_table(){
	if(this->table_name.size() == 0){
		cout << "    Database empty!" << endl;
		return;
	}
	for(unsigned i=0; i<this->table_name.size(); i++)
		this->table_name[i].info();	
}

// un vector de columnas, para el atributo de table
vector<cold> db::create(vector<pair<string,string>> pa){
	vector<cold> v;
	for(unsigned i=0; i<pa.size(); i++)	v.push_back(cold(i,pa[i].first,pa[i].second,false));
	return v;
}

void db::save_table(){
	this->nts = fopen("nt.sql","w");
	for(unsigned i=0; i<this->table_name.size(); i++){
		load_tx(this->nts,this->table_name[i].query);
		load_tx(this->nts,this->table_name[i].date);
		load_tx(this->nts,to_string(this->table_name[i].tb1[0]->size()));
		fprintf(this->nts,"%c",'\n');
	}
	fclose(this->nts);
}

void db::load_a(){
	load_table();
	if(this->table_name.size()!=0){
		for(unsigned i=0; i<this->table_name.size(); i++){
			for(unsigned j=0; j<this->table_name[i].tb1.size(); j++){
				this->table_name[i].tb1[j]->resize(this->table_name[i].st);
				this->table_name[i].tb1[j]->load();
			}
		}
	}
}

void db::save_a(){
	for(unsigned i=0; i<this->table_name.size(); i++){
		this->table_name[i].refresh();
		for(unsigned j=0; j<this->table_name[i].tb1.size(); j++){
			this->table_name[i].tb1[j]->save();
		}	
	}
	save_table();
}

table* db::find_(string a){
	for(unsigned i=0; i<this->table_name.size(); i++)
		if(this->table_name[i].name == a)	return &table_name[i];
	return NULL;
}

void db::create_table(string a){
	if(a.size()<=12){	cout << "      error!!!" << endl;	return;	}
	res *tmp = partition(a);
	string r;
	if(tmp!=NULL)
		this->table_name.push_back(table(a,tmp->name,create(tmp->ve),date(),0)); 	//create table
}

void db::create_index(string a){
	if(a.size()<=16){	cout << "      error!!!" << endl;	}
	string tm = "", nam, col;
	table * tbm;			//table
	unsigned i=0, j;		//variables to partial partition
	int pos;
    for(; i<=16; i++)    tm += a[i];
    if(tm != sidx){
    	cout << "      error!! query like this! \"create| index on table_name\"" << endl;
    	return;
    }
	
	nam = partial_partition(a,i,'-');
	tbm = this->find_(nam);
	if(tbm!=NULL){
		col = partial_partition(a,i,';');
		pos = tbm->position(col);
		if(pos>=0){
			tbm->c[pos].ix = new rbtree<int, cmg<int>>();
			tbm->c[pos].idx = true;
			for(unsigned i=0; i<tbm->tb1[pos]->size(); i++)
				tbm->c[pos].ix->insert(stoi(tbm->tb1[pos]->get(i)),i);
		}
		else	cout << "      error!! doesn't exist this column!!" << endl;
	}
	else	cout << "      error!! doesn't exist this table!!" << endl;
}

void db::insert_into(string a){
	if(a.size()<=11){	cout << "      error!!!" << endl;	}
	string tm = "", nam;
	vector<string> val, dat;
	vector<int> bpos;		//bool position, all column
	table * tbm;			//table
	unsigned i=0, j;		//variables to partial partition
    for(; i<=11; i++)    tm += a[i];
    if(tm != si){
    	cout << "      error!! query like this! \"insert into table_name(...\"" << endl;
    	return;
    }
	
	nam = partial_partition(a,i,'(');
	tbm = this->find_(nam);
	if(tbm != NULL){
		fill(val,a,i);			//name of columns (name, id)
		next_to_find(a,i,'(');	
		fill(dat,a,i);			//data of column to insert (percy,01)
		if(val.size()!=dat.size() or (val.size()>tbm->c.size())){	cout << "      error!! wrong data!!" << endl;	return;	}

		// search position of val(name)
		for(j=0; j<val.size(); j++)
			bpos.push_back(tbm->position(val[j]));

		if(validate_column(bpos)){
			for(j=0; j<bpos.size(); j++){
				if(tbm->c[bpos[j]].idx)
					tbm->c[bpos[j]].ix->insert(stoi(dat[j]), tbm->tb1[bpos[j]]->size());
				tbm->tb1[bpos[j]]->set(dat[j]);
				tbm->c[bpos[j]].ins = true;
			}
			for(j=0; j<tbm->c.size(); j++){
				if(tbm->c[j].ins == false){
					if(tbm->c[bpos[j]].idx)
						tbm->c[bpos[j]].ix->insert(stoi("0"), tbm->tb1[bpos[j]]->size());
					tbm->tb1[j]->set("0");
				}
			}
			tbm->vd.push_back(true);
			tbm->pv();
		}
		else	cout << "      error!! doesn't exist this column!!" << endl;
	}
	else	cout << "      error!! doesn't exist this table!!" << endl;
}

void db::select_from(string a){
	if(a.size()<=13){	cout << "      error!!!" << endl;	return;	}
	string tm = "", nam, wh, cond, fr;
	table * tbm;			//table
	pair<string,string> par;
	char op;
	unsigned i=0,j, l;		//variables to partial partition
	int k = -1;
    for(; i<=13; i++)    tm += a[i];
    if(tm != ss){
    	cout << "      error!! query like this! \"select * from  ...\"" << endl;
    	return;
    }
	
	l = i;
	nam = partial_partition(a,i,' ');
	fr = partial_partition(a,l,a[a.size()-2]);
	tbm = this->find_(nam);
	if(nam == fr and tbm != NULL)	cout << *tbm << endl;
	else if(tbm != NULL){
		if(sw != partial_partition(a,i,' ')){
			cout << "      error!! query like this! \"select * from  table_name where col_name = id;\"" << endl;		
			return;
		}
		cond = partial_partition(a,i,';');

		op = pair_(par,cond);

		for(j=0; j<tbm->tb1.size(); j++)
			if(tbm->c[j].name == par.first){	k = j;	break;	}

		if(k<0){
			cout << "      error! doesn't exist this column!" << endl;
			return;
		}

		struct timeval ti, tf;
    	double tiempo;
		gettimeofday(&ti, NULL);

		cout << "    " << tbm->name << endl << "    ";
		for(unsigned i=0; i<tbm->c.size(); i++)
			cout << tbm->c[i].name << "\t";
		cout << endl;

		unsigned nr=0;
		for(unsigned i=0; i<tbm->tb1[k]->size(); i++){
			if(tbm->vd[i]==true and tbm->tb1[k]->opr(tbm->tb1[k]->get(i),par.second,op)){
				tbm->rows_data(i);
				nr++;
			}
		}

		gettimeofday(&tf, NULL);
	    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
	    printf("\n     >time table-scan: %.8lf s\n",tiempo/1000);
	    cout << "     >rows: " << nr << endl;
	}
	else	cout << "      error!! doesn't exist this table" << endl;
}

void db::select_from_index(string a){
	if(a.size()<=14){	cout << "      error!!!" << endl;	return;	}
	string tm = "", nam, wh, cond, fr;
	table * tbm;			//table
	pair<string,string> par;
	char op;
	unsigned i=0,j, l;		//variables to partial partition
	int k = -1;
    for(; i<=14; i++)    tm += a[i];
    if(tm != ssidx){
    	cout << "      error!! query like this! \"select| * from  ...\"" << endl;
    	return;
    }
	
	l = i;
	nam = partial_partition(a,i,' ');
	fr = partial_partition(a,l,a[a.size()-2]);
	tbm = this->find_(nam);
	if(nam == fr and tbm != NULL)	cout << *tbm << endl;
	else if(tbm != NULL){
		if(sw != partial_partition(a,i,' ')){
			cout << "      error!! query like this! \"select * from  table_name where col_name = id;\"" << endl;		
			return;
		}
		cond = partial_partition(a,i,';');

		op = pair_(par,cond);

		for(j=0; j<tbm->tb1.size(); j++)
			if(tbm->c[j].name == par.first){	k = j;	break;	}

		if(k<0){
			cout << "      error! doesn't exist this column!" << endl;
			return;
		}

		struct timeval ti, tf;
    	double tiempo;
		gettimeofday(&ti, NULL);

		cout << "    " << tbm->name << endl << "    ";
		for(unsigned i=0; i<tbm->c.size(); i++)
			cout << tbm->c[i].name << "\t";
		cout << endl;

		unsigned nr=0;
		rbnode<int> *x = tbm->c[k].ix->search(stoi(par.second));
		if(x!=NULL){
			nr = x->pointer.size();
			for(unsigned i=0; i<nr; i++)
				tbm->rows_data(x->pointer[i]);
		}
		else	nr=0;

		gettimeofday(&tf, NULL);
	    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
	    printf("\n     >time red-black: %.8lf s\n",tiempo/1000);
	    cout << "     >rows: " << nr << endl;
	}
	else	cout << "      error!! doesn't exist this table" << endl;
}

void db::update_where(string a){
	if(a.size()<=12){	cout << "      error!!!" << endl;	return;	}
	string tm = "", nam, set, cond;
	table * tbm;
	pair<string,string> par, par1;
	char op;
	unsigned i=0, j;
	int k = -1, l = -1;
    for(; i<=12; i++)    tm += a[i];
    if(tm != su){
    	cout << "      error!! query like this! \"update table table_name ...\"" << endl;
    	return;
    }

    unsigned ctd = 0;
	nam = partial_partition(a,i,' ');
	tbm = this->find_(nam);
	if(partial_partition(a,i,' ')=="set" and tbm != NULL){
		set = partial_partition(a,i,',');
		op = pair_(par,set);	i++;

		if(sw != partial_partition(a,i,' ')){
			cout << "      error!! query like this! \"update table table_name set namc = new, where nmc = x;\"" << endl;
			return;
		}

		cond = partial_partition(a,i,';');
		op = pair_(par1,cond);

		for(j=0; j<tbm->tb1.size(); j++){
			if(tbm->c[j].name == par.first){	k = j;	ctd++;	}
			if(tbm->c[j].name == par1.first){	l = j;	ctd++;	}
			if(ctd == 2)	break;
		}

		if(k<0 or l<0){
			cout << "      error! doesn't exist this column!" << endl;
			return;
		}
		
		for(i=0; i<tbm->tb1[l]->size(); i++){
			if(tbm->vd[i]==true and tbm->tb1[l]->opr(tbm->tb1[l]->get(i),par1.second,op))
				tbm->tb1[k]->update(i,par.second);
		}
	}
	else
		cout << "      error!! query like this! \"update table table_name set namc = new, where nmc = x;\"" << endl;
}

void db::delete_from(string a){
	if(a.size()<=11){	cout << "      error!!!" << endl;	return;	}
	string tm = "", nam, wh, cond, fr;
	table * tbm;
	pair<string,string> par;
	char op;
	unsigned i=0,j, l;
	int k = -1;
    for(; i<=11; i++)    tm += a[i];
    if(tm != sdd){
    	cout << "      error!! query like this! \"delete from  ...\"" << endl;
    	return;
    }
	
	l = i;
	nam = partial_partition(a,i,' ');
	fr = partial_partition(a,l,a[a.size()-2]);
	tbm = this->find_(nam);
	if(nam == fr and tbm != NULL)	tbm->clear();
	else if(tbm != NULL){
		if(sw != partial_partition(a,i,' ')){
			cout << "      error!! query like this! \"delete from table_name where col_name = id;\"" << endl;
			return;
		}
		cond = partial_partition(a,i,';');

		op = pair_(par,cond);

		for(j=0; j<tbm->tb1.size(); j++)
			if(tbm->c[j].name == par.first){	k = j;	break;	}

		if(k<0){
			cout << "      error! doesn't exist this column!" << endl;
			return;
		}

		for(unsigned i=0; i<tbm->tb1[k]->size(); i++){
			if(tbm->vd[i]==true and tbm->tb1[k]->opr(tbm->tb1[k]->get(i),par.second,op)){
				//tbm->rows_erase(i);
				//i--;
				tbm->vd[i] = false;
			}
		}
	}
	else	cout << "      error!! doesn't exist this table" << endl;
}

void db::drop_table(string a){
	if(a.size()<=10){	cout << "      error!!!" << endl;	}
	string tm = "", nam, dh;
	unsigned i=0, k;
	int j = -1;
    for(; i<=10; i++)    tm += a[i];
    if(tm != sd){
    	cout << "      error!! query like this! \"drop table table_name;\"" << endl;
    	return;
    }
    nam = partial_partition(a,i,';');

    for(k=0; k<this->table_name.size(); k++)
    	if(this->table_name[k].name == nam){	j = k;	break;	}

    if(j<0){
    	cout << "      error!! doesn't exist this table!!" << endl;
    	return;
    }

    cout << "    remove table: " << nam << endl;
    for(k=0; k<this->table_name[j].c.size(); k++){
    	dh = "table/"+nam+"_"+this->table_name[j].c[k].name;
    	char z[dh.size()+4];

    	if(this->table_name[j].c[k].type == "varchar"){
    		dh += ".out";	strcpy(z,dh.c_str());
    		remove(z);
    	}
    	else	dh += ".bin";	strcpy(z,dh.c_str());	remove(z);
    	cout << "     +column: " << z <<endl;
    }
    this->table_name.erase(this->table_name.begin()+j);
}

void db::random(string a){
	unsigned i = 7;
	string nam = partial_partition(a,i,' ');
	unsigned n = stoi(partial_partition(a,i,';'));
	
	table *tmb;
	tmb = this->find_(nam);
	tmb->random(n);
}

#endif


//>time scan: 2.89600000 s
//>rows: 100061

//>time table-scan: 14.65700000 s
//>rows: 499214