#include "Entity.hpp"

Entity::Entity(const std::string &entity_name, int initial_x, int initial_y)
    : name(entity_name), x(initial_x), y(initial_y) {}

void Entity::showPosition()
{
    std::cout << name << " - Position: (" << x << ", " << y << ")" << std::endl;
}

int Entity::getX() const
{
    return x;
}

int Entity::getY() const
{
    return y;
}

std::string Entity::getName() const
{
    return name;
}
