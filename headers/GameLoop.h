#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "../Headers/Map.h"
#include "../Headers/MapGenerator.h"
#include <map>
#include <string>
#include <memory>
#include <ctime>

class GameLoop {
public:
    GameLoop();
    void parse_cfg();
    void start_game();
    void init_window();

private:
    std::unique_ptr<std::map<std::string, std::string>> args;
    Map map;
};
#endif