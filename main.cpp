#include <iostream>
#include <string>
#include "tutor/Screen.h"
#include "tutor/Airplane.h"
using namespace std;


int main() {
    cout << "TinySTL Welcome!!" << endl;
#if 0
    cout << "sizeof(int) = " << sizeof(int) << endl;
    cout << sizeof(Screen) << endl; //16

    size_t const N = 100;
    Screen* p[N];
    for( int i = 0 ; i < N ; ++ i)
        p[i] = new Screen(i);
    //输出前10个pointers， 比较间隔
    for(int i = 0 ; i < 10 ; ++ i){//间隔16
        cout << p[i] << endl;
    }

    for(int i = 0 ; i < N ; ++ i)
        delete p[i];
    return 0;
#endif

#if 0
    cout << sizeof(Airplane) << endl;
    size_t const N = 100;
    Airplane* p[N];
    for( int i = 0 ; i < N ; ++i )
        p[i] = new Airplane;
    for( int i = 0 ; i < 10 ; i ++)
        cout << p[i] << endl;
    for( int i = 0 ; i < N ; i ++)
        delete p[i];
#endif
}
