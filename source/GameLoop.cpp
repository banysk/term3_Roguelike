#pragma once
#include "../Headers/GameLoop.h"
#include <curses.h>
#include <fstream>
#include <iostream>

#define LEFT 260
#define UP 259
#define RIGHT 261
#define DOWN 258

void GameLoop::parse_cfg() {
    std::string file_line, parameter_name, parameter_argument;
    int equals_sign_position;
    std::ifstream cfg_in("settings.cfg");
    while (cfg_in >> file_line) {
        equals_sign_position = file_line.find('=');
        parameter_name = file_line.substr(0, equals_sign_position);
        parameter_argument = file_line.substr(equals_sign_position + 1, file_line.length() - 1);
        (*args)[parameter_name] = parameter_argument;
    }
    cfg_in.close();
    std::ofstream cfg_out("settings.cfg");
    for (auto parameter_pair : *args) {
        cfg_out << parameter_pair.first << "=" << parameter_pair.second << "\n";
    }
    cfg_out.close();
}

GameLoop::GameLoop() : args(std::unique_ptr<std::map<std::string, std::string>>(new std::map<std::string, std::string>())) {
    // get settings
    parse_cfg();
    // generate map pattern
    MapGenerator map_generator(std::stoi((*args)["DIMENSIONS"]), std::stoi((*args)["MAX_TUNNELS"]), std::stoi((*args)["MAX_LENGTH"]));
    map_generator.generate_map(*args);
    map_generator.save_pattern();
    // create map
    map = Map(std::stoi((*args)["DIMENSIONS"]), std::stoi((*args)["OVERVIEW"]), std::stoi((*args)["FOG"]));
    map.init_vectors();
    map.load_map_pattern(*args);
}

void GameLoop::init_window() {
    int d = std::stoi((*args)["DIMENSIONS"]);
    initscr();
    keypad(stdscr, TRUE);
    resize_term(d + 2, d + 50 + 2);
    noecho();
    curs_set(0);
    nodelay(stdscr, true);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_YELLOW); // WALL
    init_pair(2, COLOR_WHITE, COLOR_BLACK); // FLOOR
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK); // KNIGHT
    init_pair(4, COLOR_CYAN, COLOR_BLACK); // PRINCESS
    init_pair(5, COLOR_GREEN, COLOR_BLACK); // ZOMBIE
    init_pair(6, COLOR_RED, COLOR_BLACK); // DRAGON && HP
    init_pair(7, COLOR_GREEN, COLOR_WHITE); // AID_BUFF
    init_pair(8, COLOR_BLUE, COLOR_WHITE); // MANA_BUFF
    init_pair(9, COLOR_RED, COLOR_BLACK); // FIREBALL
    init_pair(10, COLOR_BLUE, COLOR_BLACK); // MANA
    init_pair(11, COLOR_YELLOW, COLOR_BLACK); // POINTS
}

void GameLoop::start_game() {
    long long fireball_time = clock();
    long long monster_time = fireball_time;
    long long player_time = monster_time;
    bool player_moved = false;
    int ch;
    init_window();
    while (map.status() == PLAY) {
        if (clock() - fireball_time >= std::stoi((*args)["TIK"]) / 3) {
            map.move_fireballs();
            fireball_time = clock();
        }
        if (clock() - monster_time >= 2 * std::stoi((*args)["TIK"])) {
            map.move_monsters();
            monster_time = clock();
        }
        if ((ch = getch(stdscr)) == ERR) {
        }
        else if (clock() - player_time >= std::stoi((*args)["TIK"])) {
            switch (ch) {
            case 'W':
            case 'w':
                player_moved = true;
                map.move_knight(0, -1);
                break;
            case 'S':
            case 's':
                player_moved = true;
                map.move_knight(0, 1);
                break;
            case 'A':
            case 'a':
                player_moved = true;
                map.move_knight(-1, 0);
                break;
            case 'D':
            case 'd':
                player_moved = true;
                map.move_knight(1, 0);
                break;
            case UP:
                player_moved = true;
                map.try_cast_fireball(0, -1);
                break;
            case DOWN:
                player_moved = true;
                map.try_cast_fireball(0, 1);
                break;
            case LEFT:
                player_moved = true;
                map.try_cast_fireball(-1, 0);
                break;
            case RIGHT:
                player_moved = true;
                map.try_cast_fireball(1, 0);
                break;
            default:
                player_moved = false;
                break;
            }
            if (player_moved) {
                player_time = clock();
                player_moved = false;
            }
        }
        map.render();
    }
    map.print_center(31, std::string(30, '='));
    switch (map.status())
    {
    case VICTORY:
        color_set(11, NULL);
        map.print_center(33, "VICTORY!!!");
        break;
    case LOSE:
        color_set(6, NULL);
        map.print_center(33, "LOSE...");
        break;
    }
    nodelay(stdscr, false);
    getch();
    endwin();
}