#include "../Headers/Princess.h"

Princess::Princess(int x_, int y_, char object_char_, int hp_, int mana_, int dmg_, int points_) : Character::Character(x_, y_, object_char_, hp_, mana_, dmg_, points_) {}

collide_result Princess::collide(Wall*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Princess::collide(Floor*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Princess::collide(Knight*) {
    return WIN_GAME; // персонаж побеждает
}
collide_result Princess::collide(Princess*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Princess::collide(Zombie*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Princess::collide(Dragon*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Princess::collide(Aid*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Princess::collide(Mana*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Princess::collide(FireBall*) {
    return DESTROYED; // шар разбивается
}

bool Princess::is_alive() {
    return hp > 0;
}
void Princess::get_damage(int dmg_) {}
int Princess::get_damage() {
    return 0;
}
int Princess::get_points() {
    return 0;
}

void Princess::add_points(int) {}