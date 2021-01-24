#pragma once
#include "../Headers/MapGenerator.h"
#include <random>
#include <curses.h>
#include <fstream>
#include <string>

MapGenerator::MapGenerator(int dimensions, int max_tunnels, int max_length) :
    dimensions(dimensions), max_tunnels(max_tunnels), max_length(max_length) {}

void MapGenerator::init() {
    map.clear();
    for (int i = 0; i < dimensions; i++) {
        map.push_back(std::vector<char>(dimensions, '#'));
    }
}

void MapGenerator::generate_location(int seed) {
    std::random_device rd;
    for (int step = 0; step < seed; step++) { // how mush times we call algorithm
        int currentRow = rd() % (dimensions - 2) + 1; // our current row - start at a random spot
        int currentColumn = rd() % (dimensions - 2) + 1; // our current column - start at a random spot
        std::vector<std::pair<int, int>> directions; // array to get a random direction from (left,right,up,down)
        directions.push_back(std::make_pair(-1, 0)); // ^
        directions.push_back(std::make_pair(1, 0)); // ^
        directions.push_back(std::make_pair(0, -1)); // ^
        directions.push_back(std::make_pair(0, 1)); // ^

        std::pair<int, int> lastDirection; // save the last direction we went
        std::pair<int, int> randomDirection; // next turn/direction - holds a value from directions
        while (max_tunnels && dimensions && max_length) { // lets create some tunnels - while maxTunnels, dimentions, and maxLength  is greater than 0.

            // lets get a random direction - until it is a perpendicular to our lastDirection
            // if the last direction = left or right,
            // then our new direction has to be up or down,
            // and vice versa
            do {
                randomDirection = directions[rd() % directions.size()];
            } while ((randomDirection.first == -lastDirection.first && randomDirection.second == -lastDirection.second) ||
                (randomDirection.first == lastDirection.first && randomDirection.second == lastDirection.second));

            int randomLength = rand() % max_length; //length the next tunnel will be (max of maxLength)
            int tunnelLength = 0; //current length of tunnel being created

            // lets loop until our tunnel is long enough or until we hit an edge
            while (tunnelLength < randomLength) {
                //break the loop if it is going out of the map
                if (((currentRow == 1) && (randomDirection.first == -1)) ||
                    ((currentColumn == 1) && (randomDirection.second == -1)) ||
                    ((currentRow == dimensions - 2) && (randomDirection.first == 1)) ||
                    ((currentColumn == dimensions - 2) && (randomDirection.second == 1))) {
                    break;
                }
                else {
                    map[currentRow][currentColumn] = 'x'; //set the value of the index in map to 0 (a tunnel, making it one longer)
                    currentRow += randomDirection.first; //add the value from randomDirection to row and col (-1, 0, or 1) to update our location
                    currentColumn += randomDirection.second;
                    tunnelLength++; //the tunnel is now one longer, so lets increment that variable
                }
            }
            if (tunnelLength) { // update our variables unless our last loop broke before we made any part of a tunnel
                lastDirection = randomDirection; //set lastDirection, so we can remember what way we went
                max_tunnels--; // we created a whole tunnel so lets decrement how many we have left to create
            }
        }
    }
}

void MapGenerator::place_knight() {
    bool placed = false;
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) {
            if (map[i][j] == 'x') {
                map[i][j] = 'K';
                placed = true;
                break;
            }
        }
        if (placed) {
            break;
        }
    }
}

void MapGenerator::place_princess() {
    bool placed = false;
    for (int i = dimensions - 1; i > -1; i--) {
        for (int j = dimensions - 1; j > -1; j--) {
            if (map[i][j] == 'x') {
                map[i][j] = 'P';
                placed = true;
                break;
            }
        }
        if (placed) {
            break;
        }
    }
}

void MapGenerator::place_object(int amount, char ch, int k1, int k2) {
    std::random_device rd;
    for (int i = 0; i < amount; i++) {
        int rand_x = 0;
        int rand_y = 0;
        while (map[rand_y][rand_x] != 'x') {
            rand_x = rd() % dimensions;
            rand_y = rd() % (k1 * dimensions / k2) + ((k2 - k1) * dimensions / k2);
        }
        map[rand_y][rand_x] = ch;
    }
}

void MapGenerator::generate_map(std::map<std::string, std::string>& args) {
    init();
    generate_location(std::stoi(args["SEED"]));
    place_knight();
    place_princess();
    place_object(std::stoi(args["ZOMBIES"]), 'Z', 4, 5);
    place_object(std::stoi(args["DRAGONS"]), 'D', 3, 5);
    place_object(std::stoi(args["AIDS"]), 'A', 1, 1);
    place_object(std::stoi(args["MANA"]), 'M', 1, 1);
}

void MapGenerator::save_pattern(std::string path) {
    std::ofstream map_file;
    map_file.open(path + "map.txt");
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) {
            map_file << map[i][j];
        }
        map_file << '\n';
    }
}

void MapGenerator::draw_pattern() {
    initscr();
    resize_term(dimensions, dimensions + 100);
    refresh();
    curs_set(0);
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) {
            mvprintw(i, 50 + j, std::string(1, map[i][j]).c_str());
        }
    }
    getch();
    endwin();
}