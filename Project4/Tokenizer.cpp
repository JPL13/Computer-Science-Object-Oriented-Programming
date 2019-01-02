#include "provided.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    ~TokenizerImpl(){delete [] delimiter;}
    vector<string> tokenize(const std::string& s) const;
private:
    int size;
    char* delimiter;
};

TokenizerImpl::TokenizerImpl(string separators)
{
    size=separators.size();
    delimiter=new char[size];
    
    for(int i=0; i<size; i++)
        delimiter[i]=separators[i];
}

vector<string> TokenizerImpl::tokenize(const std::string& s) const
{
    std::vector<std::string> list;
   // for(int i=0;i<size;i++)
   // {
   //     char c=delimiter[i];
       // std::cout<<c<<std::endl;
   // }
    
    unsigned long obj_size = s.length();
    int counter = 0;
    
    
    std::string temp = "";
    for (int i=0;i<obj_size;i++)
    {
        char current_char = s[i];
        
        bool it_is_one_of_them=false;
        
        for(int j=0;j<size;j++)
        {
            
            if(current_char==delimiter[j])
            {it_is_one_of_them=true;}
            
        }
        
        if (it_is_one_of_them==false)
        {
            temp += current_char;
            counter++;
            
            if(i==obj_size-1)
                list.push_back(temp);
        }
        else
        {
            if (counter!=0)
            {
                list.push_back(temp);
                temp = "";
                counter = 0;          
            }
            
        }
    }
    
    //std:: cout<<list.size()<<std::endl;
    
    return list;
    
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const std::string& s) const
{
    return m_impl->tokenize(s);
}
