#include "../Headers/Zombie.h"

Zombie::Zombie(int x_, int y_, char object_char_, int hp_, int mana_, int dmg_, int points_) : Character::Character(x_, y_, object_char_, hp_, mana_, dmg_, points_) {}

collide_result Zombie::collide(GameObject* object) {
    return object->collide(this);
}

collide_result Zombie::collide(Wall*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Zombie::collide(Floor*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Zombie::collide(Knight*) {
    return ATTACK; // персонаж атакует
}
collide_result Zombie::collide(Princess*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Zombie::collide(Zombie*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Zombie::collide(Dragon*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Zombie::collide(Aid*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Zombie::collide(Mana*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Zombie::collide(FireBall*) {
    return ATTACK; // шар наносит урон
}

bool Zombie::is_alive() {
    return hp > 0;
}
void Zombie::get_damage(int dmg_) {
    hp -= dmg_;
}
int Zombie::get_damage() {
    return dmg;
}
int Zombie::get_points() {
    return points;
}

void Zombie::add_points(int) {}