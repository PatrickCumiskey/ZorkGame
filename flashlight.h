#ifndef FLASHLIGHT_H
#define FLASHLIGHT_H
#include "item.h"

class Flashlight: public Item
{
private:
    unsigned int usesRemaining = 0;

public:
    Flashlight(string desc, int uses = 6);
    void setUses(int uses);
    int getUses();
    void useLight();
    ~Flashlight();

};

#endif // FLASHLIGHT_H
