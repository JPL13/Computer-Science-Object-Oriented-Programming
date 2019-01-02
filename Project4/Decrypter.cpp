#include "provided.h"
#include <string>
#include <vector>
#include <algorithm>    // std::sort
#include "MyHash.h"
using namespace std;

//helper
 bool compareNoCase( const string& first, const string& second ) {
     int i=0;
     while ((i < first.length()) && (i < second.length()))
     {
         if (tolower (first[i]) < tolower (second[i])) return true;
         else if (tolower (first[i]) > tolower (second[i])) return false;
         i++;
     }
     
     if (first.length() < second.length()) return true;
     else return false;
    }


class DecrypterImpl
{
public:
    bool load(string filename);
    vector<string> crack(const string& ciphertext);
private:
   
    void PickAWord(string& w, MyHash<string, bool>& table, vector<string>token_words, Translator* translator);
    void recursive(const string& ciphertext, vector<string>token_words, Translator* translator, Tokenizer* PTtokenizer, vector<string>& solutions);
    
    WordList wlist;
    
};

bool DecrypterImpl::load(string filename)
{
    //Your load() method must load the contents of the indicated word list text file, to be used
   // during the decrypting process. (Presumably, it will delegate this task to a WordList
   //                                 object.) Every time load() is called, it must discard the old list //of words and start fresh
    //before loading the new words. If this function successfully loads the words, it must
    //return true; otherwise it must return false.   O(W)

    return wlist.loadWordList(filename);
  
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
    vector<string>solutions;
    //1. Start with an empty mapping
    Translator translator;
    //2. Break up (“tokenize”) the ciphertext message into separate words and pick a ciphertext word w from the message that (a) has not yet been chosen and (b) has the most ciphertext letters for which we don’t have any translation. (When your algorithm first starts, this results in your picking the longest ciphertext word.)

    vector<string> token_words;
    
    
    Translator* PTtranslator;
    PTtranslator=&translator;
    
    Tokenizer tokenizer(" ,;:.!()[]{}-\"#$%^&0123456789");
    token_words=tokenizer.tokenize(ciphertext);
   
    Tokenizer* PTtokenizer;
    PTtokenizer=&tokenizer;
    

    recursive(ciphertext, token_words, PTtranslator, PTtokenizer, solutions);

 
    sort (solutions.begin(), solutions.end(), compareNoCase);
    return solutions;
}

void DecrypterImpl::PickAWord(string& w, MyHash<string, bool>& table, vector<string>token_words, Translator* translator)
{
    
    vector<string> unused_words;
    vector<string> translated_words;
    
    MyHash<string, string>cipher_trans;
 
    for (int i=0; i<token_words.size();i++ )
    {
        //find all unused words and put them into a vector
        if(*table.find(token_words[i])==false)
        { unused_words.push_back(token_words[i]);}
    }
    
    /* for (int i=0; i<unused_words.size();i++ )
     {
         cout<< "unused "<<i<<": "<<unused_words[i]<<endl;
     }*/
    int size=unused_words.size();
    
    //cout<<"how many unused :"<<size<<endl;
    int* num_marks=new int[size];
    //get translation of the unused_words
    int biggest=0;
   // w=unused_words[0];
    for (int i=0; i<unused_words.size();i++ )
    {
        num_marks[i]=0;
        string trans=translator->getTranslation(unused_words[i]);
        
       // cout<<"translation of the unused: "<<trans<<endl;
        translated_words.push_back(trans);
        cipher_trans.associate(unused_words[i], trans);
        for(int j=0; j<trans.size(); j++)
        {
            if(trans[j]=='?')
                num_marks[i]++;
        }
        //cout<<"Num of marks?  :"<<num_marks[i]<<endl;
        if(num_marks[i]>biggest)
        {biggest=num_marks[i];
            w=unused_words[i]; //pick the word w
           // cout<<"W is "<<w<<endl;
        }
     
    }
	delete[] num_marks;
    //mark w as used
    bool used=true;
    table.associate(w, used);
  
}


void DecrypterImpl::recursive(const string& ciphertext,  vector<string>token_words, Translator* translator, Tokenizer* PTtokenizer, vector<string>& solutions)
{
    MyHash<string, bool>table;
    int size=token_words.size();
   
    //initialize each word's used status as false, means not been used yet
    for(int i=0; i<token_words.size(); i++)
    {    bool used_words=false ;
        table.associate(token_words[i], used_words);
    }
        //pick a ciphertext word w from the message that (a) has not yet been chosen and (b) has the most ciphertext letters for which we don’t have any translation.
        string w;
        PickAWord(w, table, token_words, translator);
       // cout<<"string W is: "<<w<<endl;
        //3. Translate the chosen encrypted word using the current mapping table to get a partial decrypted translation.
        string currentTranslation=translator->getTranslation(w);
        
       // cout<<"Translation of string W is: "<<currentTranslation<<endl;
        //4. get a collection C of all words in the word list that could possibly match the ciphertext word compatibly with the partially decrypted version of the word.
        
        vector<string>C=wlist.findCandidates(w, currentTranslation);//to store candidates;
        
        /*  for(int i=0; i<C.size(); i++)
         {  cout<<"Candidate list: "<<C[i]<<endl; }   */
        
        //5.If there are no words in the list that could match the ciphertext word compatibly with the partially decrypted version of the word, so C is empty, then your current mapping table must be wrong, and your function can throw it away and return to the previous recursive call.
        if(C.empty())
        { translator->popMapping();
            return;}
        
        
        vector<string>::iterator it;
        
        //6.For each candidate plaintext word p in your collection C for ciphertext word w:
        for(it=C.begin(); it!=C.end(); it++)
        {
            //cout<<*it<<endl;
            if(!translator->pushMapping(w, *it))
            {continue; }//check next candidate in C
            else
            {  //Next use this partial proposed translation table to translate your entire ciphertext message into a proposed plaintext message.
                string plaintext=translator->getTranslation(ciphertext);
                vector<string>plain_token=PTtokenizer->tokenize(plaintext);
                //cout<<"plaintext: "<<plaintext<<endl;
                
                bool all_translated=true;//check if all plaintext words have no '?'
                bool all_found=true;//all fully translated are found in the wordlist
                
                
                for (int k=0; k<plain_token.size(); k++)
                {
                    bool full_translated=true;
                    
                    //check if the word is fully translated
                    for(int j=0; j<plain_token[k].size(); j++)
                    {
                        if(plain_token[k][j]=='?')
                        { full_translated=false;
                            all_translated=false;
                        }
                    }
                    
                    //i.If at least one fully-translated word cannot be found in the word list, then the temporary mapping we chose is wrong. go back to step 6
                    
                    if(full_translated && !wlist.contains(plain_token[k]))
                    {
                        translator->popMapping();
                        all_found=false;
                        break;//check next candidate in C
                    }//end if
                }//end for plain token iteration
                
                //ii. If all of the fully-translated words are found in our word list, but the message has not been completely translated (some words still have ?s in them that were not translated), then this partial solution is promising, as is the current proposed mapping table.
                //Recursively call step 2, passing in our temporary mapping as the new input mapping
                
                if(!all_translated )
                {
                    recursive(ciphertext, token_words, translator, PTtokenizer, solutions);
                }
                
                //iii. If every single word of the decrypted message was fully translated and in the word list, record this as a valid solution (potentially one of many) for eventual output to the user. Then discard the current temporary mapping and go back to step 6 to try other candidate translations for the chosen word w and their mappings.
                else
                {
                    //cout<<"solution: "<<plaintext<<endl;
                    solutions.push_back(plaintext);
                    translator->popMapping();
                    continue;//go to step 6
                }
                
            }//end else
        }//end for C iteration
    
    // 7.Having tried all the words in our collection C, throw away the current mapping table and return to the previous recursive call.
    
    if(it==C.end())
    { translator->popMapping();
        return;}
}


//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
   return m_impl->crack(ciphertext);
}
