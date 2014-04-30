#include <iostream>

using std::cerr;
using std::endl;

class A
{
public:
    A() { cerr << "A()" << endl; }
    A(const A&) { cerr << "A(const A& a)" << endl; }
    A(A &&) { cerr << "A(A &&)" << endl; }
    virtual ~A() { cerr << "~A()" << endl; }

private:
    /* data */
};

A CreateA(int n) {
    A a;
    A b;
    return (n > 5 ? a : b);
}

int main(int argc, char *argv[])
{
    //A b;
    A a(CreateA(5));
    return 0;
}
