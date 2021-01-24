#include "../Headers/Floor.h"

Floor::Floor(int x_, int y_, char object_char_) : Environment::Environment(x_, y_, object_char_) {};

collide_result Floor::collide(Wall*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Floor::collide(Floor*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Floor::collide(Knight*) {
    return CAN_MOVE; // персонаж может ходить
}
collide_result Floor::collide(Princess*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Floor::collide(Zombie*) {
    return CAN_MOVE; // зомби может ходить
}
collide_result Floor::collide(Dragon*) {
    return CAN_MOVE; // дракон может ходить
}
collide_result Floor::collide(Aid*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Floor::collide(Mana*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Floor::collide(FireBall*) {
    return CAN_MOVE; // шар может летать
}

bool Floor::is_alive() {
    return true;
}
void Floor::get_damage(int dmg_) {}
int Floor::get_damage() {
    return 0;
}
int Floor::get_points() {
    return 0;
}

void Floor::add_points(int) {}