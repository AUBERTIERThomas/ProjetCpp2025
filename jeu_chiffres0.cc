#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "boutons.hh"
#include "scenes.hh"

// g++ -Wall jeu_chiffres0.cc -o jeu_chiffres0 -lsfml-graphics -lsfml-window -lsfml-system

#define NVALEUR 6

// Les axes d'amélioration
/*
- Les classes, j'ai mis que l'essentiel, et à voir comment on peut mettre plusieurs niveaux d'hiérarchie (j'ai juste crée des classes dérivées mais elles ont pas d'intéret pour l'instant)
- J'avoue je sais pas trop quoi penser pour les fonctions virtuelles
- Relancer une nouvelle partie ? 
- le système de parenthèses et d'ordre de priorité, j'ai pas du tout pensé à ca au début 
*/

int main() {
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Jeu de chiffres");
    window.setFramerateLimit(60);
	
    // Boucle principale
    
    // on essaye de regénérer une nouvelle partie ?, le score exact à la fin, nouvelle interface (très dur ca)
    // Version où l'ordre de priorité n'existe pas, ca veut dire que ca fonctionne par parenthèses 
    // ex : 3,-,4,*,5 <=> (3-4)*5, j'avoue j'avais pas prévu ce cas de figure
    
    bool replay = true;
    
    while (replay) {
    	srand((unsigned int)time(0));
    	NumberScene ns(NVALEUR, window);
    	//std::cout << "test" << std::endl;
        replay = ns.NumberGame(window);
    }

    return 0;
}

