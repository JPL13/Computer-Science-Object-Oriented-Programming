#include "provided.h"
#include <string>
#include <vector>
#include "MyHash.h"
#include <iostream>
#include <fstream>
using namespace std;

class WordListImpl
{
public:
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
    MyHash<string, vector<string>> words_map;
    string index(string word)const;
};

bool WordListImpl::loadWordList(string filename)
{
    //Your loadWordList() method must load the contents of the indicated word list text file
    //into data structures.If this function is able to open the file and load the words, it must return true;otherwise it must return false.
    
    
    words_map.reset();
    ifstream infile(filename);
    if (!infile)
        return false;
    
    else
    {
        std::string s;
        
        while (infile>>s)
        {
            //cout<<s<<' ';
            bool is_valid=true;
            
            for(int i=0; i<s.size(); i++)
            {
                //turn s to lower case
                s[i]=tolower(s[i]);
                
                if(!islower(s[i])&&s[i]!=39)
                { is_valid=false;
                    break;}
            }
            if(is_valid)
            {    string indexed_s=index(s);
                
                //cerr<<indexed_s<<endl;
                //if the indexed words not in the map
                if(words_map.find(indexed_s)==nullptr)
                {
                    vector<string> v; //declare an empty vector
                    v.push_back(s);
                    words_map.associate(indexed_s, v);
                    
                }
                else
                {
                    words_map.find(indexed_s)->push_back(s);  //put s into the existing vector
                }
                //cerr<<words_map.getNumItems()<<endl;
            }
        }//end while
        return true;
    }
    
}

bool WordListImpl::contains(string word) const
{
    //The contains() method is used to determine if the specified word is in the word list. The
    //method must return true if the specified word is in the currently-loaded word list, or false
    //    otherwise.
    string indexed_s=index(word);
    
    for(int i=0; i<word.size(); i++)
    {
        //turn s to lower case
        word[i]=tolower(word[i]);
    }
    
    if(words_map.find(indexed_s)!=nullptr)
    {
        vector<string> v=*words_map.find(indexed_s);
        for (vector<string>::const_iterator it = v.begin() ; it != v.end(); ++it)
        {
            if(*it==word)
                return true;
        }
    }
    
    return false; // This compiles, but may not be correct
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    // Use letter patterns to index your word list data!
    //Using a pattern scheme and a clever hash-based data structure, we could
    //easily locate all plaintext words that have the same pattern as a given ciphertext word.
    //We could then further reduce the collection of viable words by eliminating those that are
    //inconsistent with currTranslation.
    vector<string> candidates;
    string cipher_indexed=index(cipherWord);
    
    //cout<<"Index: "<<cipher_indexed<<endl;
    
    //check if empty
    if(words_map.find(cipher_indexed)==nullptr)
    {
        vector<string> v;
        return v;
    }
    vector<string> all_plaintext=*words_map.find(cipher_indexed);
 
    //TESTING***********
  // for (vector<string>::const_iterator it = all_plaintext.begin() ; it != all_plaintext.end(); ++it)
  //      cerr<<*it<<endl;
    //TESTING***********
    for (vector<string>::const_iterator it = all_plaintext.begin() ; it != all_plaintext.end(); ++it)
    {
        bool is_candidate=true;
        for (int i=0; i<(*it).size(); i++)
        {
            
            if(currTranslation[i]!='?'&&(*it)[i]!=tolower(currTranslation[i]))
            {
                is_candidate=false;
            }
            if(islower((*it)[i])&&!isalpha(cipherWord[i]))
            {
                is_candidate=false;
            }
            if((*it)[i]==39&&cipherWord[i]!=39)
            {
                is_candidate=false;
            }
        }
        if(is_candidate)
        candidates.push_back(*it);
      
    }
    
    return candidates;  // This compiles, but may not be correct
}

string WordListImpl::index(string word) const
{
    MyHash<char, char> index_map;
    int index=0;
    char* index_letters=new char[word.size()];//declare an array of chars to hold A B C D ..
    index_letters[0]='A';
    for(int i=1; i<word.size(); i++)
    {
        index_letters[i]='A'+i;
    }
    
    //tolower
    for(int i=0; i<word.size(); i++)
    {
        word[i]=tolower(word[i]);
    }
    
    //cout<<"to be indexed: "<<word<<endl;
    for(int i=0; i<word.size(); i++)
    {
        if(islower(word[i]))//if alpha
        {
            if(index_map.find(tolower(word[i]))==nullptr)//if not already in the map
            {
                index_map.associate(tolower(word[i]), index_letters[i]); //put the letter and the index pair in the map
                index++;
            }
            
        }
        else //if not alphabet
            index_map.associate(word[i], word[i]);
    }
    
    string indexed_word="";
    
    for(int i=0; i<word.size(); i++)
    {
        indexed_word+=*index_map.find(word[i]);
    }
    
	delete []index_letters;
    return indexed_word;
    
}


//***** hash functions for string, int, and char *****

unsigned int hash(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hash(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hash(const char& c)
{
    return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
   return m_impl->findCandidates(cipherWord, currTranslation);
}
