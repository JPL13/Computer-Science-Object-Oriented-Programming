//
//  Map.cpp
//  Homework 1
//
//  Created by Juan Piao on 1/17/18.
//  Copyright © 2018 Piao. All rights reserved.
//

#include "Map.h"

#include <iostream>
using namespace std;

// Create an empty map (i.e., one with no key/value pairs)
Map::Map()
{
    m_size=0;
}
bool Map::empty() const  // Return true if the map is empty, otherwise false.
{
    if(m_size==0)
        return true;
    else
        return false;
}
int  Map::size() const   // Return the number of key/value pairs in the map.
{
    return m_size;
}
bool Map::insert(const KeyType& key, const ValueType& value)
// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map, or the map has a fixed
// capacity and is full).
{
    if(!contains(key)&&m_size<DEFAULT_MAX_ITEMS)
    {
        m_size++;
        data[m_size-1].key=key;
        data[m_size-1].value=value;
        return true;
    }
    else
        return false;
}
bool Map::update(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.
{
        if(contains(key))
        {
            for (int i = 0; i < m_size; i++)
            {
                if (data[i].key == key)
                {
                    data[i].value = value;
                }
            }
            
            return true;
        }
    
       else
           return false;
}
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// If key is not equal to any key currently in the map and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that the key is not already in the map and the map has a fixed
// capacity and is full).
{
    if(contains(key))
    {
        for (int i = 0; i < m_size; i++)
        {
            if (data[i].key == key)
            {
                data[i].value = value;
            }
        }
        
        return true;
    }
    
    else if(!contains(key)&&m_size<DEFAULT_MAX_ITEMS)
    {
        m_size++;
        data[m_size-1].key=key;
        data[m_size-1].value=value;
        return true;
    }
    
    else
        return false;
}
bool Map::erase(const KeyType& key)
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.
{
    if(contains(key))
    {
        for (int i = 0; i < m_size; i++)
        {
            if (data[i].key == key)
            {
               
                for(int j=i; j<m_size-1; j++)
                {
                    data[j].key = data[j+1].key;
                    data[j].value = data[j+1].value;
                }
                 m_size--;
            }
        }
       
        
        return true;
    }
    else
        return false;
}

bool Map::contains(const KeyType& key) const
// Return true if key is equal to a key currently in the map, otherwise
// false.
{
    for (int i = 0; i < m_size; i++)
    {
        if (data[i].key == key)
        {
            return true;
        }
    }
    return false;

}
bool Map::get(const KeyType& key, ValueType& value) const
// If key is equal to a key currently in the map, set value to the
// value in the map that that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.
{
    for (int i = 0; i < m_size; i++)
    {
        if (data[i].key == key)
        {
            value=data[i].value;
            return true;
        }
    }
    return false;
    
}
bool Map::get(int i, KeyType& key, ValueType& value) const
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of one of the key/value pairs in the map and return
// true.  Otherwise, leave the key and value parameters unchanged and
// return false.  (See below for details about this function.)
{
    if(i>=0&&i<m_size)
    {
        key=data[i].key;
        value=data[i].value;
        return true;
    }
    else
        return false;
}
void Map::swap(Map& other)
// Exchange the contents of this map with the other one.
{
    DataType temp;
    
    int size;
    
    if(m_size<other.size())
        size=other.size();
    else
        size=m_size;
    
   
    for (int i = 0; i < size; i++)
    {
        temp.key=data[i].key;
        temp.value=data[i].value;
        
        data[i].key=other.data[i].key;
        data[i].value=other.data[i].value;
        
        other.data[i].key= temp.key;
        other.data[i].value= temp.value;
 
    }
    int t=m_size;
    m_size=other.m_size;
    other.m_size=t;
    
    
}

