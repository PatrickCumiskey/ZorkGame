#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "item.h"

#include <string>
#include <vector>
using namespace std;
using std::vector;


class Character {
private:
    string description;
    vector<Item*> itemsInCharacter;

public:
    Character(string description);
    void addItem(Item &Item);
    void addItem(Item *Item);
    Item* getItemAtLocation(int location);
    void removeItem(int location);
    int isItemInCharacter(string inString);
    string longDescription();
    string shortDescription();
    int numberOfItems();
    string listItems();

};

#endif /*CHARACTER_H_*/
