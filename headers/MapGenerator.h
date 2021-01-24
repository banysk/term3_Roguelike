#pragma once
#include <vector>
#include <map>

class MapGenerator {
public:
    /*
    constructor
    */
    MapGenerator(int dimensions, int max_tunnels, int max_length);
    /*
    generate_map
    */
    void generate_map(std::map<std::string, std::string>& args);
    /*
    generate whole map
    */
    void save_pattern(std::string path = "");
    /*
    only for testing, don't use it
    */
    void draw_pattern();

    void place_object(int amount, char ch, int k1, int k2);
private:
    /*
    since the map consists of tunnel and wall cells, we could describe it as zeros and ones in a two-dimensional array
    */
    std::vector<std::vector<char>> map;
    /*
    width and height of the map
    */
    int dimensions;
    /*
    max number of tunnels possible
    */
    int max_tunnels;
    /*
    max length each tunnel can have
    */
    int max_length;
    /*
    generate vector
    */
    void init();
    /*
    generate walls and floor
    */
    void generate_location(int seed);
    /*
    place knight to upper left corner
    */
    void place_knight();
    /*
    place princess to lower right corner
    */
    void place_princess();
};