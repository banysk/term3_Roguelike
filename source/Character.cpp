#include "../headers/Character.h"

Character::Character(int x_, int y_, char object_char_, int hp_, int mana_, int dmg_, int points_) :
    hp(hp_), mana(mana_), dmg(dmg_), points(points_), max_hp(hp_), max_mana(mana_) {
    x = x_;
    y = y_;
    object_char = object_char_;
}
int Character::get_hp() {
    return hp;
}
int Character::get_max_hp() {
    return max_hp;
}
int Character::get_mana() {
    return mana;
}
int Character::get_max_mana() {
    return max_mana;
}