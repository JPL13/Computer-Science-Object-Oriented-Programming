//
//  Map.cpp
//  Project2
//
//  Created by Juan Piao on 1/25/18.
//  Copyright © 2018 Piao. All rights reserved.
//

#include "Map.h"
#include <iostream>
#include <cstdlib>
using namespace std;

//construct an empty Map through circularly double linked lists
Map::Map()
: m_size(0)
{
    head = new Node;
    head->m_next = head;
    head->m_previous = head;
    
}
//copy constructor
Map::Map(const Map& other)
: m_size(other.m_size)
{
    head = new Node;        // Initializes new head.
    head->m_next = head;
    head->m_previous = head;
    
    for (Node* p = other.head->m_next; p != other.head; p = p->m_next) // Loop through the current map
    {
        Node* adder = new Node;
        adder->m_value = p->m_value;
        adder->m_key = p->m_key;
        adder->m_next = head;
        adder->m_previous = head->m_previous;
        head->m_previous->m_next = adder;
        head->m_previous = adder;
    }
}

//destructor
Map::~Map()
{
    while (head->m_previous != head)
    {
        Node* deleter = head->m_previous;
        deleter->m_previous->m_next= head;
        head->m_previous = deleter->m_previous;
        delete deleter;
    }
    delete head;
}

//assignment operator
Map& Map::operator=(const Map& rhs)
{
    if (this != &rhs)
    {
        Map temp(rhs);
        swap(temp);
    }
    return *this;
}

bool Map::erase(const KeyType& key)
{
    int pos = find(key);
    
    
    if (pos >= 0 || pos < size())    //if key is found in the list
    {
        Node* p = head; //use p to traverse through the linked list
        for (int i = 0; i < size(); i++)
        {
            p = p->m_next;
            if(i==pos)
            {  Node* deleter = p;      //use deleter to point to the item to be deleted
                //rearrange the surrounding items
                p->m_previous->m_next = deleter->m_next;
                p->m_next->m_previous = deleter->m_previous;
                
                delete deleter; //delete the target item
               
                m_size--; //reduce m_size by 1
                return true;
            }
        }
        
    }
    
    return false;
   
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    int pos = find(key);
    
     if (pos >= 0 || pos < size()) //if key is found in the list
     {
         Node* p = head; //use p to traverse through the linked list
         for (int i = 0; i <size(); i++)
         {
             p = p->m_next;
             
             if(i==pos)
             {
                 value=p->m_value; //set the value to which the key maps to
                 return true;
             }
         }
     }
   
      return false;
}

// If 0 <= i < size(), copy into the key and value parameters the
// key and value of one of the key/value pairs in the map and return
// true.  Otherwise, leave the key and value parameters unchanged and
// return false.
bool Map::get(int i, KeyType& key, ValueType& value) const
{
    
    if (i >= 0 || i < size())
    {
        Node* p = head; //use p to traverse through the linked list
        
        for (int j = 0; j < size(); j++)
        {
            p = p->m_next;
            
            if (j == i)
            {
                key=p->m_key;     //copy into the key with the ith key in the map
                value=p->m_value; //set the value to which the key maps to
                return true;
            }
            
        }
        
    }
    
    return false;
}

void Map::swap(Map& other)
{
    // Swap the head pointers
    
    Node* temp_head = other.head;
    other.head = head;
    head = temp_head;
    
    // Swap sizes
    
    int t = m_size;
    m_size = other.m_size;
    other.m_size = t;
    
}

//if find "key" in the existing map, return its position
int Map::find(const KeyType& key) const
{
    if (size() > 0)
    {
        Node* p = head; //use p to traverse through the linked list
        for (int i = 0; i < size(); i++)
        {
            p = p->m_next;      // Point p to the next item
            if (p->m_key == key)
                return i;
        }
    }
    return -1;
}

bool Map::doInsertOrUpdate(const KeyType& key, const ValueType& value,
                           bool mayInsert, bool mayUpdate)
{
    int pos = find(key);
    if (pos != -1)  // found
    {
        if (mayUpdate)
        {
             Node* p = head; //use p to traverse through the linked list
            for (int i = 0; i <size(); i++)
            {
                p = p->m_next;
                if(i==pos)
               {
                p->m_value=value; //update the corresponding value
                 return mayUpdate;
               }
            }
        }
        
    }
    else if (mayInsert)  // not found, and allowed to insert
    {
        //insert the new node at the end
        
        Node* p = head->m_previous; //point p to the last item in the map
        
        //create a new item to store the key and value
        Node* newItem = new Node;
        newItem->m_value = value;
        newItem->m_key=key;
        //link the new item with head and the previous item
        newItem->m_next = head;
        newItem->m_previous = p;
        p->m_next = newItem;
        head->m_previous = newItem;
        m_size++;
        
 
       return true;
    }

        return false;
}

bool combine(const Map& m1, const Map& m2, Map& result)
{
    if(result.size()!=0)
    {    Map temp;  //create a new Map object which is empty
        result=temp; //assign the empty Map to "result"
    }
    
    result=m1;
    
    bool check=true;
    KeyType k;
    ValueType v1, v2;
        for(int i=0;i<m2.size();i++)
        {
            
            m2.get(i,k,v2);
            
                 if(!m1.contains(k))
                 {
                     result.insert(k,v2);
                     
                 }
            
            
                 else if(m1.get(k,v1)&&v1!=v2)
                 {
                     result.erase(k);
                     check=false;
                 }
 
        }
        
        return check;
}

void subtract(const Map& m1, const Map& m2, Map& result)
{
    
    if(result.size()!=0)
    {    Map temp;  //create a new Map object which is empty
        result=temp; //assign the empty Map to "result"
    }
    
    result=m1;

    for(int i=0;i<m1.size();i++)
    {
        KeyType k;
        ValueType v1;
        m1.get(i,k,v1);
        
        if(m2.contains(k))
            result.erase(k);
    
    }
    
    
}

void Map::dump() const     // Prints out all the values in the Sequence to cerr for teting purposes.
{
    for (Node* p = head->m_next; p != head; p = p->m_next)
        std::cerr <<p->m_key <<" "<<p->m_value << std::endl;
}

