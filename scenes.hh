#pragma once
#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include "boutons.hh"

/*
class GameWindow {
	public:
		GameWindow(int h, int w, std::string title);
		sf::RenderWindow window;
};

GameWindow::GameWindow(int h, int w, std::string title) {
	window = sf::RenderWindow(sf::VideoMode(h, w), title);
    window.setFramerateLimit(60);
}
*/

class NumberScene {
	protected:
		//sf::RenderWindow window;
	
		size_t butNumber;
		std::vector<int> poss_num;
    	std::vector<int> numbers;
		std::vector<NumberButton> numberButtons;
		const int target = 100 + rand() % 900;
		
		std::vector<OperationButton> operationButtons;
    	ActionButton validateButton{"Valider", 550, 500, 100, 50, globalFont};
    	ActionButton clearButton{"Effacer", 675, 500, 100, 50, globalFont};
    	
    	sf::Font globalFont;
    	sf::Text targetText;
    	sf::Text resultText;
    	sf::Text attentionText;
    	sf::Text scoreText;
    	
    	sf::Texture texture1;
    	sf::Texture texture2;
    	
    	std::string op;
    	int currentResult;
    	int score;
    	bool fin;
		
	public:
		NumberScene(size_t num, sf::RenderWindow& win);
		std::vector<int> generateRandomNumbers(size_t count, size_t min, size_t max);
		void AddNumberButton(int nb);
		bool NumberGame(sf::RenderWindow& window);
};

NumberScene::NumberScene(size_t num, sf::RenderWindow& window) {
	butNumber = num;
	
    if (!globalFont.loadFromFile("arial.ttf")) {
        std::cout << "Erreur 0" << std::endl;
        //return -1;
    }
	
	poss_num = {1,2,3,4,5,6,7,8,9,10,15,25,50,100};
    numbers = this->generateRandomNumbers(butNumber, 1, 100); // NVALEUR : entre 1 et 14

    for (size_t i = 0; i < butNumber; ++i) {
    	// 6 boutons max par rangée
        numberButtons.emplace_back(numbers[i], 50 + (i%6) * 120, 200 + (i/6)*75, 100, 50, globalFont); // en gros équivalent à push_back en construisant directement une instance de NumberButton (plus simple pour les disposer)
    }
    
    operationButtons = {
        	OperationButton("+", 50, 500, 50, 50, globalFont),
        	OperationButton("-", 110, 500, 50, 50, globalFont),
        	OperationButton("*", 170, 500, 50, 50, globalFont),
        	OperationButton("/", 230, 500, 50, 50, globalFont),
    	};
    //validateButton("Valider", 600, 500, 100, 50, globalFont);
    //clearButton("Effacer", 700, 500, 100, 50, globalFont);
    
    // On peut ajouter d'autres textes
    targetText = sf::Text("Objectif: " + std::to_string(target), globalFont, 24);
    targetText.setPosition(50, 20);
    targetText.setFillColor(sf::Color::Black);

    resultText = sf::Text("Resultat: 0", globalFont, 24);
    resultText.setPosition(50, 60);
    resultText.setFillColor(sf::Color::Black);
    
    attentionText = sf::Text("Bouton Rouge = inutilisable", globalFont, 15);
    attentionText.setPosition(500, 20);
    attentionText.setStyle(sf::Text::Bold | sf::Text::Italic | sf::Text::Underlined);
    attentionText.setFillColor(sf::Color::Red);
    
    scoreText = sf::Text("Score : -1", globalFont, 40);
	scoreText.setPosition(250, 50); // Centrer
	scoreText.setFillColor(sf::Color::Black);
	
    if (!texture1.loadFromFile("incroyable.png")) { // l'image doit etre dans le meme répertoire
        std::cout << "Erreur 1" << std::endl;
        //return -1;
    }
    if (!texture2.loadFromFile("tables_multi.png")) { // l'image doit etre dans le meme répertoire
        std::cout << "Erreur 2" << std::endl;
        //return -1;
    }
    
    op = "+";
    currentResult = -1;
    fin = false;
}

std::vector<int> NumberScene::generateRandomNumbers(size_t count, size_t min, size_t max) { 
    int i;
    while (numbers.size() < count) {
        i = rand()%poss_num.size();
		numbers.push_back(poss_num[i]);
		poss_num.erase(poss_num.begin() + i);
    }
    return numbers;
}

void NumberScene::AddNumberButton(int nb) {
	size_t len = numberButtons.size();
	numberButtons.emplace_back(nb, 50 + (len%6) * 120, 200 + (len/6)*75, 100, 50, globalFont);
}

bool NumberScene::NumberGame(sf::RenderWindow& window) {
	NumberButton* activeNumberButton = &numberButtons[0];
	OperationButton* activeOperationButton = &operationButtons[0];
	(*activeOperationButton).new_shape_color(sf::Color::Green);

	sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) { // Quand on ne fait pas d'actions, cela sort de la boucle
            if (event.type == sf::Event::Closed) { // Quand on ferme la fenêtre
                window.close();
                return 0;
            }

            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) { // Evènement : Clique gauche sur la souris
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                for (auto& btn : numberButtons) { // auto = NumberButton
                    if (btn.isClicked(mousePos) && btn.isActive) { // Bouton bleue utilisable qu'une seule fois
                    	//btn.new_shape_color(sf::Color::Red);
                    	
                        if (currentResult == -1) { //Premier chiffre du calcul
                        	currentResult = btn.getValue();
                            resultText.setString("Resultat: " + std::to_string(currentResult));
                            btn.new_shape_color(sf::Color::Green);
                            activeNumberButton = &btn;
                        }
                        else { //Deuxième chiffre du calcul
                        	int b = btn.getValue();
                        	std::cout << currentResult << " et " << b  << std::endl;
                        	if (op == "+") currentResult += b;
							if (op == "-") currentResult -= b;
                            if (op == "*") currentResult *= b;
                            if (op == "/" && b != 0 && currentResult % b == 0) currentResult /= b;
                            else {
                            	(*activeNumberButton).new_shape_color(sf::Color::Blue);
                            }
                            AddNumberButton(currentResult);
                            currentResult = -1;
                            resultText.setString("Resultat: 0");
                            (*activeNumberButton).new_shape_color(sf::Color::Red);
                            btn.new_shape_color(sf::Color::Red);
                        }
                        break;
                    }
                }

                for (auto& btn : operationButtons) { // auto = OperationButton
                    if (btn.isClicked(mousePos)) {
                        op = btn.getOperation();
                        (*activeOperationButton).new_shape_color(sf::Color::Blue);
                        btn.new_shape_color(sf::Color::Green);
                        activeOperationButton = &btn;
                        break;
                    }
                }

                if (validateButton.isClicked(mousePos)) {
                	fin = true; // Valider = fin du jeu
                	score = abs(target-currentResult);
                }

                // Tout réinitialiser
                if (clearButton.isClicked(mousePos)) {
                    currentResult = -1;
                    op = "";
                    while(numberButtons.size() > butNumber) numberButtons.erase(numberButtons.end());
                    for (auto& btn : numberButtons) {
                    	btn.new_shape_color(sf::Color::Blue); 
                    }
                    resultText.setString("Resultat: 0");
                }
            }
        }
		
		// ------- Pendant le jeu
		
		window.clear(sf::Color::White);

		    // Important pour afficher les textes
		window.draw(targetText);
		window.draw(resultText);
		window.draw(attentionText);

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
		
		// -------- Fin
		if (fin) {
			sf::Sprite sprite;
			if (!score){
				window.clear(sf::Color::Green);
				sprite.setTexture(texture1);
    			sprite.setPosition(250, 100);
				window.draw(sprite);
			}
			else if (score <= 10) {
				window.clear(sf::Color::Yellow);
			}
			else if (score <= 50) {
				window.clear(sf::Color(255, 165, 0, 0)); // Orange (j'ai trouvé sur un site) : R(Red), G(Green), B(Blue), A(alpha) = transparence
				// https://www.webfx.com/web-design/color-picker/color-chart/ si tu veux regarder d'autres couleurs
			}
			else{
				window.clear(sf::Color::Red);
				sprite.setTexture(texture2);
    			sprite.setPosition(200, 100);
    			sprite.scale(0.5f, 0.5f);
				window.draw(sprite);
			}
			
			if (score == -1) window.clear(sf::Color::White);
			scoreText.setString("SCORE : " + std::to_string(score));
			window.draw(scoreText);
				    
			ActionButton replayButton{"Rejouer", 350, 540, 100, 50, globalFont}; //Bouton pour relancer une partie
			replayButton.draw(window);
				    
			window.display();
			while(!replayButton.isClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
				//std::cout << "hehehaha" << std::endl;
				if (window.pollEvent(event) && (event.type == sf::Event::Closed)) {
                	window.close();
                	return 0;
            	}
			}; //On attend que le bonton soit pressé ou que la fenêtre soit fermée
				
			return 1;
		}
	}
	return 0;
}






