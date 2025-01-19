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
    	ActionButton validateButton{"Valider", 500, 500, 100, 50, globalFont, 0, 20};
    	ActionButton clearButton{"Effacer", 650, 500, 100, 50, globalFont, 0, 17};
    	/*------------------------------------------*/
    	sf::Text targetText;
    	sf::Text resultText;
    	sf::Text attentionText;
    	/*------------------------------------------*/
    	static const std::string _imageName;
    	static sf::Texture bgTexture;
    	sf::Sprite sprite;
    	/*------------------------------------------*/
    	int activeNumberButton;	// Indice du bouton nombre actif (en vert)
		int activeOperationButton; // Indice du bouton opération actif (en vert)
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
		size_t getButNumber() const {return numberButtons.size();}
		/*------------------------------------------*/
		std::vector<int> generateRandomNumbers(size_t count);
		/*------------------------------------------*/
		void AddNumberButton(int nb); // Mise en fin de liste du nouveau bouton.
		void RemoveNumberButtons(size_t butNum); // Retire le dernier bouton jusqu'à ce qu'il en reste butNum
		void ResetCptButton(); // Réinitialise les compteurs des boutons nombres et opérations (ils sont supprimés automatiquement)
		/*------------------------------------------*/
		void NumberClickCheck(sf::Vector2f mousePos);
		void OperationClickCheck(sf::Vector2f mousePos);
		void ActionClickCheck(sf::Vector2f mousePos);
		/*------------------------------------------*/
		void OnClick(sf::Event event); // Lorsqu'un des boutons est utilisé (appelle les méthodes du dessus)
		/*------------------------------------------*/
		void UpdateWindow(sf::RenderWindow& window); // Refresh l'écran toutes les frames
		/*------------------------------------------*/
		bool NumberGame(sf::RenderWindow& window); // METHODE PRINCIPALE, suit le déroulé du jeu
		/*------------------------------------------*/
		friend std::ostream& operator<< (std::ostream& stream, NumberScene& ns);
		NumberButton& operator[] (size_t i) {return numberButtons[i];}
};

const std::string NumberScene::_imageName = "Number_BG.png";
sf::Texture NumberScene::bgTexture = loadTextures();

NumberScene::NumberScene(size_t num, sf::RenderWindow& window) {
	butNumber = num;
	poss_num = {1,2,3,4,5,6,7,8,9,10,15,25,50,100}; //Liste des nombres pouvant tomber
    numbers = this->generateRandomNumbers(butNumber); // butNumber = 5,6,7 ou 8 correspondant au nombre de boutons de nombre choisi dans le menu

    for (size_t i = 0; i < butNumber; ++i) numberButtons.emplace_back(numbers[i], 50 + (i%6) * 120, 200 + (i/6)*75, 100, 50, globalFont); // 6 boutons max par rangée
    
    /* Ajout des boutons d'opérations */
    operationButtons.push_back(new AdditionButton(50, 500, 50, 50, globalFont));
    operationButtons.push_back(new SubstractionButton(110, 500, 50, 50, globalFont));
    operationButtons.push_back(new MultiplicationButton(170, 500, 50, 50, globalFont));
    operationButtons.push_back(new DivisionButton(230, 500, 50, 50, globalFont));
    
    /* Image en fond d'écran */
	sprite.setTexture(bgTexture);
    sprite.scale(8, 8);
	window.draw(sprite);
    
    /* Text de l'objectif de score */
    targetText = sf::Text("Objectif: " + std::to_string(target), globalFont, 24);
    targetText.setPosition(50, 25);
    targetText.setFillColor(sf::Color::White);
	
	/* Text du résultat du joueur. Si aucun bouton n'est sélectionné, vaut 0. */
    resultText = sf::Text("Resultat: 0", globalFont, 24);
    resultText.setPosition(50, 65);
    resultText.setFillColor(sf::Color::White);
    
    /* Text de l'indication */
    attentionText = sf::Text("Bouton Rouge = inutilisable", globalFont, 15);
    attentionText.setPosition(500, 20);
    attentionText.setStyle(sf::Text::Bold | sf::Text::Italic | sf::Text::Underlined);
    attentionText.setFillColor(sf::Color::Red);
    
    currentResult = -1;
    fin = false; // Reste faux tant que le joueur ne valide pas son score.
}

std::ostream& operator<< (std::ostream& stream, NumberScene& ns) {
	stream << "Boutons : ";
	for (size_t i = 0; i < ns.getButNumber(); i++) // Affiche la valeur de tous les boutons numériques de la scène.
		stream << "[" << ns[i].getValue() << "] ";
	return stream;
}

std::vector<int> NumberScene::generateRandomNumbers(size_t count) { 
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
	while(numberButtons.size() > butNum) numberButtons.erase(numberButtons.end()); //
}

void NumberScene::ResetCptButton() {
	numberButtons[0].setGlobalId(0);
	operationButtons[0]->setGlobalId(0);
}

void NumberScene::NumberClickCheck(sf::Vector2f mousePos) {
	for (auto& btn : numberButtons) { // auto = NumberButton
        if (btn.isClicked(mousePos)) { // Bouton bleu utilisable qu'une seule fois
                    	
            if (currentResult == -1) { //Premier chiffre du calcul
                currentResult = btn.getValue();
                resultText.setString("Resultat: " + std::to_string(currentResult));
                numberButtons[btn.getId()].setState(1);
            	activeNumberButton = btn.getId();
            }
            else { //Deuxième chiffre du calcul
                currentResult = operationButtons[activeOperationButton]->compute(&numberButtons[activeNumberButton], &btn);
                if (currentResult != -1) { // currentResult = -1 signifie que le calcul effectué est une division non entière (on reset le tour)
                    AddNumberButton(currentResult);
                    currentResult = -1;
                    numberButtons[activeNumberButton].setState(2);
                    numberButtons[btn.getId()].setState(2);
                }
            	resultText.setString("Resultat: 0");
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
        	break;
    	}
    }
}

void NumberScene::ActionClickCheck(sf::Vector2f mousePos) {
	if (validateButton.isClicked(mousePos)) {
		fin = true; // Valider = fin du jeu
        if (currentResult == -1) score = -1;
    	else score = abs(target-currentResult); // le score correspond à la différence entre l'objectif et la valeur obtenue, l'objectif est d'avoir le score le plus proche de 0
    }

    /* Tout réinitialiser */
    if (clearButton.isClicked(mousePos)) {
        currentResult = -1;
  		RemoveNumberButtons(butNumber);
        for (auto& btn : numberButtons) btn.setState(0); 
    	resultText.setString("Resultat: 0");
	}
}

void NumberScene::OnClick(sf::Event event) {
	sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
	
	/* Recherche quel bouton a été activé (effectue l'action nécessaire dans la fonction dédiée) */
    NumberClickCheck(mousePos);
	
	OperationClickCheck(mousePos);
	
    ActionClickCheck(mousePos);
}

void NumberScene::UpdateWindow(sf::RenderWindow& window) {
	window.clear(sf::Color(50, 20, 50, 0));

	/* Important pour afficher les textes */
	window.draw(sprite);
	window.draw(targetText);
	window.draw(resultText);
	window.draw(attentionText);

    /* Pour les boutons */
	for (auto& btn : numberButtons) btn.draw(window);
	for (auto& btn : operationButtons) btn->draw(window);
	validateButton.draw(window);
	clearButton.draw(window);
	window.display();
}

bool NumberScene::NumberGame(sf::RenderWindow& window) {
	/* Par défaut, l'addition est sélectionnée */
	activeNumberButton = 0;
	activeOperationButton = 0;
	operationButtons[activeOperationButton]->setState(1);

	sf::Event event; // Stocke l'action du joueur (si il y en a une)
    while (window.isOpen()) {
        while (window.pollEvent(event)) { // Quand on ne fait pas d'actions, cela sort de la boucle (rien ne change)
            if (event.type == sf::Event::Closed) window.close(); // Quand on ferme la fenêtre

            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) { // Evènement : Clique gauche sur la souris
                OnClick(event); // Vérifie l'action du joueur
            }
        }
		
		// -- Pendant le jeu --- */
		UpdateWindow(window);
		
		/* -------- Fin -------- */
		if (fin) {
			ResetCptButton();
			if (score == -1) score = 999; // Si aucun bouton n'est sélectionné, le score est fixé à 999 (le pire palier)
			EndScene es(score, window); // Lance l'écran de fin
			return es.scoreMenu(window);
		}
	}
	return false;
}
