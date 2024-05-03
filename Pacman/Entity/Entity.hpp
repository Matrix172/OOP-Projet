#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <iostream>

/**
 * @brief La classe Entity, permet de créer des Getter
 * Move est une fonction virtuelle pure qui sera redéfinie dans les classes filles afin de distinguer les déplacements selon les instances
 * 
*/
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
