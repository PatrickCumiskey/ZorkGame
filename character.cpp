#include "character.h"
#include "command.h"

Character::Character(string description) {
    this->description = description;
}

void Character::addItem(Item &item) {
    itemsInCharacter.push_back(&item);
}

void Character::addItem(Item *item) {
    itemsInCharacter.push_back(item);
    //    delete item; I know this deletes item, but I'm not sure why it was here
}

int Character::numberOfItems() {
    return itemsInCharacter.size();
}

int Character::isItemInCharacter(string inString)
{
    int sizeItems = (itemsInCharacter.size());

    // Checks if anything is in the room
    if (itemsInCharacter.size() < 1) {
        return -1;
    }
    else if (itemsInCharacter.size() > 0) {
        int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            // compare inString with short description
            int tempFlag = inString.compare( itemsInCharacter[x]->getShortDescription() );
            if (tempFlag == 0) {
                return x;
            }
            x++;
        }
    }
    return -1;
}

Item* Character::getItemAtLocation(int location)
{
    return itemsInCharacter[location];
}

void Character::removeItem(int location)
{
    itemsInCharacter.erase(itemsInCharacter.begin()+location);
}

string Character::longDescription()
{
    string ret = this->description;
    ret += this->listItems();
    return ret;
}

string Character::listItems()
{
    string ret = "Item list:\n";
    for (vector<Item*>::iterator i = itemsInCharacter.begin(); i != itemsInCharacter.end(); i++)
        ret += "\t"+ (*i)->getShortDescription() + "\n";
    return ret;
}

string Character::shortDescription()
{
    return description;
}
