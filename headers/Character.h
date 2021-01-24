#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"

class Character : public GameObject {
public:
    Character(int x_, int y_, char object_char_, int hp_, int mana_, int dmg_, int points_);

    int get_hp();
    int get_max_hp();
    int get_mana();
    int get_max_mana();

protected:
    int hp;
    int max_hp;
    int mana;
    int max_mana;
    int dmg;
    int points;
};
#endif