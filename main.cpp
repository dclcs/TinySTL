#include <iostream>
#include <string>
#include "container/vector.h"
using namespace std;
#if 0
template<typename Alloc>
void cookie_test(Alloc alloc, size_t n){
    typename Alloc::value_type *p1, *p2, *p3;
    p1 = alloc.allocate(n);
    p2 = alloc.allocate(n);
    p3 = alloc.allocate(n);

    cout << "p1 = " << p1 << '\t' << "p2 = " << p2 << '\t' << "p3 = " << p3 << endl;

    alloc.deallocate(p1, sizeof(typename Alloc::value_type));
    alloc.deallocate(p2, sizeof(typename Alloc::value_type));
    alloc.deallocate(p3, sizeof(typename Alloc::value_type));
}
#endif



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

    cout << sizeof(Airplane) << endl;
    size_t const N = 100;
    Airplane* p[N];
    for( int i = 0 ; i < N ; ++i )
        p[i] = new Airplane;
    for( int i = 0 ; i < 10 ; i ++)
        cout << p[i] << endl;
    for( int i = 0 ; i < N ; i ++)
        delete p[i];

    cout << sizeof(__gnu_cxx::__pool_alloc<int>) << endl; //1
    cout << sizeof(double) << endl;
    vector<int, __gnu_cxx::__pool_alloc<int>> vecPool;
    cookie_test(__gnu_cxx::__pool_alloc<double>(), 1);

    cout << sizeof(std::allocator<int>) << endl; //1
    vector<int, std::allocator<int>> vec;
    cookie_test(std::allocator<double>(), 1);
#endif
    TinySTL::vector<int> a(10);
    cout << sizeof(a) << endl;
    return 0;
}
