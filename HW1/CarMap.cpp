//
//  CarMap.cpp
//  Homework 1
//
//  Created by Juan Piao on 1/18/18.
//  Copyright © 2018 Piao. All rights reserved.
//

#include "CarMap.h"

#include <iostream>
#include <string>
using namespace std;


CarMap::CarMap():C_map()      // Create an empty car map.
{
}
bool CarMap::addCar(string license)
// If a car with the given license plate is not currently in the map,
// and there is room in the map, add an entry for that car recording
// that it has 0 gallons of gas in it, and return true.  Otherwise,
// make no change to the map and return false.
{
    if(!C_map.contains(license)&&fleetSize()<DEFAULT_MAX_ITEMS)
    {
        C_map.insert(license,0);
        return true;
    }
     else
         return false;
}

double CarMap::gas(string license) const
// If a car with the given license plate is in the map, return the
// number of gallons of gas in its tank; otherwise, return -1.
{
    double gas;
    return C_map.get(license, gas)?gas:-1;
   
}
bool CarMap::addGas(string license, double gallons)
// If no car with the given license plate is in the map or if
// gallons is negative, make no change to the map and return
// false.  Otherwise, increase the number of gallons of gas in the
// indicated car by the gallons parameter and return true.
{
    double gas;
    if(!C_map.contains(license)||gallons<0)
        return false;
    else
    {
        if (C_map.get(license, gas))
            {
                double newGas;
                newGas=gas+gallons;
                C_map.update(license,newGas);
            }
        return true;
    }
    
}
bool CarMap::useGas(string license, double gallons)
// If no car with the given license plate is in the map or if
// gallons is negative or if gallons > gas(), make no change to the
// map and return false.  Otherwise, decrease the number of gallons
// of gas in the indicated car by the gallons parameter and return
// true.
{
    double g;
    if(!C_map.contains(license)||gallons<0 || gallons > gas(license))
        return false;
    else
    {
        if (C_map.get(license, g))
            {
                double newGas;
                newGas=g-gallons;
                C_map.update(license,newGas);
            }
            return true;
        
    }
    
}
int CarMap::fleetSize() const  // Return the number of cars in the CarMap.
{
    return C_map.size();
}
void CarMap::print() const
// Write to cout one line for every car in the map.  Each line
// consists of the car's license plate, followed by one space,
// followed by the number of gallons in that car's tank.  Write
// no other text.
{
    string license;
    double gas;
    
    for(int i=0; i<C_map.size(); i++)
    {
        C_map.get(i,license, gas);
        cout<<license<<" "<<gas<<endl;
        
    }
}
