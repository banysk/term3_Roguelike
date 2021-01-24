#ifndef MAP_H
#define MAP_H

#include <vector>
#include <map>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <random>
#include <curses.h>
#include "../headers/Wall.h"
#include "../headers/Floor.h"
#include "../headers/Knight.h"
#include "../headers/Princess.h"
#include "../headers/Zombie.h"
#include "../headers/Dragon.h"
#include "../headers/Aid.h"
#include "../headers/Mana.h"
#include "../headers/FireBall.h"

enum GameStatus {
    VICTORY,
    LOSE,
    PLAY
};

class Map {
public:
    Map() = default;
    /*
    constructor
    */
    Map(int dimensions, int vision, bool fog);
    /*
    init map
    */
    void init_vectors();
    /*
    load map pattern from file
    */
    void load_map_pattern(std::map<std::string, std::string>& args, std::string path = "");
    /*
    fuctions for drawind
    */
    void draw(GameObject*);
    void render();
    void fog_of_war();
    bool is_in_circle(int x, int y);
    void mob_die(GameObject* mob);
    void move_object(int x_from, int y_from, int x_to, int y_to);
    bool move_knight(int x_, int y_);
    void move_monsters();

    GameStatus status();

    struct Pair {
        int y;
        int x;
        Pair& operator=(const Pair &a) {
            y = a.y;
            x = a.x;
            return *this;
        }
    };

    Pair bfs_monster(GameObject* monster);


    void show_info();
    void print_center(int row, std::string message);

    void try_cast_fireball(int x, int y);
    void cast_fireball(GameObject* dragon);
    void move_fireballs();

    void collide_fireball(GameObject*);

private:
    GameStatus game_status;
    bool fog;
    int vision;
    int dimensions;
    Knight* knight;
    std::vector<std::vector<GameObject*>> location;
    std::vector<FireBall*> fireballs;
    std::vector<Zombie*> zombies;
    std::vector<Dragon*> dragons;
    char wall_char;
    char floor_char;
    char knight_char;
    char princess_char;
    char zombie_char;
    char dragon_char;
    char aid_char;
    char mana_char;
    char fireball_char;
    int fireball_dmg;
};
#endif