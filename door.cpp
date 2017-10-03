#include "door.h"

Door::Door(string description, int code, string direction, Room* destinationRoom)
{
    this->description = description;
    this->code = code; // For the key
    this->direction = direction;
    this->destRoom = destinationRoom;
}

string Door::getDescription(){
    return this->description;
}

string Door::getDirection(){
    return this->direction;
}

Room* Door::getDestinationRoom(){
    return this->destRoom;
}

void Door::destroyDoor(){
    delete this;
}

int Door::checkCode(int keyCode)
{
    if(code == keyCode)
        return 1;
    return 0;
}

int Door::getCode()
{
    return this->code;
}

//int Door::closeLock()
//{
//    // I doubt we'll be closing a lock, but it might make for a dramatic moment if a Door closed behind someone.
//    return 0;
//}

// We might need a check in place for if there is a door between two rooms or blocking a doorway
// Instead we could have a door in the room and then 'create' the doorway on key use.
