#include "../headers/Map.h"

Map::Map(int dimensions, int vision, bool fog) : dimensions(dimensions), vision(vision), fog(fog) {
    game_status = PLAY;
}

void Map::init_vectors() {
    for (auto row : location)
        for (auto object : row)
            delete object;
    location.clear();
    for (auto ball : fireballs)
        delete ball;
    fireballs.clear();
    for (int i = 0; i < dimensions; i++)
        location.push_back(std::vector<GameObject*>(dimensions, nullptr));
}

void Map::load_map_pattern(std::map<std::string, std::string>& args, std::string path) {
    std::fstream map_in;
    char object;
    int c = 0;
    dragon_char = args["DRAGON_CHAR"][0];
    fireball_dmg = std::stoi(args["FIREBALL_DAMAGE"]);
    wall_char = args["WALL_CHAR"][0];
    floor_char = args["FLOOR_CHAR"][0];
    fireball_char = args["FIREBALL_CHAR"][0];
    knight_char = args["KNIGHT_CHAR"][0];
    princess_char = args["PRINCESS_CHAR"][0];
    zombie_char = args["ZOMBIE_CHAR"][0];
    aid_char = args["AID_CHAR"][0];
    mana_char = args["MANA_CHAR"][0];
    map_in.open(path + "map.txt");
    for (int row = 0; row < dimensions; row++) {
        for (int col = 0; col < dimensions; col++) {
            map_in >> object;
            switch (object)
            {
            // environment
            case '#':
                location[row][col] = new Wall(col, row, wall_char);
                break;
            // ^
            case 'x':
                location[row][col] = new Floor(col, row, floor_char);
                break;
            // npcs
            case 'K':
                knight = new Knight(col, row, knight_char,
                    std::stoi(args["KNIGHT_HP"]), std::stoi(args["KNIGHT_MANA"]),
                    std::stoi(args["KNIGHT_DMG"]), std::stoi(args["KNIGHT_POINTS"]),
                    std::stoi(args["AID_POWER"]), std::stoi(args["MANA_POWER"]), std::stoi(args["FIREBALL_COST"]));
                location[row][col] = knight;
                break;
            // ^
            case 'P':
                location[row][col] = new Princess(col, row, princess_char,
                    std::stoi(args["PRINCESS_HP"]), std::stoi(args["PRINCESS_MANA"]),
                    std::stoi(args["PRINCESS_DMG"]), std::stoi(args["PRINCESS_POINTS"]));
                break;
            // ^
            case 'Z':
                zombies.push_back(new Zombie(col, row, zombie_char,
                    std::stoi(args["ZOMBIE_HP"]), std::stoi(args["ZOMBIE_MANA"]),
                    std::stoi(args["ZOMBIE_DMG"]), std::stoi(args["ZOMBIE_POINTS"])));
                location[row][col] = zombies[zombies.size() - 1];
                break;
            // ^
            case 'D':
                dragons.push_back(new Dragon(col, row, 'D',
                    std::stoi(args["DRAGON_HP"]), std::stoi(args["DRAGON_MANA"]),
                    std::stoi(args["DRAGON_DMG"]), std::stoi(args["DRAGON_POINTS"])));
                location[row][col] = dragons[dragons.size() - 1];
                break;
            // buffs
            case 'A':
                location[row][col] = new Aid(col, row, aid_char);
                break;
            // ^
            case 'M':
                location[row][col] = new Mana(col, row, mana_char);
                break;
            // default
            default:
                location[row][col] = new Floor(col, row, floor_char);
                break;
            }
        }
    }
}

GameStatus Map::status() {
    if (!knight->is_alive())
        game_status = LOSE;
    return game_status;
}

void Map::draw(GameObject* object) {
    char ch = object->get_char();
    if (ch == wall_char) color_set(1, NULL);
    if (ch == floor_char) color_set(2, NULL);
    if (ch == knight_char) color_set(3, NULL);
    if (ch == princess_char) color_set(4, NULL);
    if (ch == zombie_char) color_set(5, NULL);
    if (ch == dragon_char) color_set(6, NULL);
    if (ch == aid_char) color_set(7, NULL);
    if (ch == mana_char) color_set(8, NULL);
    if (ch == fireball_char) color_set(9, NULL);
    mvprintw(object->get_y() + 1, object->get_x() + 1, (std::string(1, object->get_char())).c_str());
}

void Map::render() {
    clear();
    color_set(0, NULL);
    box(stdscr, 0, 0);
    // location
    for (auto row : location) {
        for (auto object : row) {
            draw(object);
        }
    }
    // fireballs
    for (auto ball : fireballs)
        draw(ball);
    // fog of war
    if (fog)
        fog_of_war();
    // refresh
    show_info();
    refresh();
}

bool Map::is_in_circle(int x, int y) {
    int d = sqrt(pow(knight->get_x() - x, 2) + pow(knight->get_y() - y, 2));
    return d <= vision;
}

void Map::fog_of_war() {
    color_set(2, NULL);
    for (int row = 0; row < dimensions; row++) {
        for (int col = 0; col < dimensions; col++) {
            if (!is_in_circle(col, row)) {
                mvprintw(row + 1, col + 1, " ");
            }
        }
    }
}

void Map::mob_die(GameObject* mob) {
    int x = mob->get_x();
    int y = mob->get_y();
    bool died = false;
    if (!died) {
        for (int i = 0; i < zombies.size(); i++) {
            if (zombies[i]->get_x() == x && zombies[i]->get_y() == y) {
                knight->add_points(zombies[i]->get_points());
                zombies.erase(zombies.begin() + i);
                delete location[y][x];
                location[y][x] = new Floor(x, y, floor_char);
                died = true;
                break;
            }
        }
    }
    if (!died) {
        for (int i = 0; i < dragons.size(); i++) {
            if (dragons[i]->get_x() == x && dragons[i]->get_y() == y) {
                knight->add_points(dragons[i]->get_points());
                dragons.erase(dragons.begin() + i);
                delete location[y][x];
                location[y][x] = new Floor(x, y, floor_char);
                died = true;
                break;
            }
        }
    }
    if (!died) {
        for (int i = 0; i < fireballs.size(); i++) {
            if (fireballs[i]->get_x() == x && fireballs[i]->get_y() == y) {
                fireballs.erase(fireballs.begin() + i);
                died = true;
                break;
            }
        }
    }
}

void Map::move_object(int x_from, int y_from, int x_to, int y_to) {
    delete location[y_to][x_to];
    location[y_to][x_to] = location[y_from][x_from];
    location[y_from][x_from] = new Floor(x_from, y_from, floor_char);
    location[y_to][x_to]->set_x(x_to);
    location[y_to][x_to]->set_y(y_to);
}

// KNIGHT
bool Map::move_knight(int x_, int y_) {
    int target_x = knight->get_x() + x_;
    int target_y = knight->get_y() + y_;
    GameObject* target = location[target_y][target_x];
    collide_result result = knight->collide(target);
    switch (result)
    {
    case CAN_MOVE: // обычное перемещение
        move_object(knight->get_x(), knight->get_y(), target_x, target_y);
        break;

    case PICK_AID: // подобрал аптеку
        move_object(knight->get_x(), knight->get_y(), target_x, target_y);
        knight->restore_hp();
        break;

    case PICK_MANA: // подобрал ману
        move_object(knight->get_x(), knight->get_y(), target_x, target_y);
        knight->restore_mana();
        break;

    case DESTROYED: // ударился об шар
        move_object(knight->get_x(), knight->get_y(), target_x, target_y);
        knight->get_damage(fireball_dmg);
        break;

    case ATTACK: // атаковал монстра
        target->get_damage(knight->get_damage());
        if (!target->is_alive()) {
            mob_die(target);
            move_object(knight->get_x(), knight->get_y(), target_x, target_y);
        }
        break;

    case WIN_GAME: // спас принцессу
        move_object(knight->get_x(), knight->get_y(), target_x, target_y);
        game_status = VICTORY;
        break;
    default:
        break;
    }
    return false;
}

void Map::print_center(int row, std::string message) {
    mvprintw(row, (dimensions + 1) + 25 - message.size() / 2, message.c_str());
}

void Map::show_info() {
    color_set(0, NULL);
    print_center(1, "INFO");
    color_set(11, NULL);
    print_center(3, "POINTS:" + std::to_string(knight->get_points()));
    color_set(6, NULL);
    print_center(5, "HP:" + std::to_string(knight->get_hp()) + "/" + std::to_string(knight->get_max_hp()));
    color_set(10, NULL);
    print_center(7, "MANA:" + std::to_string(knight->get_mana()) + "/" + std::to_string(knight->get_max_mana()));
    color_set(0, NULL);
    print_center(9, "DAMAGE:" + std::to_string(knight->get_damage()));
    print_center(11, "FIREBALL DAMAGE:" + std::to_string(fireball_dmg));
    print_center(13, std::string(30, '='));
    print_center(15, "'W' - UP");
    print_center(17, "'A' - LEFT");
    print_center(19, "'S' - DOWN");
    print_center(21, "'D' - RIGHT");
    print_center(23, std::string(30, '='));
    print_center(25, "Tap arrow to cast fireball:)");
    print_center(27, "Fireballs on the map:" + std::to_string(fireballs.size()));
    print_center(29, "X:" + std::to_string(knight->get_x()) + " Y:" + std::to_string(knight->get_y()));

}

void Map::try_cast_fireball(int x, int y) {
    int pos_x = knight->get_x();
    int pos_y = knight->get_y();
    if (knight->cast_fireball()) {
        fireballs.push_back(new FireBall(pos_x, pos_y, fireball_char, x, y));
    }
}

void Map::cast_fireball(GameObject* dragon) {
    int dx[4] = { 0, 1, 0, -1 };
    int dy[4] = { 1, 0, -1, 0 };
    std::random_device rd;
    int c = rd() % 4;
    fireballs.push_back(new FireBall(dragon->get_x(), dragon->get_y(), fireball_char, dx[c], dy[c]));
}

//

Map::Pair Map::bfs_monster(GameObject* monster) {
    Pair direction;
    Pair start;
    start.x = knight->get_x();
    start.y = knight->get_y();

    int dx[4] = { 0, 1, 0, -1 };
    int dy[4] = { 1, 0, -1, 0 };
    std::vector<std::vector<int>> distance;
    std::vector<std::vector<short>> visited;

    int v;
    for (int row = 0; row < dimensions; row++) {
        distance.push_back(std::vector<int>(dimensions, dimensions * dimensions));
        visited.push_back(std::vector<short>(dimensions, 0));
        for (int col = 0; col < dimensions; col++) {
            if (location[row][col]->get_char() == wall_char ||
                location[row][col]->get_char() == aid_char ||
                location[row][col]->get_char() == mana_char ||
                location[row][col]->get_char() == dragon_char ||
                location[row][col]->get_char() == zombie_char) {
                visited[row][col] = 1;
            }
        }
    }
    std::queue<Pair> q;
    distance[start.y][start.x] = 0;
    visited[start.y][start.x] = 1;
    q.push(start);
    while (!q.empty()) {
        Pair v = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            if (!visited[v.y + dy[i]][v.x + dx[i]]) {
                distance[v.y + dy[i]][v.x + dx[i]] = distance[v.y][v.x] + 1;
                visited[v.y + dy[i]][v.x + dx[i]] = 1;
                q.push({ v.y + dy[i], v.x + dx[i] });
            }
        }
    }

    int dist = dimensions * dimensions;
    int monster_x = monster->get_x();
    int monster_y = monster->get_y();
    int x_ = 0;
    int y_ = 0;

    for (int i = 0; i < 4; i++) {
        if (distance[monster_y + dy[i]][monster_x + dx[i]] < dist) {
            dist = distance[monster_y + dy[i]][monster_x + dx[i]];
            x_ = monster_x + dx[i];
            y_ = monster_y + dy[i];
        }
    }

     direction.x = x_;
     direction.y = y_;

    return direction;
}
//
void Map::move_monsters() {
    std::random_device rd;
    // зомби ходит с шансом 60 процентов
    for (auto zombie : zombies) {
        if (rd() % 10 < 6) {
            Pair point = bfs_monster(zombie);
            GameObject* target = location[point.y][point.x];
            collide_result result = zombie->collide(target);
            switch (result)
            {
            case CAN_MOVE: // ходит
                move_object(zombie->get_x(), zombie->get_y(), point.x, point.y);
                break;
            case ATTACK: // атакует в ближнем бою
                knight->get_damage(zombie->get_damage());
            case DESTROYED: // наткнулся на шар, тот разбился
                zombie->get_damage(fireball_dmg);
                mob_die(target);
            default:
                break;
            }
        }
    }
    // ходит и стреляет в направлении игрока
    for (auto dragon : dragons) {
        if (rd() % 10 < 4) {
            Pair point = bfs_monster(dragon);
            GameObject* target = location[point.y][point.x];
            collide_result result = dragon->collide(target);
            switch (result)
            {
            case CAN_MOVE: // ходит
                move_object(dragon->get_x(), dragon->get_y(), point.x, point.y);
                if (rd() % 10 < 4)
                    cast_fireball(dragon);
                break;
            case ATTACK: // атакует в ближнем бою
                knight->get_damage(dragon->get_damage());
            case DESTROYED: // наткнулся на шар, тот разбился
                dragon->get_damage(fireball_dmg);
                mob_die(target);
            default:
                break;
            }
        }
    }
}

void Map::move_fireballs() {
    for (int i = fireballs.size() - 1; i > -1; i--) {
        int target_x = fireballs[i]->get_next_x();
        int target_y = fireballs[i]->get_next_y();
        GameObject* target = location[target_y][target_x];
        collide_result result = fireballs[i]->collide(target);
        switch (result)
        {
        // шары могут пролетать сквозь друг друга
        case CAN_MOVE: // шар летит
            fireballs[i]->fly();
            break;
        case DESTROYED: // шар разбился об стену / ящик / принцессу
            delete fireballs[i];
            fireballs.erase(fireballs.begin() + i);
            break;
        case ATTACK: // шар нанёс урон и разбился
            delete fireballs[i];
            fireballs.erase(fireballs.begin() + i);
            target->get_damage(fireball_dmg);
            if (!target->is_alive()) {
                mob_die(target);
            }
            break;
        }
    }
}
