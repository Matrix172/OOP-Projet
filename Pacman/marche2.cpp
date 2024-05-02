#include <iostream>
#include <cstdlib>
#include <vector>

class Plateaudejeu {
private:
    static const int size = 20; // Taille du plateau de jeu
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

public:
    Game(Player& p, Ghost& g, Ghost& g1, Ghost& g2) : player(p), ghost(g), ghost2(g1), ghost3(g2) {}

    void drawBoard() const {
        const std::vector<std::string> map = {
            " ###################",
            " #.................# ",
            " #.######.#.######.# ",
            " #....#...#...#....# ",
            " ##.#.#.#####.#.#.## ",
            " #o.#..... .....#.o# ",
            " #.##.###.#.###.##.# ",
            " #........#........# ",
            " ####.# ##### #.#### ",
            "    #.#       #.#    ",
            "#####.# ##### #.#####",
            "     .  #123#  .     ",
            "#####.# ##=## #.#####",
            "    #.#   0   #.#    ",
            " ####.### # ###.#### ",
            " #....#...#...#....# ",
            " #.##.#.#####.#.##.# ",
            " #.................# ",
            " #o##.###.#.###.##o# ",
            " #........#........# ",
            " ################### "
        };

        for (int i = map.size() - 1; i >= 0; --i) {
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

    void update() {
        std::string ghost_name;
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
    Player player("Pacman", 0, -5);
    Ghost ghost("Fantome 1", 0, 1);
    Ghost ghost2("Fantome 2", 1, 1);
    Ghost ghost3("Fantome 3", -1, 1);
    Game game(player, ghost, ghost2, ghost3);

    while (true) {
        game.drawBoard();
        game.update();
        std::cout << "\n" << std::endl;
    }

    return 0;
}
