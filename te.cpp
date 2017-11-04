#include <iostream>
#include <vector>
#include <time.h>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

#define N (4 + 5*3 + 1 + 1)

template<class T>
void print(vector<T> &v){
	for(unsigned i=0; i<v.size(); i++)
		cout << v[i] << " ";
	cout << endl;
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

string time_string(time_t now){
	char buff[20];
	strftime(buff,20,"%Y-%m-%d %H:%M:%S",localtime(&now));
	return string(buff);
}

int main(int argc, char const *argv[]){
	time_t now = 0;
	cout << now << endl;
	cout << time_string(now) << endl;


	string s = "";
    srand(time(NULL));
    for(int i=0; i <= 9; i++)
        s += 97+rand()%(122-97);
    cout << s << endl;
}
//1506213762