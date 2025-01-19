#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "buttons.hh"

//#include "numberscenes.hh"
#include "startscenes.hh"

//#define NVALEUR 6 // Permettait de définir le nombre de boutons de nombre dans le jeu

int main() {
	
	/* Ouverture de la fenêtre. Elle peut être mise en plein écran, mais le ratio déformera le rendu.*/
	sf::RenderWindow window(sf::VideoMode(800, 600), "Des chiffres (et pas des lettres)");
    window.setFramerateLimit(60);
    
    /* Tant que le joueur ne ferme pas la fenêtre, on relance une partie une fois que la précédente se termine.*/
    bool replay = true;
    
    srand(time(NULL)); //Réinitialisation de la seed.
    
    while (replay) {
    	StartScene ss(window);
        replay = ss.MainMenu(window);
        //NumberScene ss(NVALEUR,window);
        //replay = ss.NumberGame(window);
    }

    return 0;
}

