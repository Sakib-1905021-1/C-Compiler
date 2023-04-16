#include<bits/stdc++.h>
using namespace std;

class TreeNode{
private:   
    string parseMessage;
    int space = 0;
public:
    vector<TreeNode*> nodeList;
    TreeNode(){
        
    }
    TreeNode(string parseMessage){
        this->parseMessage = parseMessage;
    }

    void setParseMessage(string parseMessage){
        this->parseMessage = parseMessage;
    }

    string getParseMessage(){
        return this->parseMessage;
    }

    void setSpace(int space){
        this->space = space;
    }

    int getSpace(){
        return this->space;
    }
};