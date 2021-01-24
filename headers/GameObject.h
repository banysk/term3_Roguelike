#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <algorithm>

class Wall;
class Floor;
class Knight;
class Princess;
class Zombie;
class Dragon;
class Aid;
class Mana;
class FireBall;

enum collide_result {
    CAN_MOVE, // for characters
    PICK_AID, // for knight
    PICK_MANA, // for knight
    ATTACK, // for characters
    DESTROYED, // for fireballs
    WIN_GAME, // for knight
    NO_ACTION // for static objects
};

class GameObject {
public:
    char get_char();
    const int get_x() const;
    const int get_y() const;
    void set_x(int x_);
    void set_y(int y_);
    bool is_at(int x, int y);

    virtual collide_result collide(Wall*) = 0;
    virtual collide_result collide(Floor*) = 0;
    virtual collide_result collide(Knight*) = 0;
    virtual collide_result collide(Princess*) = 0;
    virtual collide_result collide(Zombie*) = 0;
    virtual collide_result collide(Dragon*) = 0;
    virtual collide_result collide(Aid*) = 0;
    virtual collide_result collide(Mana*) = 0;
    virtual collide_result collide(FireBall*) = 0;

    virtual bool is_alive() = 0;
    virtual void get_damage(int dmg_) = 0;
    virtual int get_damage() = 0;
    virtual int get_points() = 0;
    virtual void add_points(int) = 0;

protected:
    int x;
    int y;
    char object_char;
};
#endif