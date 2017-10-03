#include "room.h"
#include "command.h"
#include "door.h"
using namespace std;

Room::Room(string description) {
    this->description = description;
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west) {
    if (north != NULL)
        exits["north"] = north;
    if (east != NULL)
        exits["east"] = east;
    if (south != NULL)
        exits["south"] = south;
    if (west != NULL)
        exits["west"] = west;
}

void Room::setExit(string location, Room *room)
{
    // location must be "north", "south", "east" or "west"
    if(location == "north"){
        this->exits["north"] = room;
    }
    if(location == "south"){
        exits["south"] = room;
    }
    if(location == "east"){
        exits["east"] = room;
    }
    if(location == "west"){
        exits["west"] = room;
    }
}


string Room::shortDescription() {
    return description;
}

string Room::longDescription() {
    return "room = " + description + ".\n" + displayItem() + ".\n" + displayDoor()  + exitString();
}

string Room::exitString() {
    string returnString = "\nexits =";
    for (map<string, Room*>::iterator i = exits.begin(); i != exits.end(); i++)
        // Loop through map
        returnString += "  " + i->first;	// access the "first" element of the pair (direction as a string)
    return returnString;
}

Room* Room::nextRoom(string direction) {
    map<string, Room*>::iterator next = exits.find(direction); //returns an iterator for the "pair"

    if (next == exits.end())
        return NULL; // if exits.end() was returned, there's no room in that direction.
    return next->second; // If there is a room, remove the "second" (Room*)
    // part of the "pair" (<string, Room*>) and return it.
}

void Room::addItem(Item *inItem) {
    cout << endl;
    cout << "Just added" + inItem->getLongDescription();
    itemsInRoom.push_back(inItem);
}

void Room::addItem(Item &inItem) {
    itemsInRoom.push_back(&inItem);
}

string Room::displayItem() {
    string tempString = "items in room =";
    int sizeItems = (itemsInRoom.size());
    if (sizeItems < 1) {
        tempString = "no items in room";
    }
    else if (sizeItems > 0) {
        int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            tempString = tempString + " " + itemsInRoom[x]->getShortDescription();
            x++;
        }
    }
    return tempString;
}

string Room::displayDoor() {
    string tempString = "doors in room = ";
    int sizeDoors = (doorsInRoom.size());
    if (sizeDoors < 1) {
        tempString = "no doors in room";
    }
    else if (sizeDoors > 0) {
        int x = (0);
        for (int n = sizeDoors; n > 0; n--) {
            tempString = tempString + doorsInRoom[x].getDescription() + " " ;
            x++;
        }
    }
    return tempString;
}

int Room::numberOfItems() {
    return itemsInRoom.size();
}

Item* Room::getItemAtLocation(int location)
{
    return itemsInRoom[location];
}

void Room::addDoor(Door *inDoor) {
    cout << endl;
    cout << "Just added" + inDoor->getDescription();
    doorsInRoom.push_back(*inDoor);
}

void Room::addDoor(Door &inDoor) {
    doorsInRoom.push_back(inDoor);
}

void Room::removeItem(int location)
{
    itemsInRoom.erase(itemsInRoom.begin()+location);
}

int Room::isItemInRoom(string inString)
{
    int sizeItems = (itemsInRoom.size());

    // Checks if anything is in the room
    if (sizeItems < 1) {
        return -1;
    }
    else if (sizeItems > 0) {
        int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            // compare inString with short description
            int tempFlag = inString.compare( itemsInRoom[x]->getShortDescription());
            if (tempFlag == 0) {
                return x;
            }
            x++;
        }
    }
    return -1;
}

Door* Room::getDoorAtLocation(int location)
{
    return &doorsInRoom[location];
}

void Room::removeDoor(int location)
{
    doorsInRoom.erase(doorsInRoom.begin()+location);
}

int Room::isDoorInRoom(int keycode)
{
    int sizeDoors = (doorsInRoom.size());

    // Checks if anything is in the room
    if (sizeDoors < 1) {
        return -1;
    }
    else if (sizeDoors > 0) {
        int x = (0);
        for (int n = sizeDoors; n > 0; n--) {
            if(doorsInRoom[x].getCode() == keycode) {
                //            if(33 == keycode) {
                return x;
            }
            x++;
        }
    }
    return -1;
}
