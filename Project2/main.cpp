#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    
    Map m;   //create an empty map
    assert(m.empty());  //check if it is empty
    assert(m.insert("Fred", 123));  //insert 2 pairs of data
    assert(m.insert("Ethel", 456));
    assert(m.size() == 2);  //check the size
    
    ValueType v = 42;
    
    assert(!m.get("Lucy", v)  &&  v == 42); //test to make sure the get(k,v)function returns false if the key is not in the list
    assert(m.get("Fred", v)  &&  v == 123); //test to make sure if the key can be found in the list, the value get reset to the value in the map
  
    v = 42;
    KeyType x = "Lucy";
    assert(m.get(0, x, v)  &&
           ((x == "Fred"  &&  v == 123)  ||  (x == "Ethel"  &&  v == 456))); //to make sure the key and value parameters are reset to the key and value of one of the key/value pairs in the map
    KeyType x2 = "Ricky";
    assert(m.get(1, x2, v)  &&
           ((x2 == "Fred"  &&  v == 123)  ||  (x2 == "Ethel"  &&  v == 456))  &&
           x != x2);
    
    Map m0(m);  //test copy constructor
    assert(m0.size() == 2);
    Map m00;
    m00.swap(m0); //test swap function
    assert(m00.size() == 2); // the size of m00 is 2 which is the size of m0
    assert(m0.size() == 0); // the size is correct after the swap
    assert(m00.insert("Lucy", 777));
    assert(!m00.erase("XX")); //make sure we can't erase something that's not in the list
    assert(m00.erase("Fred")&&m00.size()==2); //erase the first item in  m00 and check the size
    assert(m00.erase("Lucy")&&m00.size()==1); //erase the latest item in  m00 and check the size
    assert(m00.erase("Ethel")&&m00.size()==0); //erase the last item in  m00 and check the size
    
    
    
    
    
    //test the combind functionality
    Map m1,m2,m3,result;
    m1.insert("Fred", 123);
    m1.insert("Ethel", 456);
    m1.insert("Lucy", 789);
    
    m2.insert("Lucy", 654);
    m2.insert("Ricky", 321);
    combine(m1,m2,result);
    assert(!result.contains("Lucy")&&result.size()==3);//the result doesn't contain "Lucy" since the value of "Lucy" in m1 and m2 are different
    m2.update("Lucy",789); //now update the value of "Lucy" in m2 to 789 to make the value the same as in m1
    combine(m1,m2,result);
    assert(result.contains("Lucy")&&result.size()==4);//now the result contain "Lucy" and the size is 4
    //result.dump();
    
    cerr<<"________"<<endl;
    
    //test the subtract functionality
    m3.insert("Lucy", 789);
    m3.insert("Ricky", 321);
    m3.insert("Ethel", 654);
    subtract(m1,m3,result);
    
     assert(!result.contains("Lucy")&&result.contains("Fred")&&result.size()==1);
    // m1.dump();
    // m2.dump();
    //result.dump(); //test to see if the result only contains "Fred"
    
    
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
    

}
