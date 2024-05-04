# PROGRAMMATION OBJET C++ #

Développement d'un jeu basé sur le langage C++.
Ce jeu intéragit avec l'utilisateur par invite de commande.

## Contraintes : ##
1 - Utilisation du langage C++
2 - Utilisation des mécanismes d'héritage
3 - Créer des méthodes virtuelles
4 - Utiliser au mieux la librairie standard
6 - Projet CMake

### PACMAN ###

Ce jeu est un semblant de Pacman se jouant dans le terminal.
Lorsque l'executable est lancé, le joueur controle pacman représenté par la lettre 'P' dans la carte.
Les fantômes se déplacent aléatoirement sur la carte.

Lorsque Pacman rencontre un fantome. GameOver.

La partie se fini lorsque Pacman à réussi à manger toutes les pastilles.

Lorsque Pacman se déplace sur une Pacgomme, représentées par des 'o', il devient alors invincible pendant 20 déplacements et peut donc manger les fantômes.

#### Contrôles ####
Pacman se contrôle avec Z,Q,S,D.
Z : Haut
Q : Gauche
S : Bas
D : Droite

Il est possible de quitter le jeu avec la touche 'E'.
