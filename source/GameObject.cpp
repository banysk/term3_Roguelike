#include "../headers/GameObject.h"

char GameObject::get_char() {
    return object_char;
}

const int GameObject::get_x() const{
    return x;
}

const int GameObject::get_y() const{
    return y;
}

void GameObject::set_x(int x_) {
    x = x_;
}

void GameObject::set_y(int y_) {
    y = y_;
}

bool GameObject::is_at(int x_, int y_) {
    return (x == x_ && y == y_);
}