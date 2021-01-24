#ifndef KNIGHT_H
#define KNIGHT_H

#include "Character.h"

class Knight : public Character {
public:
    Knight(int x_, int y_, char object_char_, int hp_, int mana_, int dmg_, int points_, int hp_rs, int mana_rs_, int fireball_cost_);

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

    void restore_hp();
    void restore_mana();
    bool cast_fireball();

    int get_points() override;
    void add_points(int) override;


private:
    int hp_rs;
    int mana_rs;
    int fireball_cost;
};
#endif