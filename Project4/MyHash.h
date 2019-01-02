// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.
#include <iostream>
template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5):m_maxLoadFactor(maxLoadFactor)
    {
        NUM_BUCK=100;
        table = new Bucket*[NUM_BUCK];
        for (int i = 0; i < NUM_BUCK; i++)
            table[i] = NULL;
        m_numOfItems=0;
        
        if(maxLoadFactor<=0)
            m_maxLoadFactor=0.5;
        
    }
    ~MyHash()
    {
        clear();
    }
    void reset()
    {
        clear();
       NUM_BUCK=100;
       m_numOfItems=0;
       table = new Bucket*[NUM_BUCK];
        for (int i = 0; i < NUM_BUCK; i++)
            table[i] = NULL;
        
    }
    
    void associate(const KeyType& key, const ValueType& value)
    {
        if(find(key)==nullptr)
    {
        //test
       // std::cout<<getLoadFactor()<<std::endl;
        if(getLoadFactor()>=m_maxLoadFactor)
          { resize();}
    }
        insert(key, value);
        
    }
    int getNumItems() const{return m_numOfItems;}
    double getLoadFactor() const{return (m_numOfItems+0.0)/NUM_BUCK;}

      // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const
    {
        unsigned int hash(const KeyType& k); // prototype
        unsigned int h = hash(key);
        int hash_Val= h % NUM_BUCK;
        
        Bucket* entry = table[hash_Val];
        while (entry != nullptr && entry->getKey()!=key){
            entry = entry->getNext();
        }
        
        if (entry==nullptr)//not found
            return nullptr;
        else
            return entry->getValue();
    }

      // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }

      // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;

private:
    class Bucket;
    double m_maxLoadFactor;
    int NUM_BUCK;
    int m_numOfItems;
    Bucket** table;
    
    //helper function
    void clear()
    {
        for (int i = 0; i < NUM_BUCK; i++)
        {
            if (table[i] != NULL) {
                Bucket *prevEntry = NULL;
                Bucket *entry = table[i];
                while (entry != NULL) {
                    prevEntry = entry;
                    entry = entry->getNext();
                    delete prevEntry;
                }//end while
            }//end if
        }//end for
        delete[] table;
    }
    
    
    void insert(const KeyType& key, const ValueType& value)
    {
        //check if the key is already in the table
        if(find(key)!=nullptr)  //key already in the table
        {*find(key)=value;
            return;}
        unsigned int hash(const KeyType& k); // prototype
        unsigned int h = hash(key);
        int hash_Val= h % NUM_BUCK;
        //if table not empty
        if (table[hash_Val] != NULL)
        {
           // bool found = false;
           // Bucket* temp;
           // temp=table[hash_Val];
          /* if(found)
            { while(temp!=nullptr)
            {
                //key already in the table, update
              if(temp->getKey()==key){
                    //update the value
                  temp->setValue(value);
                   found = true;
                    break;
                    
                  }//end if
                }//end while
            }
            
           */
                //insert in front
                Bucket* newBucket = new Bucket(key, value, table[hash_Val]);
                table[hash_Val] = newBucket;
                
                m_numOfItems++;
        
            
            
        }//end if
        
        //if  empty
        else
        {
            table[hash_Val] = new Bucket(key, value);
            m_numOfItems++;
        }
        
    }
    
    void resize()
    {
        int oldTableSize = NUM_BUCK;
        NUM_BUCK*=2;
        
        Bucket** oldTable = table;
        table = new Bucket*[NUM_BUCK];
        for (int i = 0; i < NUM_BUCK; i++)
            table[i] = NULL;
        m_numOfItems = 0;
        for (int hash = 0; hash < oldTableSize; hash++)
            if (oldTable[hash] != NULL) {
                Bucket *oldEntry;
                Bucket *entry = oldTable[hash];
                while (entry != NULL) {
                    insert(entry->getKey(), *(entry->getValue()));
                    oldEntry = entry;
                    entry = entry->getNext();
                    delete oldEntry;
                }
            }
        delete[] oldTable;
        
    }
    
    class Bucket {
    private:
        KeyType key;
        ValueType value;
        Bucket* next;
    public:
        
        Bucket(KeyType key, ValueType value, Bucket* next=NULL) {
            this->key = key;
            this->value = value;
            this->next=next;
        }
        
        KeyType getKey() {
            return key;
        }
        
        ValueType* getValue() {
            return &value;
        }
        void setValue(ValueType v) {
            this->value=v;
        }
        
        Bucket* getNext() {
            return next;
        }
        
    };
     
};
