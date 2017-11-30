#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]){
	vector<int> v(1000,-1);
	cout << v.size() << endl;
	cout << v[23] << endl;
	return 0;
}