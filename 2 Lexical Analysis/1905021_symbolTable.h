/*
|***************AUTHOR**************|

  ======|| ||\\        //||  ======||
||         || \\      // || ||
||         ||  \\    //  || ||
  ======   ||   \\  //   ||   ======
       ||  ||    \\//    ||        ||
       ||  ||            ||        ||
||======   ||            || ||======

*/
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define endl "\n"
#define fast_io ios_base::sync_with_stdio(false); cin.tie(0);

class symbolInfo{
private:
    string name, type;
    symbolInfo* next = nullptr;

public:
    symbolInfo(){

    }

    symbolInfo(const string &name, const string &type){
        this->name = name; this->type = type;

    }

    virtual ~symbolInfo(){ 

    }

    void setName(const string &name){
        this->name = name;

    }

    const string &getName() const{
        return this->name;

    }

    void setType(){
        this->type = type;

    }

    const string &getType() const{
        return this->type;

    }

    void setNext(symbolInfo* next){
        this->next = next;

    }

    symbolInfo* getNext() const{
        return this->next;

    }

};

class scopeTable{
private:
    int tableId = 0; 
    int bucketSize;//numBuckets
    symbolInfo** hashTable;
    scopeTable* parentScope = nullptr;
public:
    scopeTable(int bucketSize,int n){
        tableId = n;
        this->bucketSize = bucketSize;
        hashTable = new symbolInfo*[bucketSize];
        for(int i=0; i<bucketSize; ++i){
            hashTable[i] = nullptr;
        }
        cout <<"\t"<< "ScopeTable# " << tableId << " created" << endl;
        //tableId = 1;
    }

    virtual ~scopeTable(){
        //?
        for(int i=0; i<bucketSize; ++i){
            if(hashTable[i] != nullptr) delete hashTable[i];
        }
        delete[] hashTable;
    }

    void setHashTable(symbolInfo** hashTable){
        this->hashTable = hashTable;

    }

    symbolInfo** getHashTable() const{
        return this->hashTable;

    }

    /*
    Insert_into_symbol_table  -> lookup -> delete -> print
    */
    void setBucketSize(int bucketSize){
        this->bucketSize = bucketSize;

    }

    int getBucketSize() const{
        return this->bucketSize;
    }


    unsigned long getHash(string str){
        unsigned long hash = 0;
        unsigned long i =0;
        unsigned long len = str.length();
        for(i=0; i< len; ++i){
            hash = ((str[i]) + (hash << 6) + (hash << 16) - hash)%bucketSize;
        }

        return hash%bucketSize;

    }
    
    //check whether the symbol already in scopeTable
    symbolInfo* insertHelp(string key){
        int index = getHash(key);
        symbolInfo* symbolInfHash = hashTable[index];
        int idx = 0;
        while(symbolInfHash != nullptr){
            if(symbolInfHash->getName() == key){
                //cout<<"'"<<key<<"'"<<" found in ScopeTable# "<<tableId<<" at position "<<index+1<<", "<<idx+1<<endl;
                return symbolInfHash;
            }
            symbolInfHash = symbolInfHash->getNext();
            idx++;
        }
        return nullptr;

    }

    bool insertIntoSymbolTable(symbolInfo symbolInf){
        string name, type;
        name = symbolInf.getName();
        type = symbolInf.getType();

        if(insertHelp(name) != nullptr){
            cout<<"'"<<symbolInf.getName()<<"' "<<" already exists in the current ScopeTable"<<endl;
            return false;
        }
        int index = getHash(name);
        symbolInfo* newSymbolInf = new symbolInfo(name, type);
        int incr = 0;
        if(hashTable[index] == nullptr) hashTable[index] = newSymbolInf;
        else{
            symbolInfo* symbolInfHash = hashTable[index];
            while(symbolInfHash->getNext() != nullptr){
                symbolInfHash = symbolInfHash->getNext(); incr++;
            }
            incr++;
            symbolInfHash->setNext(newSymbolInf);
        }
        cout<<"Inserted in ScopeTable# "<<tableId<<" at position "<<index+1<<", "<<incr+1<<endl;
        return true;



    }

    symbolInfo* lookupSymbol(string key){
        int index = getHash(key);
        symbolInfo* symbolInfHash = hashTable[index];
        int idx = 0;
        while(symbolInfHash != nullptr){
            if(symbolInfHash->getName() == key){
                cout<<"'"<<key<<"'"<<" found in ScopeTable# "<<tableId<<" at position "<<index+1<<", "<<idx+1<<endl;
                return symbolInfHash;
            }
            symbolInfHash = symbolInfHash->getNext();
            idx++;
        }
        return nullptr;

    }

    bool deleteSymbol(string key){
        int index = getHash(key);
        int position = 0;
        symbolInfo* symbolInfHash = hashTable[index];
        if(symbolInfHash == nullptr) return false;
        else if(symbolInfHash->getName() == key){
            cout<<"Deleted "<<"'"<<key<<"'"<<" from ScopeTable# "<<tableId<<" at position "<< index+1<<", "<<position+1<<endl;
            hashTable[index] = symbolInfHash->getNext();
            return true;
        }

        symbolInfo* symbol = symbolInfHash;
        while(symbolInfHash != nullptr){
            if(symbolInfHash->getName() == key){
                symbol->setNext(symbolInfHash->getNext());
                cout<<"Deleted "<<"'"<<key<<"'"<<" from ScopeTable# "<<tableId<<" at position "<< index+1<<", "<<position+1<<endl;
                delete symbolInfHash;
                return true;
            }
            position++;
            symbol = symbolInfHash;
            symbolInfHash = symbolInfHash->getNext();
        }
        return false;

    }

    void printScopeTable(ofstream &out){
        
        out<<"\t"<<"ScopeTable# "<<tableId<<endl;
        for(int i=0; i<bucketSize; ++i){
            symbolInfo* head = hashTable[i];
            if(head == nullptr) continue;
            out<<"\t";
            out<<i+1<<"--> ";
            while(head != nullptr){
                out<<"<"<<head->getName()<<","<<head->getType()<<"> ";
                head = head->getNext();
            }
            out<<endl;
        }
        //cout<<endl;

    }

    void setTableId(int tableId){
        this->tableId = tableId;
    }

    int getTableId() const{
        return this->tableId;
    }

    void setParentScopeTable(scopeTable* parentScope){
        this->parentScope = parentScope;

    }

    scopeTable* getParentScopeTable() const{
        return this->parentScope;

    }

};


class symbolTable{
    scopeTable* currScopeTable;
    int bucketSize = 2;
    int countScopeTable;
public:
    symbolTable(int bucketSize){
        this->countScopeTable = 1;
        this->bucketSize = bucketSize;
        currScopeTable = new scopeTable(bucketSize,countScopeTable);
        //cout<<"           ukaluka"<<endl;


    }

    ~symbolTable(){
        while(currScopeTable != nullptr){
            scopeTable* parentScopeTable = currScopeTable->getParentScopeTable();
            delete currScopeTable;
            currScopeTable = parentScopeTable;
        }
    }

    void setCurrScopeTable(scopeTable* currScopeTable){
        this->currScopeTable = currScopeTable;

    }

    scopeTable* getCurrScopeTable() const{
        return this->currScopeTable;

    }

    void setBucketSize(int bucketSize){
        this->bucketSize = bucketSize;

    }

    int getBucketSize() const{
        return this->bucketSize;

    }

    /* enter -> exit -> insert-> remove -> lookup -> printCurr-> printAll*/

    void enterScope(){
        scopeTable* newScopeTable = new scopeTable(bucketSize,++countScopeTable);
        newScopeTable->setParentScopeTable(currScopeTable);
        currScopeTable = newScopeTable;
        

//        cout<<"ScopeTable# "<<currScopeTable->getTableId()<<" created"<<endl;


    }

    void exitScope(){
        if(currScopeTable == nullptr) return;
        scopeTable* deleteCurrScopeTable = currScopeTable;
        currScopeTable = currScopeTable->getParentScopeTable();
        if(deleteCurrScopeTable->getParentScopeTable() == nullptr){
            cout<<"ScopeTable# "<<deleteCurrScopeTable->getTableId()<<" cannot be removed"<<endl;
            currScopeTable = deleteCurrScopeTable;
            return;
        }
        cout<<"ScopeTable# "<<deleteCurrScopeTable->getTableId()<<" removed"<<endl;
        delete deleteCurrScopeTable;
        /*scopeTable* cScopeTable = currScopeTable;
        while(currScopeTable->getParentScopeTable() != nullptr){
            currScopeTable->setChildCounter(currScopeTable->getChildCounter()-1);
            currScopeTable = currScopeTable->getParentScopeTable();

        }*/


    }

    void quitHelp(){
        if(currScopeTable == nullptr) return;
        scopeTable* deleteCurrScopeTable = currScopeTable;
        currScopeTable = currScopeTable->getParentScopeTable();
        cout<<"ScopeTable# "<<deleteCurrScopeTable->getTableId()<<" removed"<<endl;
        delete deleteCurrScopeTable;
        


    }

    void quitScope(){
        if(currScopeTable == nullptr) return;
        while(currScopeTable != nullptr ){
            cout<<"\t";
            quitHelp();
        }

    }

    bool insert(symbolInfo symbolInf,ofstream &out){
        if(currScopeTable == nullptr) return false;
        bool success = currScopeTable->insertIntoSymbolTable(symbolInf);
        if(!success){
            out<<"\t"<<symbolInf.getName()<<" already exists in the current ScopeTable"<<endl;
        }
        return success;

    }

    bool remove(string key){
        if(currScopeTable == nullptr) return false;
        bool delete_success = currScopeTable->deleteSymbol(key);
        if(!delete_success) cout<<"Not found in the current ScopeTable"<<endl;

        return delete_success;

    }

    symbolInfo* lookup(string key){
        scopeTable* scpTable = currScopeTable;
        while(scpTable != nullptr){
            symbolInfo* sInfo = scpTable->lookupSymbol(key);
            if(sInfo != nullptr) return sInfo;
            scpTable = scpTable->getParentScopeTable();
        }
        cout<<"'"<<key<<"'"<<" not found in any of the ScopeTables"<<endl;
        return nullptr;

    }

    void printCurrScopeTable(){
        //currScopeTable->printScopeTable();

    }

    void printAllScopeTable(ofstream &out){
        scopeTable* curr = currScopeTable;
        while(curr != nullptr){
            curr->printScopeTable(out);
            curr = curr->getParentScopeTable();
        }

    }

};
