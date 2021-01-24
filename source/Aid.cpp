#include "../Headers/Aid.h"

Aid::Aid(int x_, int y_, char object_char_) : Buff::Buff(x_, y_, object_char_) {}

collide_result Aid::collide(Wall*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Aid::collide(Floor*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Aid::collide(Knight*) {
    return PICK_AID; // герой подбирает аптечку
}
collide_result Aid::collide(Princess*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Aid::collide(Zombie*) {
    return NO_ACTION; // ничего не может сделать
}
collide_result Aid::collide(Dragon*) {
    return NO_ACTION; // ничего не может сделать
}
collide_result Aid::collide(Aid*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Aid::collide(Mana*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Aid::collide(FireBall*) {
    return DESTROYED; // шар разрушается об бафф
}

bool Aid::is_alive() {
    return true;
}
void Aid::get_damage(int dmg_) {}

int Aid::get_damage() {
    return 0;
}

int Aid::get_points() {
    return 0;
}

void Aid::add_points(int) {}