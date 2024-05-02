#ifndef PLATEAUDEJEU_HPP
#define PLATEAUDEJEU_HPP

#include <vector>

class Plateaudejeu
{
private:
    static const int size = 20;            // Taille du plateau de jeu
    static const int half_size = size / 2; // Demi-taille du plateau de jeu

public:
    static bool isValidPosition(int x, int y);
    static bool isWall(const std::vector<std::vector<char>> &map, int x, int y);
};

#endif // PLATEAUDEJEU_HPP
