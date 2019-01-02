#include "provided.h"
#include "MyHash.h"
#include <string>
//#include <stack>
using namespace std;

template<typename KeyType>
class Stack
{
    int Top;
    
    int MAX=1000;
    int a[1000];    //Maximum size of Stack
    
public:
    Stack()  { Top = -1; }
    
    KeyType top(){return a[Top]; }
    
    bool push(int x)
    {
        if (Top >= MAX)
        {
            cout << "Stack Overflow";
            return false;
        }
        else
        {
            a[++Top] = x;
            return true;
        }
    }
    int pop()
    {
        if (Top < 0)
        {
            cout << "Stack Underflow";
            return 0;
        }
        else
        {
            int x = a[Top--];
            return x;
        }
    }
    bool isEmpty(){
        return (Top < 0);
    }
    
};



class TranslatorImpl
{
public:
    TranslatorImpl();
    ~TranslatorImpl();
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
    char alpha[26];
    char current[26];
    bool used[26];
    MyHash<char, Stack<char>> map;
    //declare an empty stack
    Stack<char> container;
    
    int num_pop;
    int num_push;
    
};
TranslatorImpl::TranslatorImpl()
{
    
    for(int i=0; i<26; i++)
    {
        alpha[i]='A'+ i;
        current[i]='?';
        used[i]=false;
        map.associate(alpha[i], container);
        container.push(current[i]);
    }
    
    
    num_pop=0;
    num_push=0;
}
TranslatorImpl::~TranslatorImpl()
{
    
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    if(ciphertext.size()!=plaintext.size())
        return false;
    
    for(int i=0; i<ciphertext.size(); i++)
    {
        ciphertext[i]=toupper(ciphertext[i]);
        plaintext[i]=toupper(plaintext[i]);
    }
    
    //check if conflicts occurs
    for(int i=0; i<ciphertext.size(); i++)
    {
        //if either contains a non-letter
        if(!isalpha(ciphertext[i])||!isalpha(plaintext[i]))
            return false;
        //if one ciphertext letter would map to two or more different plaintext letters,
        char temp=ciphertext[i];
        int pos=temp-'A';
        if(current[pos]!='?'&&current[pos]!=plaintext[i])
            return false;
        
        //if two or more different ciphertext letters map to the same plaintext letter.
        char temp2=plaintext[i];
        int pos2=temp2-'A';
        if(used[pos2]==true&&current[pos]!=plaintext[i])
            return false;
      
        /*for(int j=0; j<26; j++)
        {
            if(current[j]==plaintext[i])
            {  if( alpha[j]!=ciphertext[i])
                return false;}
            
        }*/
    }
    
    //after saving the current mapping table onto a stack and updating the current mapping table so that it incorporates the collection of new character mappings specified by the parameters.
    
    //push current map to stack
    
    for(int i=0; i<26; i++)
    {
        map.find(alpha[i])->push(current[i]);}
    
    //copy current map's content to a new map
    for(int i=0; i<26; i++)
    {
        current[i]=(*map.find(alpha[i])).top();
        
    }
    
    //updating the current mapping table
    for(int i=0; i<ciphertext.size(); i++)
    {
        char temp=ciphertext[i];
        int pos=temp-'A';
        current[pos]=plaintext[i];
        //mark plaintext[i] as used
        char temp2=plaintext[i];
        int pos2=temp2-'A';
        used[pos2]=true;
            
    }
  
    num_push++;
    return true;
    
}

bool TranslatorImpl::popMapping()
{
    if(num_pop==num_push)
        return false;
    //pop the most-recently pushed mapping table from the stack, make it current
    for(int i=0; i<26; i++)
    {
        used[i]=false;
    }
    for(int i=0; i<26; i++)
    {
        current[i]=(*map.find(alpha[i])).top();
        map.find(alpha[i])->pop();
        
        char temp2=current[i];
        int pos2=temp2-'A';
        //mark current[i] as used
        if(isalpha(current[i]))
        {used[pos2]=true;}
      
    }
    
    num_pop++;
    return true;
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
    string translation="";
    string cipher;
    for(int i=0; i<ciphertext.size(); i++)
    {
        cipher+=toupper(ciphertext[i]);
    }
    
    //If the ciphertext character is a letter that maps to a plaintext letter in the current mapping, then that plaintext letter appears, in the same case as in the ciphertext string.
    for(int i=0; i<ciphertext.size(); i++)
    {
        if(isalpha(ciphertext[i]))
        {
            if(isupper(ciphertext[i]))
            {
                int pos=ciphertext[i]-'A';
                translation+=current[pos];}
            else
            {    int pos=ciphertext[i]-'a';
                translation+=tolower(current[pos]);
                
            }
        }
        else
            // If the ciphertext character is not a letter, that character appears, unchanged.
            translation+=ciphertext[i];
        
    }
    
    return translation;
    
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}

