#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

time_t getEpochTime(const wstring& dateTime){
       static const wstring dateTimeFormat{ L"%Y-%m-%dT%H:%M:%SZ" };
       wistringstream ss{ dateTime };   tm dt;
       ss >> get_time(&dt, dateTimeFormat.c_str());
       return mktime(&dt);
}

int main(void){
    wstring dateTimeStr{ L"2017-09-23T19:42:42Z" };
    cout << getEpochTime(dateTimeStr) << std::endl;

       return 0;
}
