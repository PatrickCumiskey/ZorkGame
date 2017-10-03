#ifndef KEY_H
#define KEY_H
#include "item.h"

class Key: public Item
{

private:
    int keycode;

public:

    Key(string desc, int keycode);
    void setCode(int code);
    int getCode();
    ~Key();

};

#endif // KEY_H
