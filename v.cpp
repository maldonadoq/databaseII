#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char const *argv[]){
    string ip = "31.3241.23";
    string port = " 4321";
    ofstream file1("lastServers.bin", ios::out | ios::binary);
    if (file1.good()) {
        file1.write(ip.c_str(), ip.size());
        file1.write(port.c_str(), port.size());
        file1.close();
    }
    else {
        std::cout << "file error write" << endl;
    }    

    char w = '0';
    string z = "";
    cout << w << endl;
    cout << ""+2 << endl;
    return 0;
}

/*
int main(){
  ofstream file("dates.out");

  vector<string> Test(2);

  Test[0] = "01-Jul-09";
  Test[1] = "01-Jul-10";

  for(unsigned int i=0; i<Test.size(); i++)
    file << Test[i] << endl;
  file.close();
}
*/