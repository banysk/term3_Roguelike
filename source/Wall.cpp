#include "../headers/Wall.h"

Wall::Wall(int x_, int y_, char object_char_) : Environment::Environment(x_, y_, object_char_) {};

collide_result Wall::collide(Wall*) {
    return NO_ACTION; // ������ �� ����������
}
collide_result Wall::collide(Floor*) {
    return NO_ACTION; // ������ �� ����������
}
collide_result Wall::collide(Knight*) { 
    return NO_ACTION; // �������� �� ����� �����
}
collide_result Wall::collide(Princess*) {
    return NO_ACTION; // ������ �� ����������
}
collide_result Wall::collide(Zombie*) {
    return NO_ACTION; // ����� �� ����� ������
}
collide_result Wall::collide(Dragon*) {
    return NO_ACTION; // ������ �� ����� ������
}
collide_result Wall::collide(Aid*) {
    return NO_ACTION; // ������ �� ����������
}
collide_result Wall::collide(Mana*) {
    return NO_ACTION; // ������ �� ����������
}
collide_result Wall::collide(FireBall*) {
    return DESTROYED; // ��� �����������
}

bool Wall::is_alive() {
    return true;
}
void Wall::get_damage(int dmg_) {}
int Wall::get_damage() {
    return 0;
}
int Wall::get_points() {
    return 0;
}

void Wall::add_points(int) {}