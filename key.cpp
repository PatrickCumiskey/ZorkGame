#include "key.h"

Key::Key(string desc, int code) : Item( desc )
{
    this->keycode = code;
}

void Key::setCode(int code)
{
    this->keycode = code;
}

int Key::getCode()
{
    return keycode;
}
