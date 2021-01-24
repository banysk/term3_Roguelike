#ifndef BUFF_H
#define BUFF_H

#include "GameObject.h"

class Buff : public GameObject {
public:
    Buff(int x_, int y_, char object_char_);

private:
    int power;
};
#endif