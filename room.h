#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "item.h"
class Door;
using namespace std;
using std::vector;

class Room {

private:
    string description;
    map<string, Room*> exits;
    string exitString();
    vector <Item*> itemsInRoom; // Can't use point vector due to getting the item info out...
    vector <Door> doorsInRoom;


public:
    int numberOfItems();
    Room(string description);
    void setExits(Room *north, Room *east, Room *south, Room *west);
    void setExit(string location, Room *room);
//    void getExits(); // Temp void, probably return an array
    string shortDescription();
    string longDescription();
    Room* nextRoom(string direction);
    void addItem(Item *inItem);
    void addItem(Item &inItem);
    string displayItem();
    string displayDoor();
    void addDoor(Door *inDoor);
    void addDoor(Door &inDoor);
    int isItemInRoom(string inString);
    Item* getItemAtLocation(int location);
    void removeItem(int location);
    int isDoorInRoom(int keycode);
    Door* getDoorAtLocation(int location);
    void removeDoor(int location);
};

#endif
