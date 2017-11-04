#ifndef _STR_H_
#define _STR_H_

#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
#include <sstream>
#include <fstream>

using namespace std;

vector<string> typ(){
	vector<string> t;
	t.push_back("integer");	t.push_back("double");
	t.push_back("varchar");	t.push_back("boolean");
	t.push_back("date");	t.push_back("age");
	return t;
}

static vector<string> types = typ();

template<class T>
void print_(vector<T> v){
	for(unsigned i=0; i<v.size(); i++)
		cout << v[i] << " ";
	cout << endl;
}

string getline(FILE *t, unsigned l){
	char c;
	unsigned i=0;
	string tm="";
	while((c=getc(t))!=EOF){
		if(c=='\n')	i++;
		if(i==l){
			if(c=='\n')	break;
			tm+=c;
		}
	}
	return tm;
}

string date(){
	time_t _tm =time(NULL );
	struct tm * curtime = localtime (&_tm);
	string t = (string)asctime(curtime);
	t[t.size()-1] = ' ';
	return t;
}

string stri(string a,int s, int e){
	string z = "";
	for(int i=s; i<=e; i++)	z+=a[i];
	return z;
}

void load_tx(FILE *a, string bq){
    for(int i=0;bq[i]!='\0';i++){
        fprintf(a, "%c",bq[i]);
    }
    fprintf(a,"%c",'\n');
}

void next_to_find(string a, unsigned &i, char b){
	for(; a[i]!=b; i++);
	i++;
}

string partial_partition(string a, unsigned &s, char c){
    string t = "";
    for(; a[s] == ' '; s++);
    for(; a[s]!=c; s++)   t += a[s];
    s++;
    return t;
}

void fill(vector<string> &v, string a, unsigned &i){
	unsigned ct = 0, k=i;
	for(; a[i]!=')'; i++)
		if(a[i] == ',')	ct++;
	for(unsigned j=0; j<ct; j++)
		v.push_back(partial_partition(a,k,','));
	v.push_back(partial_partition(a,k,')'));

}

bool validate_type(string t){
	for(unsigned i=0; i<types.size(); i++)
		if(types[i] == t)	return true;
	cout << "type invalid!" << endl;
	return false;
}

bool partial_pair(vector<pair<string, string>> &v, vector<string> &vs){
    string type, name;
    unsigned j;
    for(unsigned i=0; i<vs.size(); i++){
        j=0;
        name = partial_partition(vs[i],j,' ');
        type = partial_partition(vs[i],j,'\0');
        if(!validate_type(type))	return false;
        v.push_back(pair<string,string>(name,type));
    }
    return true;
}

bool validate_column(vector<int> v){
	for(unsigned i=0; i<v.size(); i++)
		if(v[i]<0)	return false;
	return true;
}

bool to_bool(string const& s) {
     return s != "0";
}

char pair_(pair<string,string> &v, string w){
	unsigned j = 0;
	v.first = partial_partition(w,j,' ');
	char op = w[j];
	j++;
	v.second = partial_partition(w,j,'\0');
	return op;
}

double double_random(double mn, double mx){
    return mn + (((double)rand()/RAND_MAX)*(mx-mn));
}

string string_random(){
	string a = "";
	for(int i=0; i < 3; i++)
        a += 97+rand()%(122-97);
    return a;
}

string time_string(time_t now){
	if(now == 0) return "NULL";
	char buff[20];
	strftime(buff,20,"%Y-%m-%d %H:%M:%S",localtime(&now));
	return string(buff);
}


time_t to_time(string dat){
	dat[10] = 'T';
	dat += 'Z';
	wstring date_t(dat.begin(), dat.end());
	static const wstring date_tFormat{ L"%Y-%m-%dT%H:%M:%SZ" };
	wistringstream ss{ date_t };   tm dt;
	ss >> get_time(&dt, date_tFormat.c_str());
	return mktime(&dt);
}

#endif