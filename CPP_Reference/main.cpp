#include <iostream>
 
typedef enum{
    VIVANT=0,
    MORT,
} EtatVie;
 
class Personne
{
public:
    Personne(std::string _nom,
    unsigned int _taille,
    unsigned int _age,
    int _atq,
    int _dfs,
    int _hea) :
    nom(_nom), age(_age), taille(_taille),
    atq(_atq), dfs(_dfs), hea(_hea){}
 
    void sePresenter(void)
    {
        std::cout << "Bonjour je suis " << this->nom << ", je mesure " << this->taille
        << "cm et j'ai " << this->age << "an(s)." << std::endl;
        std::cout << "PV : " << this->hea << "/100 (" << ((this->getEtatVie() == VIVANT)?"Vivant":"Mort") << "), DFS : " << this->dfs << "/100, ATQ : " << this->atq << "/100." << std::endl;
    }
 
    EtatVie getEtatVie(void){
        return this->etat_vie;
    }
 
    void defendre(int _atq){
        int vie_perdue = this->dfs - _atq;
 
        if (vie_perdue > 0) vie_perdue = 0;
 
       
        this->dfs -= 10;
        if (this->dfs < 0) this->dfs = 0;
 
        this->hea = this->hea + vie_perdue;
        if (this->hea <= 0){
            this->hea = 0;
            etat_vie = MORT;
        }
    }
 
    /**
     * @brief Attacks a Person given as a reference
     * @param _pers: reference to Person to attack
     * @returns void
    */
    void attaquer(Personne & _pers){
        std::cout << this->nom << " attaque " << _pers.nom << std::endl;
        if (this->etat_vie != MORT) _pers.defendre(this->atq);
    }
 
protected:
    std::string nom;
    EtatVie etat_vie = VIVANT;
    unsigned int age;
    unsigned int taille;
    int atq = 0;
    int dfs = 0;
    int hea = 100;
};
 
class EtreDeLaForce
{
public:
    EtreDeLaForce(std::string _type) : type(_type) {}
 
    virtual void utiliserLaForce(void)
    {
        std::cout << "Je suis un " << this->type <<" et j'utilise la force !" << std::endl;
    }
 
protected:
    std::string type;
};
 
class Jedi : public Personne, public EtreDeLaForce
{
public:
    Jedi(std::string _nom, unsigned int _taille, unsigned int _age, std::string _couleur_sabre) :
    Personne(_nom, _taille, _age, 60, 80, 100), EtreDeLaForce("Jedi"), couleur_sabre(_couleur_sabre)
    {
    }
 
protected:
    std::string couleur_sabre = "bleue";
};
 
class Sith : public Personne, public EtreDeLaForce
{
public:
    Sith(std::string _nom, unsigned int _taille, unsigned int _age, std::string _couleur_sabre) :
    Personne(_nom, _taille, _age, 80, 60, 70), EtreDeLaForce("Sith"), couleur_sabre(_couleur_sabre)
    {
    }
 
    void utiliserLaForce(void) override
    {
        std::cout << "Je suis un " << this->type <<" et j'utilise la force agrougrou !!!!!" << std::endl;
    }
 
protected:
    std::string couleur_sabre = "rouge";
};
 
int main(int argc, char *argv[])
{
    Jedi mathieu("Mathieu", 183, 27, "vert");
    Sith nathan("nathan", 183, 27, "vert");
    Sith sofiane("sofiane", 308, 867, "rouge");
 
    mathieu.sePresenter();
    nathan.sePresenter();
    sofiane.sePresenter();
 
    std::cout << "FIGHT !!!!!!" << std::endl;
 
    while ((mathieu.getEtatVie() != MORT) && (nathan.getEtatVie() != MORT)){
        mathieu.attaquer(nathan);
        mathieu.attaquer(sofiane);
        nathan.attaquer(mathieu);
        sofiane.attaquer(mathieu);
    }
 
    std::cout << "FINISHED" << std::endl;
 
    mathieu.sePresenter();
    nathan.sePresenter();
    sofiane.sePresenter();
 
    return 0;
}