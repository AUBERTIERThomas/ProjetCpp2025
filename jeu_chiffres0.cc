#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "boutons.hh"

// g++ -Wall jeu_chiffres0.cc -o jeu_chiffres0 -lsfml-graphics -lsfml-window -lsfml-system

#define NVALEUR 8

// Les axes d'amélioration
/*
- Les classes, j'ai mis que l'essentiel, et à voir comment on peut mettre plusieurs niveaux d'hiérarchie (j'ai juste crée des classes dérivées mais elles ont pas d'intéret pour l'instant)
- J'avoue je sais pas trop quoi penser pour les fonctions virtuelles
- Relancer une nouvelle partie ? 
- le système de parenthèses et d'ordre de priorité, j'ai pas du tout pensé à ca au début 
*/

std::vector<int> generateRandomNumbers(size_t count, size_t min, size_t max) { 
    std::vector<int> poss_num = {1,2,3,4,5,6,7,8,9,10,15,25,50,100};
    std::vector<int> numbers;
    int i;
    while (numbers.size() < count) {
        i = rand()%poss_num.size();
		numbers.push_back(poss_num[i]);
		poss_num.erase(poss_num.begin() + i);
    }
    return numbers;
}

int main() {
	srand((unsigned int)time(0));
    sf::Font globalFont;
    if (!globalFont.loadFromFile("arial.ttf")) {
        std::cout << "Erreur 0" << std::endl;
        return -1;
    }
    sf::RenderWindow window(sf::VideoMode(800, 600), "Jeu de chiffres");
    window.setFramerateLimit(60);

    // Objectif aléatoire entre 100 et 999
    int target = 100 + rand() % 900;

    std::vector<int> numbers = generateRandomNumbers(NVALEUR, 1, 100); // NVALEUR : entre 1 et 14

    std::vector<NumberButton> numberButtons;
    for (size_t i = 0; i < numbers.size(); ++i) {
    	// 6 boutons max par rangée
        numberButtons.emplace_back(numbers[i], 50 + (i%6) * 120, 200 + (i/6)*100, 100, 50, globalFont); // en gros équivalent à push_back en construisant directement une instance de NumberButton (plus simple pour les disposer)
    }

    std::vector<OperationButton> operationButtons = {
        OperationButton("+", 50, 500, 50, 50, globalFont),
        OperationButton("-", 110, 500, 50, 50, globalFont),
        OperationButton("*", 170, 500, 50, 50, globalFont),
        OperationButton("/", 230, 500, 50, 50, globalFont),
    };
    ActionButton validateButton("Valider", 600, 500, 100, 50, globalFont);
    ActionButton clearButton("Effacer", 700, 500, 100, 50, globalFont);

    int b;
    int premier_tour = 1;
    std::string op;
    int currentResult = 0;
    int score = -1;
    int fin = 0;

    // On peut ajouter d'autres textes
    sf::Text targetText("Objectif: " + std::to_string(target), globalFont, 24);
    targetText.setPosition(50, 20);
    targetText.setFillColor(sf::Color::Black);

    sf::Text resultText("Resultat: 0", globalFont, 24);
    resultText.setPosition(50, 60);
    resultText.setFillColor(sf::Color::Black);
    
    sf::Text Attention("Bouton Rouge = inutilisable", globalFont, 15);
    Attention.setPosition(500, 20);
    Attention.setStyle(sf::Text::Bold | sf::Text::Italic | sf::Text::Underlined);
    Attention.setFillColor(sf::Color::Red);
    
    sf::Text ScoreText("Score : -1", globalFont, 40);
	ScoreText.setPosition(250, 100); // Centrer
	ScoreText.setFillColor(sf::Color::Black);
	
	sf::Texture texture1;
    if (!texture1.loadFromFile("incroyable.png")) { // l'image doit etre dans le meme répertoire
        std::cout << "Erreur 1" << std::endl;
        return -1;
    }
    sf::Sprite sprite1;
    sprite1.setTexture(texture1);
    sprite1.setPosition(250, 150);
    
	sf::Texture texture2;
    if (!texture2.loadFromFile("tables_multi.png")) { // l'image doit etre dans le meme répertoire
        std::cout << "Erreur 2" << std::endl;
        return -1;
    }
    sf::Sprite sprite2;
    sprite2.setTexture(texture2);
    sprite2.setPosition(200, 150);
    sprite2.scale(0.5f, 0.5f);
	
    // Boucle principale
    
    // on essaye de regénérer une nouvelle partie ?, le score exact à la fin, nouvelle interface (très dur ca)
    // Version où l'ordre de priorité n'existe pas, ca veut dire que ca fonctionne par parenthèses 
    // ex : 3,-,4,*,5 <=> (3-4)*5, j'avoue j'avais pas prévu ce cas de figure
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) { // Quand on ne fait pas d'actions, cela sort de la boucle
            if (event.type == sf::Event::Closed) { // Quand on ferme la fenêtre
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) { // Evènement : Clique gauche sur la souris
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                for (auto& btn : numberButtons) { // auto = NumberButton
                    if (btn.isClicked(mousePos) && btn.getShapeColor() == sf::Color::Blue) { // Bouton bleue utilisable qu'une seule fois
                    	btn.new_shape_color(sf::Color::Red); 
                    	if (premier_tour){
                    		premier_tour = 0; 
                    		currentResult = btn.getValue();
                    	}
                        else{
                        	// Note : si on appuie plusieures fois sur un numéro, ca va écraser b à chaque fois, et l'opération correspond au dernier bouton opération cliqué
                        	// A voir comment on pourrait faire mieux mais bon 
                        	b = btn.getValue();
                        	if (op == "+") currentResult += b;
                            if (op == "-") currentResult -= b;
                            if (op == "*") currentResult *= b;
                            if (op == "/" && b != 0 && currentResult % b == 0) currentResult /= b; 
                            score = abs(target-currentResult);
                            resultText.setString("Resultat: " + std::to_string(currentResult));
                        }
                        //std::cout << "Nombre : " << btn.getValue() << std::endl;
                        break;
                    }
                }

                for (auto& btn : operationButtons) { // auto = OperationButton
                    if (btn.isClicked(mousePos)) {
                        op = btn.getOperation();
                        //std::cout << "Operation : " << btn.getOperation() << std::endl;
                        break;
                    }
                }

                if (validateButton.isClicked(mousePos)) fin = 1; // Valider = fin du jeu

                // Tout réinitialiser
                if (clearButton.isClicked(mousePos)) {
                    score = -1;
                    premier_tour = 1;
                    currentResult = 0;
                    b = 0;
                    op = "";
                    for (auto& btn : numberButtons) {
                    	btn.new_shape_color(sf::Color::Blue); 
                    }
                    resultText.setString("Resultat: 0");
                }
            }
        }
		
		// ------- Pendant le jeu
		if (fin == 0){
		    window.clear(sf::Color::White);

		    // Important pour afficher les textes
		    window.draw(targetText);
		    window.draw(resultText);
		    window.draw(Attention);

		    // Pour les boutons
		    for (auto& btn : numberButtons) {
		        btn.draw(window);
		    }
		    for (auto& btn : operationButtons) {
		        btn.draw(window);
		    }
		    validateButton.draw(window);
		    clearButton.draw(window);
		    window.display();
    	}
        
        // -------- Fin
        else{
		    if (score >= 0 && score <= 10){
		    	window.clear(sf::Color::Green);
		    	window.draw(sprite1);
		    }
		    if (score > 10 && score <= 25) window.clear(sf::Color::Yellow);
		    if (score > 25 && score <= 100) window.clear(sf::Color(255, 165, 0, 0)); // Orange (j'ai trouvé sur un site) : R(Red), G(Green), B(Blue), A(alpha) = transparence
		    // https://www.webfx.com/web-design/color-picker/color-chart/ si tu veux regarder d'autres couleurs
		    if (score > 100){
		    	window.clear(sf::Color::Red);
		    	window.draw(sprite2);
		    }
		    if (score == -1) window.clear(sf::Color::White);
		    ScoreText.setString("SCORE : " + std::to_string(score));
		    window.draw(ScoreText);
		    
		    window.display();
        }
    }

    return 0;
}

