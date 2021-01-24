#ifndef FLOOR_H
#define FLOOR_H

#include "../headers/Environment.h"

class Floor : public Environment {
public:
    Floor(int x_, int y_, char object_char_);

    collide_result collide(Wall*) override;
    collide_result collide(Floor*) override;
    collide_result collide(Knight*) override;
    collide_result collide(Princess*) override;
    collide_result collide(Zombie*) override;
    collide_result collide(Dragon*) override;
    collide_result collide(Aid*) override;
    collide_result collide(Mana*) override;
    collide_result collide(FireBall*) override;

    bool is_alive() override;
    void get_damage(int dmg_) override;
    int get_damage() override;

    int get_points() override;
    void add_points(int) override;
};
#endif