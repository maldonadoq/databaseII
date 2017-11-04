#include <typeinfo>
#include <iostream>

using namespace std;

class Parent{
public:
    virtual void DoSomething();
    virtual ~Parent(){  };
};

class Child1 : public Parent{
public:
    int childMember;
    Child1(){
        this->childMember = 1;
    }
};

class Child2 : public Parent{
public:
    int childMember;
    Child2(){
        this->childMember = 2;
    }
};

void Parent::DoSomething(){
    if (typeid(Child1) == typeid(*this)){
        auto child = static_cast<Child1*>(this);
        cout << child->childMember << endl;
    }
    else if (typeid(Child2) == typeid(*this)){
        auto child = static_cast<Child2*>(this);
        cout << child->childMember << endl;
    }
};

int main(int argc, char const *argv[]){
    Parent *a = new Child2;
    a->DoSomething();
    delete a;
    return 0;
}