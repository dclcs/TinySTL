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

    TinySTL::vector<int> iv(2, 9);
    cout << "size = " << iv.size() << endl;
    cout << "capacity = " << iv.capacity() << endl;
    iv.push_back(1);
    cout << "size = " << iv.size() << endl;
    cout << "capacity = " << iv.capacity() << endl;

    iv.push_back(3);
    cout << "size = " << iv.size() << endl;
    cout << "capacity = " << iv.capacity() << endl;

    iv.push_back(4);
    cout << "size = " << iv.size() << endl;
    cout << "capacity = " << iv.capacity() << endl;

    for(int i = 0 ; i < iv.size() ; i ++)
        cout << iv[i] << ' ';
    cout << endl;
    TinySTL::vector<int>::iterator ivite = iv.begin() + 2;
    auto it = iv.erase(ivite) ;
    for(int i = 0 ; i < iv.size() ; i ++)
        cout << iv[i] << ' ';
    cout << endl;
    cout << *it << endl;
    return 0;
}
