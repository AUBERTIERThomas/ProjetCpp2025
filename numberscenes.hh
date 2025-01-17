#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include <SFML/Graphics.hpp>

#include "buttons.hh"
#include "numberbuttons.hh"
#include "operationbuttons.hh"
#include "actionbuttons.hh"

#include "scenes.hh"
#include "endscenes.hh"

class NumberScene : public Scene {
	protected:
		size_t butNumber;
		std::vector<int> poss_num;
    	std::vector<int> numbers;
		std::vector<NumberButton> numberButtons;
		const int target = 100 + rand() % 900;
		/*------------------------------------------*/
		std::vector<OperationButton*> operationButtons;
    	ActionButton validateButton{"Valider", 550, 500, 100, 50, globalFont};
    	ActionButton clearButton{"Effacer", 675, 500, 100, 50, globalFont};
    	/*------------------------------------------*/
    	sf::Text targetText;
    	sf::Text resultText;
    	sf::Text attentionText;
    	/*------------------------------------------*/
    	static const std::string _imageName;
    	static sf::Texture bgTexture;
    	sf::Sprite sprite;
    	/*------------------------------------------*/
    	int activeNumberButton;
		int activeOperationButton;
    	/*------------------------------------------*/
    	int currentResult;
    	int score;
    	bool fin;
		
	public:
		NumberScene(size_t num, sf::RenderWindow& win);
		/*------------------------------------------*/
		static sf::Texture loadTextures() {
			sf::Texture t;
			if (!t.loadFromFile(_imageName)) { // l'image doit etre dans le meme répertoire
        		std::cout << "Erreur : image non disponible (" << _imageName << ")" << std::endl;
    		}
    		return t;
		}
		/*------------------------------------------*/
		std::vector<int> generateRandomNumbers(size_t count, size_t min, size_t max);
		/*------------------------------------------*/
		void AddNumberButton(int nb);
		void RemoveNumberButtons(size_t butNum);
		void ResetCptButton();
		/*------------------------------------------*/
		void NumberClickCheck(sf::Vector2f mousePos);
		void OperationClickCheck(sf::Vector2f mousePos);
		void ActionClickCheck(sf::Vector2f mousePos);
		/*------------------------------------------*/
		void OnClick(sf::Event event);
		/*------------------------------------------*/
		void UpdateWindow(sf::RenderWindow& window);
		/*------------------------------------------*/
		bool NumberGame(sf::RenderWindow& window);
};

const std::string NumberScene::_imageName = "Number_BG.png";
sf::Texture NumberScene::bgTexture = loadTextures();

NumberScene::NumberScene(size_t num, sf::RenderWindow& window) {
	butNumber = num;
	poss_num = {1,2,3,4,5,6,7,8,9,10,15,25,50,100};
    numbers = this->generateRandomNumbers(butNumber, 1, 100); // NVALEUR : entre 1 et 14

    for (size_t i = 0; i < butNumber; ++i) numberButtons.emplace_back(numbers[i], 50 + (i%6) * 120, 200 + (i/6)*75, 100, 50, globalFont); // 6 boutons max par rangée
    
    operationButtons.push_back(new AdditionButton(50, 500, 50, 50, globalFont));
    operationButtons.push_back(new SubstractionButton(110, 500, 50, 50, globalFont));
    operationButtons.push_back(new MultiplicationButton(170, 500, 50, 50, globalFont));
    operationButtons.push_back(new DivisionButton(230, 500, 50, 50, globalFont));
    
	sprite.setTexture(bgTexture);
    //sprite.setPosition(std::get<0>(t),std::get<1>(t));
    sprite.scale(8, 8);
	window.draw(sprite);
    
    targetText = sf::Text("Objectif: " + std::to_string(target), globalFont, 24);
    targetText.setPosition(50, 20);
    targetText.setFillColor(sf::Color::White);

    resultText = sf::Text("Resultat: 0", globalFont, 24);
    resultText.setPosition(50, 60);
    resultText.setFillColor(sf::Color::White);
    
    attentionText = sf::Text("Bouton Rouge = inutilisable", globalFont, 15);
    attentionText.setPosition(500, 20);
    attentionText.setStyle(sf::Text::Bold | sf::Text::Italic | sf::Text::Underlined);
    attentionText.setFillColor(sf::Color::Red);
    
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

void NumberScene::RemoveNumberButtons(size_t butNum) {
	numberButtons[0].setGlobalId(butNum);
	while(numberButtons.size() > butNum) numberButtons.erase(numberButtons.end());
}

void NumberScene::ResetCptButton() {
	numberButtons[0].setGlobalId(0);
	operationButtons[0]->setGlobalId(0);
}

void NumberScene::NumberClickCheck(sf::Vector2f mousePos) {
	for (auto& btn : numberButtons) { // auto = NumberButton
        if (btn.isClicked(mousePos)) { // Bouton bleue utilisable qu'une seule fois
                    	
            if (currentResult == -1) { //Premier chiffre du calcul
                currentResult = btn.getValue();
                resultText.setString("Resultat: " + std::to_string(currentResult));
                numberButtons[btn.getId()].setState(1);
            	activeNumberButton = btn.getId();
            	//std::cout << "Step 1" << std::endl;
            	//std::cout << "() " << activeNumberButton << " " << activeOperationButton << std::endl;
            }
            else { //Deuxième chiffre du calcul
                //std::cout << "() " << activeNumberButton << " " << activeOperationButton << std::endl;
                currentResult = operationButtons[activeOperationButton]->compute(&numberButtons[activeNumberButton], &btn);
                //std::cout << "currentResult = " << currentResult << std::endl;
                if (currentResult != -1) {
                    AddNumberButton(currentResult);
                    currentResult = -1;
                    numberButtons[activeNumberButton].setState(2);
                    numberButtons[btn.getId()].setState(2);
                	//std::cout << "Step 2" << std::endl;
                }
            	resultText.setString("Resultat: 0");
            	//std::cout << "{} " << numberButtons[activeNumberButton].getState() << "|" << numberButtons[activeNumberButton].getId() << " " << btn.getState() << "|" << btn.getId() << std::endl;
            }
            break;
        }
	}
}

void NumberScene::OperationClickCheck(sf::Vector2f mousePos) {
	for (auto& btn : operationButtons) { // auto = OperationButton
        if (btn->isClicked(mousePos)) {
            operationButtons[activeOperationButton]->setState(0);
            btn->setState(1);
            activeOperationButton = btn->getId();
            std::cout << "Step 0" << std::endl;
        	break;
    	}
    }
}

void NumberScene::ActionClickCheck(sf::Vector2f mousePos) {
	if (validateButton.isClicked(mousePos)) {
		fin = true; // Valider = fin du jeu
        if (currentResult == -1) score = -1;
    	else score = abs(target-currentResult);
    }

    // Tout réinitialiser
    if (clearButton.isClicked(mousePos)) {
        currentResult = -1;
  		RemoveNumberButtons(butNumber);
        for (auto& btn : numberButtons) btn.setState(0); 
    	resultText.setString("Resultat: 0");
	}
}

void NumberScene::OnClick(sf::Event event) {
	sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

    NumberClickCheck(mousePos);
	
	OperationClickCheck(mousePos);
	
    ActionClickCheck(mousePos);
    //for (auto& btn : numberButtons) std::cout << "[" << btn.getState() << "]";
	//std::cout << std::endl;
}

void NumberScene::UpdateWindow(sf::RenderWindow& window) {
	window.clear(sf::Color(50, 20, 50, 0));

	// Important pour afficher les textes
	window.draw(sprite);
	window.draw(targetText);
	window.draw(resultText);
	window.draw(attentionText);

    // Pour les boutons
	for (auto& btn : numberButtons) btn.draw(window);
	for (auto& btn : operationButtons) btn->draw(window);
	validateButton.draw(window);
	clearButton.draw(window);
	window.display();
}

bool NumberScene::NumberGame(sf::RenderWindow& window) {
	activeNumberButton = 0;
	activeOperationButton = 0;
	operationButtons[activeOperationButton]->setState(1);

	sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) { // Quand on ne fait pas d'actions, cela sort de la boucle
            if (event.type == sf::Event::Closed) { // Quand on ferme la fenêtre
                window.close();
                return 0;
            }

            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) { // Evènement : Clique gauche sur la souris
                OnClick(event);
            }
        }
		
		// ------- Pendant le jeu
		UpdateWindow(window);
		
		// -------- Fin
		if (fin) {
			ResetCptButton();
			if (score == -1) score = 999;
			EndScene es(score, window);
			return es.scoreMenu(window);
		}
	}
	return 0;
}
