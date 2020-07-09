#include <iostream>
#include <string>
#include "container/vector.h"
using namespace std;

class testClass{
private:
    int a;
    int b;
public:
    testClass():a(0), b(0){}
    testClass(int _a, int _b): a(_a), b(_b) {}
};

int main() {
    cout << "TinySTL Welcome!!" << endl;

    TinySTL::vector<int*> a(10);
    TinySTL::vector<int> b;
    TinySTL::vector<char> c(5, 'c');

    cout << "The TinySTL sizeof = " << sizeof(a) << endl;

    cout << "The size of Vector: " << c.size()  << endl;
    cout << "The capacity of Vector: " << c.capacity() << endl;
    cout << "The empty of Vector:" << b.empty() << endl;
    c[4] = 'i';
    cout << "Print the 4th elem in c: " << c[4] << endl;
    return 0;
}
