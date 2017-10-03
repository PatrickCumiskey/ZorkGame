#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
#include <iostream>
using namespace std;

class Item {
protected:
    string description;
    string longDescriptio;

public:
    Item (string description);
    string getShortDescription();
    string getLongDescription();
    virtual int getCode(){return 0;}
    virtual void setCode(int){}
    virtual int getUses(){return 0;}
    virtual void setUses(int){}
    virtual void useLight(){}
};

#endif /*ITEM_H_*/
