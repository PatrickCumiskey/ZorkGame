#include "flashlight.h"

Flashlight::Flashlight(string desc, int uses) : Item( desc )
{
    this->usesRemaining = uses;
}

int Flashlight::getUses()
{
    return this->usesRemaining;
}

void Flashlight::setUses(int uses)
{
    this->usesRemaining = uses;
}

void Flashlight::useLight()
{
    if(usesRemaining > 0) {

        this->usesRemaining--;
        // Perhaps display the information now

    }
}
