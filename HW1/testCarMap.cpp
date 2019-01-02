#include <iostream>
#include <string>
#include <cassert>
#include "CarMap.h"

using namespace std;

int main(int argc, const char * argv[]){
    
    CarMap cars;
    cars.addCar("ABC");
    cars.addCar("wer");
    cars.addGas("ABC", 30.5);
    cars.useGas("ABC", 10);
    cars.useGas("wer", 30);
    cout<< cars.gas("ABC")<<endl;
    cars.print();
    cout<<cars.fleetSize()<<endl;
    
    
    
    
    
}



