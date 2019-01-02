
#include <iostream>
#include <string>
#include <cassert>
#include "Map.h"
using namespace std;
int main(int argc, const char * argv[]) {

    using KeyType=std::string;
    using ValueType=double;
    
    
    Map m;
    m.insert("A", 10);
    m.insert("B", 44);
    m.insert("C", 10);
    
    KeyType all;
    ValueType total = 0;
    for (int n = 0; n < m.size(); n++)
    {
        KeyType k;
        ValueType v;
        m.get(n, k, v);
        all += k;
        total += v;
        
    }
    cout << all << total<<endl;

    
    
    Map gpas;
    gpas.insert("Fred", 2.956);
    gpas.insert("Ethel", 3.538);
    double v;
    string k1;
    assert(gpas.get(1,k1,v)  &&  (k1 == "Fred"  ||  k1 == "Ethel"));
    string k2;
    assert(gpas.get(1,k2,v)  &&  k2 == k1);
    //Notice that the empty string is just as good a string as any other; you should not treat it in any special way:
    
    
    // Map gpas;
    gpas.insert("Fred", 2.956);
    assert(!gpas.contains(""));
    gpas.insert("Ethel", 3.538);
    gpas.insert("", 4.000);
    gpas.insert("Lucy", 2.956);
    assert(gpas.contains(""));
    
    gpas.erase("Fred");
    
    assert(gpas.size() == 3  &&  gpas.contains("Lucy")  &&  gpas.contains("Ethel")  &&
           gpas.contains(""));
    
    //  Here's an example of the swap function:
    
    Map m1;
    m1.insert("Fred", 2.956);
    Map m2;
    m2.insert("Ethel", 3.538);
    m2.insert("Lucy", 2.956);
    m1.swap(m2);
    cout<<m1.size()<<m2.size()<<endl;
    assert(m1.contains("Lucy"));
    assert(m1.size() == 2  &&  m1.contains("Ethel")  &&  m1.contains("Lucy")  &&
           m2.size() == 1  &&  m2.contains("Fred"));
    
}
