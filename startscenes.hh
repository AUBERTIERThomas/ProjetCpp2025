#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "buttons.hh"
#include "actionbuttons.hh"

#include "scenes.hh"
#include "numberscenes.hh"

class StartScene : public Scene {
	protected:
		static const std::string _imageName;
		static sf::Texture bgTexture;
		sf::Sprite sprite;
		/*------------------------------------------*/
		std::vector<ActionButton> modeButtons;
	public:
		StartScene(sf::RenderWindow& window);
		/*------------------------------------------*/
		static sf::Texture loadTextures() {
			sf::Texture t;
			if (!t.loadFromFile(_imageName)) { // l'image doit etre dans le meme répertoire
        		std::cout << "Erreur : image non disponible (" << _imageName << ")" << std::endl;
    		}
    		return t;
		}
		/*------------------------------------------*/
		int OnClick(sf::Event event); // Lorsqu'un des boutons est utilisé
		/*------------------------------------------*/
		void UpdateWindow(sf::RenderWindow& window); // Refresh l'écran toutes les frames
		/*------------------------------------------*/
		bool MainMenu(sf::RenderWindow& window);
		
		
};

const std::string StartScene::_imageName = "MainMenu_BG.png";
sf::Texture StartScene::bgTexture = loadTextures();

StartScene::StartScene(sf::RenderWindow& window) {
	window.clear(sf::Color(50, 20, 50, 0));
	
	sprite.setTexture(bgTexture);
    sprite.scale(4,4);
	window.draw(sprite);
	
	modeButtons = {
		ActionButton{"8 (Zen)", 70, 450, 150, 50, globalFont, 1, 40},
		ActionButton{"7 (Facile)", 240, 450, 150, 50, globalFont, 1, 35},
		ActionButton{"6 (Normal)", 410, 450, 150, 50, globalFont, 1, 28},
		ActionButton{"5 (Expert)", 580, 450, 150, 50, globalFont, 1, 30}
	};
	
	for (auto& btn : modeButtons) btn.draw(window);
	
	window.display();
}

int StartScene::OnClick(sf::Event event) {
	sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
	
	for (size_t i = 0; i < modeButtons.size(); i++) {
		if (modeButtons[i].isClicked(mousePos)) {
            return i+1;
    	}
	}
	return 0;
}
/*
void NumberScene::UpdateWindow(sf::RenderWindow& window) {
	window.clear(sf::Color(50, 20, 50, 0));

	
	window.draw(sprite);
	window.draw(targetText);
	window.draw(resultText);
	window.draw(attentionText);

    
	for (auto& btn : numberButtons) btn.draw(window);
	for (auto& btn : operationButtons) btn->draw(window);
	validateButton.draw(window);
	clearButton.draw(window);
	window.display();
}
*/
bool StartScene::MainMenu(sf::RenderWindow& window) {

	sf::Event event;
	while(window.isOpen())
		while(window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        		size_t id = OnClick(event); // On regarde si un bouton a été appuyé (et lequel)
        		if (id) { // Si l'un des bouton est appuyé, on charge une partie avec les paramètres choisis
        			bool replay = true;
        			while (replay) { // Tant que le joueur veut rejouer avec les mêmes paramètres
        				NumberScene ns(9-id, window);
        				replay = ns.NumberGame(window);
        			}
        			return true; // Retour au menu
        		}
    		}
    	}
    // On attend que le bonton soit pressé ou que la fenêtre soit fermée	
	return false;
}
