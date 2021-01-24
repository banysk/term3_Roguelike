#include "../Headers/FireBall.h"

FireBall::FireBall(int x_, int y_, char object_char_, int dir_x_, int dir_y_) : 
    dir_x(dir_x_), dir_y(dir_y_) {
    x = x_;
    y = y_;
    object_char = object_char_;
}

collide_result FireBall::collide(GameObject* object) {
    return object->collide(this);
}

collide_result FireBall::collide(Wall*) {
    return NO_ACTION; // ничего не происходит
}
collide_result FireBall::collide(Floor*) {
    return NO_ACTION; // ничего не происходит
}
collide_result FireBall::collide(Knight*) {
    return DESTROYED; // игрок получает урон
}
collide_result FireBall::collide(Princess*) {
    return NO_ACTION; // ничего не происходит
}
collide_result FireBall::collide(Zombie*) {
    return DESTROYED; // зомби получает урон
}
collide_result FireBall::collide(Dragon*) {
    return DESTROYED; // дракон получает урон
}
collide_result FireBall::collide(Aid*) {
    return NO_ACTION; // ничего не происходит
}
collide_result FireBall::collide(Mana*) {
    return NO_ACTION; // ничего не происходит
}
collide_result FireBall::collide(FireBall*) {
    return DESTROYED;  // шар разбивается о шар
}
void FireBall::fly() {
    x += dir_x;
    y += dir_y;
}
int FireBall::get_next_x() {
    return x + dir_x;
}
int FireBall::get_next_y() {
    return y + dir_y;
}

bool FireBall::is_alive() {
    return true;
}
void FireBall::get_damage(int dmg_) {}
int FireBall::get_damage() {
    return 0;
}
int FireBall::get_points() {
    return 0;
}

void FireBall::add_points(int) {}