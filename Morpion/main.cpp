#include <iostream>
#include <vector>

using namespace std;

class Plateau {
protected:
    vector<vector<char>> plateau;

public:
    Plateau() : plateau(3, vector<char>(3, '-')) {}

    void afficher() const {
        for (const auto& ligne : plateau) {
            for (char symbole : ligne) {
                cout << symbole << " ";
            }
            cout << endl;
        }
    }

    bool estCaseValide(int ligne, int colonne) const {
        return ligne >= 0 && ligne < 3 && colonne >= 0 && colonne < 3 && plateau[ligne][colonne] == '-';
    }

    void jouerCoup(int ligne, int colonne, char symbole) {
        plateau[ligne][colonne] = symbole;
    }

    bool estGagne(char symbole) const {
        for (int i = 0; i < 3; ++i) {
            if (plateau[i][0] == symbole && plateau[i][1] == symbole && plateau[i][2] == symbole)
                return true;
            if (plateau[0][i] == symbole && plateau[1][i] == symbole && plateau[2][i] == symbole)
                return true;
        }

        if (plateau[0][0] == symbole && plateau[1][1] == symbole && plateau[2][2] == symbole)
            return true;
        if (plateau[0][2] == symbole && plateau[1][1] == symbole && plateau[2][0] == symbole)
            return true;

        return false;
    }
};

class JeuMorpion : public Plateau {
private:
    char joueur;

public:
    JeuMorpion() : joueur('X') {}

    void jouer() {
        int ligne, colonne;
        bool fini = false;

        while (!fini) {
            afficher();
            cout << "Joueur " << joueur << ", entrez ligne et colonne (de 1 à 3) : ";
            cin >> ligne >> colonne;

            // Conversion des indices (de 1 à 3) en indices de tableau (de 0 à 2)
            ligne--;
            colonne--;

            // Vérifier si la case est valide et vide
            if (estCaseValide(ligne, colonne)) {
                jouerCoup(ligne, colonne, joueur);

                // Vérifier si le joueur a gagné
                if (estGagne(joueur)) {
                    afficher();
                    cout << "Le joueur " << joueur << " a gagné !" << endl;
                    fini = true;
                } else {
                    // Changer de joueur
                    joueur = (joueur == 'X') ? 'O' : 'X';
                }
            } else {
                cout << "Mouvement invalide, réessayez." << endl;
            }
        }
    }
};

int main() {
    JeuMorpion jeu;
    jeu.jouer();

    return 0;
}
