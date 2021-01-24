#include "../Headers/Knight.h"

Knight::Knight(int x_, int y_, char object_char_, int hp_, int mana_, int dmg_, int points_, int hp_rs_, int mana_rs_, int fireball_cost_) :
    Character::Character(x_, y_, object_char_, hp_, mana_, dmg_, points_), hp_rs(hp_rs_), mana_rs(mana_rs_), fireball_cost(fireball_cost_) {}

collide_result Knight::collide(GameObject* object) {
    return object->collide(this);
}
collide_result Knight::collide(Wall*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Knight::collide(Floor*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Knight::collide(Knight*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Knight::collide(Princess*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Knight::collide(Zombie*) {
    return ATTACK; // зомби атакует персонажа
}
collide_result Knight::collide(Dragon*) {
    return ATTACK; // дракон атакует персонажа
}
collide_result Knight::collide(Aid*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Knight::collide(Mana*) {
    return NO_ACTION; // ничего не происходит
}
collide_result Knight::collide(FireBall*) {
    return ATTACK; // шар атакует персонажа
}
bool Knight::is_alive() {
    return hp > 0;
}
void Knight::get_damage(int dmg_) {
    hp -= dmg_;
}
void Knight::restore_hp() {
    hp = std::min(max_hp, hp + hp_rs);
}
void Knight::restore_mana() {
    mana = std::min(max_mana, mana + mana_rs);
}
bool Knight::cast_fireball() {
    if (mana - fireball_cost >= 0) {
        mana -= fireball_cost;
        return true;
    }
    return false;
}
int Knight::get_damage() {
    return dmg;
}
int Knight::get_points() {
    return points;
}

void Knight::add_points(int pts) {
    points += pts;
}