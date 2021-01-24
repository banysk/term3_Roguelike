#include "../Headers/Dragon.h"

Dragon::Dragon(int x_, int y_, char object_char_, int hp_, int mana_, int dmg_, int points_) : Character::Character(x_, y_, object_char_, hp_, mana_, dmg_, points_) {}

collide_result Dragon::collide(GameObject* object) {
    return object->collide(this);
}

collide_result Dragon::collide(Wall*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Dragon::collide(Floor*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Dragon::collide(Knight*) {
    return ATTACK; // персонаж атакует
}
collide_result Dragon::collide(Princess*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Dragon::collide(Zombie*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Dragon::collide(Dragon*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Dragon::collide(Aid*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Dragon::collide(Mana*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Dragon::collide(FireBall*) {
    return ATTACK; // шар наносит урон
}

bool Dragon::is_alive() {
    return hp > 0;
}
void Dragon::get_damage(int dmg_) {
    hp -= dmg_;
}
int Dragon::get_damage() {
    return dmg;
}
int Dragon::get_points() {
    return points;
}

void Dragon::add_points(int) {}