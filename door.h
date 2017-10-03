#ifndef DOOR_H
#define DOOR_H

#include <string>
#include <iostream> // Might not need this. Remove if you want.
#include "room.h"
using namespace std;


class Door {

private:
    string description;
    string direction;
    Room* destRoom; // We are going to need to know about both rooms to make a connection either side.
    int code; // The code is for the matching keys, maybe a string would be better.

public:
    Door(string description, int code, string direction, Room *destinationRoom);
    string getDescription();
    int checkCode(int keycode);
    void destroyDoor();
    string getDirection();
    Room* getDestinationRoom();
    int getCode();

};

#endif // DOOR_H
