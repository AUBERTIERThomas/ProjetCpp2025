#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <string.h>

// g++ -Wall test_fenetre.cc -o test_fenetre -lsfml-graphics -lsfml-window -lsfml-system

int main() {
	srand((unsigned int)time(0));
	int valeur = rand()%1000; // entre 0 et 999
	std::string valeur_str = std::to_string(valeur);
	std::cout << "Ton objectif : " << valeur_str << std::endl;
	/*
	for  (int i = 0; i < 10; i++){
        int valeur = rand();
       	std:: cout << "valeur rand " << valeur << std::endl;
	}
	*/
	
    // fenêtre (à voir pour les accents ca marche pas pour moi)
    sf::RenderWindow window(sf::VideoMode(800, 600), "Fenetre avec Boutons");

    // bouton
    sf::RectangleShape button1(sf::Vector2f(100, 50)); // (x,y)
    button1.setPosition(200, 275); 
    button1.setFillColor(sf::Color::Blue);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) { // télécharge arial sur internet si t'as pas et met dans le meme répertoire
        std::cerr << "Coup dur\n";
        return -1;
    }
    sf::Text button1Text(valeur_str, font, 20); // police = 20
    button1Text.setFillColor(sf::Color::White);
    //button1Text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    button1Text.setPosition(220, 285);
    
    // -----------------------------------------------------------
    
    sf::RectangleShape button2(sf::Vector2f(100, 50)); // (x,y)
    button2.setPosition(400, 275); 
    button2.setFillColor(sf::Color::Blue);
	
	/*
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) { // télécharge arial sur internet si t'as pas et met dans le meme répertoire
        std::cerr << "Coup dur\n";
        return -1;
    }
    */
    
    sf::Text button2Text("quoi", font, 20); // police = 20
    button2Text.setFillColor(sf::Color::White);
    //button2Text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    button2Text.setPosition(420, 285);
	
	int addition = 0;
	
	// Mes idées :
	/*
	- Drapeau pour chaque bouton : 1 fois cliquée sur le bouton on peut plus recliquer dessus
	- Changer la couleur du bouton une fois cliquée ?
	- Compteur pour savoir quand tous les boutons ont été utilisés -> window.close()
	*/
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
            	std::cout << "Voici ton score bien mérité : " << addition << std::endl;
            	if (abs(valeur-addition) < 50) std::cout << "Tu as 143 de QI." << std::endl;
                window.close();
            }

            // Cliquer sur le bouton
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Probleme NP-Complet Clique 
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (button1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    	addition += 10;
                        std::cout << "cc\n"; // ca apparait dans le terminal
                    }
                    if (button2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
						addition += 100;
                        std::cout << "feur\n"; // ca apparait dans le terminal
                    }
                }
            }
        }
        if (abs(valeur-addition) < 100) window.clear(sf::Color::Red);
        else window.clear(sf::Color::White);
        window.draw(button1);
        window.draw(button1Text);
        window.draw(button2);
        window.draw(button2Text);
        window.display();
    }
    return 0;
}

