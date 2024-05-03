#include <iostream>
#include <cstdlib>
#include <vector>
#include <conio.h>
#include <chrono>
#include <thread>

#include "Plateaudejeu/Plateaudejeu.hpp"
#include "Entity/Entity.hpp"

class Player : public Entity
{
private:
    std::vector<std::vector<char>> &map; // Référence à la carte du jeu
    bool active;

public:
    Player(const std::string &entity_name, int initial_x, int initial_y, std::vector<std::vector<char>> &game_map)
        : Entity(entity_name, initial_x, initial_y), active(true), map(game_map) {}

    bool isActive() const { return active; }

    void move() override
    {
        // Vérifier s'il y a une touche en attente
        char direction = _getch(); // Capturer la touche pressée

        int new_x = x;
        int new_y = y;

        switch (direction)
        {
        case 'q':
            new_x = x - 1;
            break;
        case 's':
            new_y = y + 1;
            break;
        case 'z':
            new_y = y - 1;
            break;
        case 'd':
            new_x = x + 1;
            break;
        default:
            std::cout << "Invalid direction! Use q/d/z/s." << std::endl;
            return; // Ne rien faire si la direction est invalide
        }

        // Vérifier si la nouvelle position n'est pas un mur
        if (Plateaudejeu::isValidPosition(new_x, new_y) && !Plateaudejeu::isWall(map, new_x, new_y))
        {
            x = new_x;
            y = new_y;
        }
        else if (Plateaudejeu::isWall(map, new_x, new_y))
        {
            std::cout << "\n--- Impossible d'aller dans cette direction. C'est un mur !!---" << std::endl;
            active = false; // Définir le joueur comme inactif en cas de collision avec un mur
        }

        checkTunnel(new_x, new_y);
    }

    void checkTunnel(int new_x, int new_y)
    {
        // Vérifier si Pacman prend le tunnel
        if ((new_x == -10) && (new_y == 1))
        {
            x = 9;
        }
        else if ((new_x == 10) && (new_y == 1))
        {
            x = -9;
        }
    }
};

class Ghost : public Entity
{
private:
    std::vector<std::vector<char>> &map; // Référence à la carte du jeu

public:
    Ghost(const std::string &entity_name, int initial_x, int initial_y, std::vector<std::vector<char>> &game_map)
        : Entity(entity_name, initial_x, initial_y), map(game_map) {}

    void move() override
    {
        int direction = rand() % 4;
        int new_x = x;
        int new_y = y;

        switch (direction)
        {
        case 0:
            new_y = y + 1;
            break;
        case 1:
            new_y = y - 1;
            break;
        case 2:
            new_x = x - 1;
            break;
        case 3:
            new_x = x + 1;
            break;
        default : 
            break;
        }

        // Vérifier si la nouvelle position n'est pas un mur
        if (Plateaudejeu::isValidPosition(new_x, new_y) && !Plateaudejeu::isWall(map, new_x, new_y))
        {
            x = new_x;
            y = new_y;
        }
    }
};

class Game
{
private:
    Player &player;
    std::vector<Ghost> &ghosts;          // Changer pour une référence à un vecteur de Ghost
    std::vector<std::vector<char>> &map; // Carte du jeu
    int score;

public:
    Game(Player &p, std::vector<Ghost> &gs, std::vector<std::vector<char>> &game_map) // Modifier le constructeur pour accepter une référence à un vecteur de Ghost
        : player(p), ghosts(gs), map(game_map), score(0)
    {
    }

    void clearScreen() const
    {
        // Efface l'écran et replace le curseur en haut à gauche
        std::cout << "\033[2J\033[1;1H";
    }

    void drawBoard() const
    {
        clearScreen();
        for (int i = 0; i < map.size(); ++i)
        {
            for (int j = 0; j < map[0].size(); ++j)
            {
                if (j == player.getX() + map[0].size() / 2 && i == player.getY() + map.size() / 2)
                    std::cout << 'P';
                else
                {
                    bool is_ghost = false;
                    for (const Ghost &ghost : ghosts)
                    {
                        if (j == ghost.getX() + map[0].size() / 2 && i == ghost.getY() + map.size() / 2)
                        {
                            std::cout << 'G';
                            is_ghost = true;
                            break;
                        }
                    }
                    if (!is_ghost)
                        std::cout << map[i][j];
                }
                std::cout << " ";
            }
            std::cout << std::endl;
        }
    }

    bool checkCollision(std::string &ghost_name) const
    {
        for (const Ghost &ghost : ghosts)
        {
            if (player.getX() == ghost.getX() && player.getY() == ghost.getY())
            {
                ghost_name = ghost.getName();
                return true;
            }
        }
        return false;
    }

    bool isGameWon() const
    {
        for (const auto &row : map)
        {
            for (char cell : row)
            {
                if (cell == '.')
                {
                    return false; // Il reste encore au moins un point sur la carte
                }
            }
        }
        return true; // Tous les points ont été ramassés
    }

    void addPoints(int amount)
    {
        score += amount;
        std::cout << "Score: " << score << std::endl;
    };

    void update()
    {
        std::string ghost_name;
        int player_x = player.getX() + map[0].size() / 2;
        int player_y = player.getY() + map.size() / 2;

        // Si Pacman est sur un point, le point disparaît
        if (map[player_y][player_x] == '.')
        {
            map[player_y][player_x] = ' ';
            addPoints(25);
            // std::cout << "Score: " << score << std::endl;
        }
        // Ou si Pacman passe sur un gros point, on le transforme en O.
        else if (map[player_y][player_x] == 'o')
        {
            map[player_y][player_x] = ' ';
            addPoints(50);
            // std::cout << "Score: " << score << std::endl;
        }

        player.move();

        // Bouger chaque fantôme de la liste
        for (Ghost &ghost : ghosts)
        {
            ghost.move();
        }

        if (checkCollision(ghost_name))
        {
            std::cout << "+========================================================+\n"
                      << std::endl;
            std::cout << "+                       Game Over!                       +" << std::endl;
            std::cout << "+========================================================+" << std::endl;
            std::cout << "Le fantome " << ghost_name << " t'a attrape !" << std::endl;
            std::cout << "Position du joueur : (" << player.getX() << ", " << player.getY() << ")" << std::endl;
            drawBoard();
            exit(0); // Sortir du jeu
        }

        if (isGameWon())
        {
            std::cout << "+========================================================+\n"
                      << std::endl;
            std::cout << "+   Partie gagnee ! Tous les points ont ete ramasses !   +\n"
                      << std::endl;
            std::cout << "+========================================================+" << std::endl;
            exit(0); // Terminer le jeu
        }
    }
};

int main()
{
    std::vector<std::vector<char>> map = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '#', '#', '#', '#', '#', '#', '.', '#', '.', '#', '#', '#', '#', '#', '#', '.', '#'},
        {'#', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '.', '#'},
        {'#', '#', '.', '#', '.', '#', '.', '#', '#', '#', '#', '#', '.', '#', '.', '#', '.', '#', '#'},
        {'#', 'o', '.', '#', '.', '.', '.', '.', '.', ' ', '.', '.', '.', '.', '.', '#', '.', 'o', '#'},
        {'#', '.', '#', '#', '.', '#', '#', '#', '.', '#', '.', '#', '#', '#', '.', '#', '#', '.', '#'},
        {'#', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '#', '#', '#', '.', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', '.', '#', '#', '#', '#'},
        {' ', ' ', ' ', '#', '.', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '.', '#', ' ', ' ', ' ', ' ', ' '},
        {'#', '#', '#', '#', '.', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', '.', '#', '#', '#', '#', '#'},
        {' ', ' ', ' ', ' ', '.', ' ', ' ', '#', '1', '2', '3', '#', ' ', ' ', '.', ' ', ' ', ' ', ' '},
        {'#', '#', '#', '#', '.', '#', ' ', '#', '#', '=', '#', '#', ' ', '#', '.', '#', '#', '#', '#', '#'},
        {' ', ' ', ' ', '#', '.', '#', ' ', ' ', ' ', '0', ' ', ' ', ' ', '#', '.', '#', ' ', ' ', ' ', ' ', ' '},
        {'#', '#', '#', '#', '.', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '.', '#', '#', '#', '#'},
        {'#', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '.', '#'},
        {'#', '.', '#', '#', '.', '#', '.', '#', '#', '#', '#', '#', '.', '#', '.', '#', '#', '.', '#'},
        {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
        {'#', 'o', '#', '#', '.', '#', '#', '#', '.', '#', '.', '#', '#', '#', '.', '#', '#', 'o', '#'},
        {'#', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}};

    // Initialisation des positions des Entités.
    Player player("Pacman", 0, -5, map);
    Ghost ghost("Fantome 1", 0, 3, map);
    Ghost ghost2("Fantome 2", 1, 3, map);
    Ghost ghost3("Fantome 3", -1, 3, map);
    Ghost ghost4("Fantome 4", 0, 3,map);

    // Création d'un vecteur contenant les fantômes
    std::vector<Ghost> ghosts;
    ghosts.push_back(Ghost("Fantome 1", 0, 3, map));
    ghosts.push_back(Ghost("Fantome 2", 1, 3, map));
    ghosts.push_back(Ghost("Fantome 3", -1, 3, map));
    ghosts.push_back(Ghost("Fantome 4", 0, 3,map));

    // Initialiser le jeu avec le joueur, les fantômes et la carte
    Game game(player, ghosts, map);
    // Game game(player, ghost, ghost2, ghost3, map);

    while (true)
    {
        game.drawBoard();
        game.update();
        std::cout << "\n" << std::endl;
        // Attendre un court laps de temps
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Attente de 500 millisecondes
    }
    
    return 0;
    
};
