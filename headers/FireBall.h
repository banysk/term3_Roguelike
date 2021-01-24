#ifndef FIREBALL_H
#define FIREBALL_H

#include "GameObject.h"

class FireBall : public GameObject {
public:
    FireBall(int x_, int y_, char object_char_, int dir_x_, int dir_y_);

    collide_result collide(GameObject*);
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

    void fly();
    int get_next_x();
    int get_next_y();

    int get_points() override;
    void add_points(int) override;

private:
    int dir_x;
    int dir_y;
};
#endif