#include "../Headers/Mana.h"

Mana::Mana(int x_, int y_, char object_char_) : Buff::Buff(x_, y_, object_char_) {}

collide_result Mana::collide(Wall*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Mana::collide(Floor*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Mana::collide(Knight*) {
    return PICK_MANA; // персонаж подбирает бафф
}
collide_result Mana::collide(Princess*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Mana::collide(Zombie*) {
    return NO_ACTION; // ничего не может сделать
}
collide_result Mana::collide(Dragon*) {
    return NO_ACTION; // ничего не может сделать
}
collide_result Mana::collide(Aid*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Mana::collide(Mana*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Mana::collide(FireBall*) {
    return DESTROYED; // шар разбивается об бафф
}

bool Mana::is_alive() {
    return true;
}
void Mana::get_damage(int dmg_) {}
int Mana::get_damage() {
    return 0;
}
int Mana::get_points() {
    return 0;
}

void Mana::add_points(int) {}