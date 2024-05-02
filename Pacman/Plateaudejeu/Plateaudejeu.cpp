#include "Plateaudejeu.hpp"

bool Plateaudejeu::isValidPosition(int x, int y)
{
    return (x > -half_size && x < half_size && y > -half_size && y < half_size);
}

bool Plateaudejeu::isWall(const std::vector<std::vector<char>> &map, int x, int y)
{
    return (map[y + map.size() / 2][x + map[0].size() / 2] == '#');
}