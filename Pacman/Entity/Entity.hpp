#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <iostream>

class Entity
{
protected:
    std::string name;
    int x, y;

public:
    Entity(const std::string &entity_name, int initial_x, int initial_y);

    virtual void move() = 0;

    void showPosition();

    int getX() const;
    int getY() const;
    std::string getName() const;
};

#endif // ENTITY_HPP
