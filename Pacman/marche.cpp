#include <iostream>
#include <cstdlib>
#include <vector>

class Plateaudejeu {
private:
    static const int size = 25; // Taille du plateau de jeu
    static const int half_size = size / 2; // Demi-taille du plateau de jeu

public:
    static bool isValidPosition(int x, int y) {
        return (x >= -half_size && x <= half_size && y >= -half_size && y <= half_size);
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
public:
    Player(const std::string& entity_name, int initial_x, int initial_y) : Entity(entity_name, initial_x, initial_y) {}

    void move() override {
        char direction;
        std::cout << "Enter direction (q/d/z/s): ";
        std::cin >> direction;

        switch (direction) {
            case 'z':
                if (Plateaudejeu::isValidPosition(x, y + 1))
                    y++;
                break;
            case 's':
                if (Plateaudejeu::isValidPosition(x, y - 1))
                    y--;
                break;
            case 'q':
                if (Plateaudejeu::isValidPosition(x - 1, y))
                    x--;
                break;
            case 'd':
                if (Plateaudejeu::isValidPosition(x + 1, y))
                    x++;
                break;
            default:
                std::cout << "Invalid direction! Use q/d/z/s." << std::endl;
                break;
        }
    }
};

class Ghost : public Entity {
public:
    Ghost(const std::string& entity_name, int initial_x, int initial_y) : Entity(entity_name, initial_x, initial_y) {}

    void move() override {
        int direction = rand() % 4;

        switch (direction) {
            case 0:
                if (Plateaudejeu::isValidPosition(x, y + 1))
                    y++;
                break;
            case 1:
                if (Plateaudejeu::isValidPosition(x, y - 1))
                    y--;
                break;
            case 2:
                if (Plateaudejeu::isValidPosition(x - 1, y))
                    x--;
                break;
            case 3:
                if (Plateaudejeu::isValidPosition(x + 1, y))
                    x++;
                break;
        }
    }
};

class Game {
private:
    Player& player;
    Ghost& ghost;
    Ghost& ghost2;
    Ghost& ghost3;
    Ghost& ghost4;

public:
    Game(Player& p, Ghost& g, Ghost& g1, Ghost& g2, Ghost& g3) : player(p), ghost(g), ghost2(g1), ghost3(g2), ghost4(g3) {}

    void start() {
        // Logique de démarrage du jeu
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
        } else if (player.getX() == ghost4.getX() && player.getY() == ghost4.getY()) {
            ghost_name = ghost4.getName();
            return true;
        }
        return false;
    }

    void drawBoard() const {
    const int size = 17; // Taille du plateau de jeu
    std::vector<std::vector<char>> board(size, std::vector<char>(size, '.')); // Initialisation de la grille avec des points

    // Placement du joueur
    int player_x = player.getX() + size / 2;
    int player_y = player.getY() + size / 2;
    board[player_y][player_x] = 'P';

    // Placement des fantômes
    int ghost_x = ghost.getX() + size / 2;
    int ghost_y = ghost.getY() + size / 2;
    board[ghost_y][ghost_x] = 'G';

    int ghost2_x = ghost2.getX() + size / 2;
    int ghost2_y = ghost2.getY() + size / 2;
    board[ghost2_y][ghost2_x] = 'G';

    int ghost3_x = ghost3.getX() + size / 2;
    int ghost3_y = ghost3.getY() + size / 2;
    board[ghost3_y][ghost3_x] = 'G';

    int ghost4_x = ghost4.getX() + size / 2;
    int ghost4_y = ghost4.getY() + size / 2;
    board[ghost4_y][ghost4_x] = 'G';

    // Affichage du plateau de jeu
    for (int i = size - 1; i >= 0; --i) {
        for (int j = 0; j < size; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

    void update() {
        std::string ghost_name;
        player.move();
        ghost.move();
        ghost2.move();
        ghost3.move();
        ghost4.move();

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
    Player player("Pacman", 0, 0);
    Ghost ghost("Fantome 1", 0, 5);
    Ghost ghost2("Fantome 2", 5, 0);
    Ghost ghost3("Fantome 3", 0, -5);
    Ghost ghost4("Fantome 4", -5, 0);
    Game game(player, ghost, ghost2, ghost3, ghost4);

    while (true) {
        game.update();
        std::cout << "\n" << std::endl;
    }

    return 0;
}
