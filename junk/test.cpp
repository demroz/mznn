#include <iostream>
#include <string>

class A {
public:
    void (A::*l)(double,double);
    A(std::string name)
    {
        if(name=="l1"){
            l=&A::l1;
        }
        if(name == "l2")
        {
            l = &A::l2;
        }
    }

    void l1(double x, double y)
    {
        std::cout<<"l1 called"<<std::endl;
    }
    void l2(double x, double y)
    {
        std::cout<<"l2 called" << std::endl;
    }

    void call_l(double x, double y)
    {
        (this->*l)(x,y);
    }
};

int main() {
    A a("l1");
    A b("l2");

    a.call_l(1.0,1.0); // should call l1
    b.call_l(1.0,1.0);
}
