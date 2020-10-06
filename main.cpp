#include <iostream>
#include <string>
#include "iterator/iterator.h"
#include "container/vector.h"
#include "container/list.h"
#include "container/deque.h"
#include "container/heap.h"
#include <queue>
#include <vector>
using namespace std;
#include <iterator>
#include <list>
#include <algorithm>

int main() {
    cout << "TinySTL Welcome!!" << endl;
#if 0
    cout << "# Create new vector" << endl;
    TinySTL::vector<int> iv(2, 3);
    cout << "size = " << iv.size() << endl;
    cout << "capacity = " << iv.capacity() << endl;
    cout << "# Push some element" << endl;
    iv.push_back(1);
    iv.push_back(3);
    iv.push_back(4);
    cout << "size = " << iv.size() << " capacity = " << iv.capacity()
         << " and the element is "<< endl;
    for(int i = 0 ; i < iv.size() ; i ++)
        cout << iv[i] << ' ';
    cout << endl;
    cout << "# erase the first element " << endl;
    TinySTL::vector<int>::iterator ivite = iv.begin();
    auto it = iv.erase(ivite) ;
    for(int i = 0 ; i < iv.size() ; i ++)
        cout << iv[i] << ' ';
    cout << endl;

    cout << "# Test erase a sequence" << endl;
    TinySTL::vector<int>::iterator first = iv.begin() + 1;
    TinySTL::vector<int>::iterator last = first + 1;
    iv.erase(first, last);
    for(int i = 0 ; i < iv.size() ; i ++)
        cout << iv[i] << ' ';
    cout << endl;

    cout << "# Test insert " << endl;
    TinySTL::vector<int>::iterator i = iv.begin() + 1;
    iv.insert(i, 3, 0);
    cout << "size = " << iv.size() << " capacity = " << iv.capacity()
         << " and the element is "<< endl;
    for(int i = 0 ; i < iv.size() ; i ++)
        cout << iv[i] << ' ';
    cout << endl;
#endif

    return 0;
}
