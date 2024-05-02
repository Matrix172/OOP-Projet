#include <iostream>
#include <cstdlib>
#include <vector>

class Plateaudejeu {
private:
    static const int size = 20;            // Taille du plateau de jeu
    static const int half_size = size / 2; // Demi-taille du plateau de jeu

public:
    static bool isValidPosition(int x, int y) {
        return (x > -half_size && x < half_size && y > -half_size && y < half_size);
    }
};

class Entity {
protected:
    std::string name;
    int x, y;

public:
    Entity(const std::string& entity_name, int initial_x, int initial_y) : name(entity_name), x(initial_x), y(initial_y) {}

    virtual void move() = 0;

    void showPosition() {
        std::cout << name << " - Position: (" << x << ", " << y << ")" << std::endl;
    }

    int getX() const { return x; }
    int getY() const { return y; }
    std::string getName() const { return name; }
};

class Player : public Entity {
private:
    std::vector<std::vector<char>>& map; // Référence à la carte du jeu

public:
    Player(const std::string& entity_name, int initial_x, int initial_y, std::vector<std::vector<char>>& game_map)
        : Entity(entity_name, initial_x, initial_y), map(game_map) {}

    void move() override {
        char direction;
        std::cout << "Enter direction (q/d/z/s): ";
        std::cin >> direction;

        int new_x = x;
        int new_y = y;

        switch (direction) {
            case 's':
                new_y = y + 1;
                break;
            case 'z':
                new_y = y - 1;
                break;
            case 'q':
                new_x = x - 1;
                break;
            case 'd':
                new_x = x + 1;
                break;
            default:
                std::cout << "Invalid direction! Use q/d/z/s." << std::endl;
                return; // Ne rien faire si la direction est invalide
        }

        // Vérifier si la nouvelle position n'est pas un mur
        if (Plateaudejeu::isValidPosition(new_x, new_y) && map[new_y + map.size() / 2][new_x + map[0].size() / 2] != '#') {
            x = new_x;
            y = new_y;
        } else {
            std::cout << "You cannot move there. It's a wall!" << std::endl;
        }
    }
};

class Ghost : public Entity {
private:
    std::vector<std::vector<char>>& map; // Référence à la carte du jeu

public:
    Ghost(const std::string& entity_name, int initial_x, int initial_y, std::vector<std::vector<char>>& game_map)
     : Entity(entity_name, initial_x, initial_y), map(game_map) {}

    void move() override {
        int direction = rand() % 4;
        int new_x = x;
        int new_y = y;

        switch (direction) {
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
        }

        // Vérifier si la nouvelle position n'est pas un mur
        if (Plateaudejeu::isValidPosition(new_x, new_y) && map[new_y + map.size() / 2][new_x + map[0].size() / 2] != '#') {
            x = new_x;
            y = new_y;
        }
    }
};

class Game {
private:
    Player& player;
    Ghost& ghost;
    Ghost& ghost2;
    Ghost& ghost3;
    std::vector<std::vector<char>>& map; // Carte du jeu
    int score;

public:
    Game(Player& p, Ghost& g, Ghost& g1, Ghost& g2, std::vector<std::vector<char>>& game_map)
        : player(p), ghost(g), ghost2(g1), ghost3(g2), map(game_map), score (0) {}

    void drawBoard() const {
        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[0].size(); ++j) {
                if (j == player.getX() + map[0].size() / 2 && i == player.getY() + map.size() / 2)
                    std::cout << 'P';
                else if (j == ghost.getX() + map[0].size() / 2 && i == ghost.getY() + map.size() / 2)
                    std::cout << 'G';
                else if (j == ghost2.getX() + map[0].size() / 2 && i == ghost2.getY() + map.size() / 2)
                    std::cout << 'G';
                else if (j == ghost3.getX() + map[0].size() / 2 && i == ghost3.getY() + map.size() / 2)
                    std::cout << 'G';
                else
                    std::cout << map[i][j];
                std::cout << " ";
            }
            std::cout << std::endl;
        }
    }

    bool checkCollision(std::string& ghost_name) const {
        if (player.getX() == ghost.getX() && player.getY() == ghost.getY()) {
            ghost_name = ghost.getName();
            return true;
        } else if (player.getX() == ghost2.getX() && player.getY() == ghost2.getY()) {
            ghost_name = ghost2.getName();
            return true;
        } else if (player.getX() == ghost3.getX() && player.getY() == ghost3.getY()) {
            ghost_name = ghost3.getName();
            return true;
        }
        return false;
        
    }

    void addPoints(int amount) {
        score += amount;
        };

    

    void update() {
        std::string ghost_name;
        int player_x = player.getX() + map[0].size() / 2;
        int player_y = player.getY() + map.size() / 2;

        if (map[player_y][player_x] == '.') {
        map[player_y][player_x] = ' '; // Vide la case sur la carte
        addPoints(25); // Incrémente le score
        std::cout << "Score: " << score << std::endl; // Affiche le nouveau score
    }

        // Si Pacman est sur un point, le point disparaît
        if (map[player_y][player_x] == '.') {
            map[player_y][player_x] = ' ';

        }
        // Si Pacman passe sur un gros point, on le transforme en O.
        if (map[player_y][player_x] == 'o') {
            map[player_y][player_x] = 'O';
        }

        player.move();
        ghost.move();
        ghost2.move();
        ghost3.move();

        if (checkCollision(ghost_name)) {
            std::cout << "Game Over! Le fantome " << ghost_name << " t'a attrape !" << std::endl;
            std::cout << "Position du joueur : (" << player.getX() << ", " << player.getY() << ")" << std::endl;
            drawBoard();
            exit(0); // Sortir du jeu
        }

        drawBoard();
    }



};

int main() {
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
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };

    Player player("Pacman", 0, -5, map);
    Ghost ghost("Fantome 1", 0, 1, map);
    Ghost ghost2("Fantome 2", 1, 1, map);
    Ghost ghost3("Fantome 3", -1, 1, map);
    Game game(player, ghost, ghost2, ghost3, map);

    while (true) {
        game.drawBoard();
        game.update();
        std::cout << "\n" << std::endl;
    }

    return 0;
};
