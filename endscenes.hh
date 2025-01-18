#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include <SFML/Graphics.hpp>

#include "buttons.hh"
#include "actionbuttons.hh"

#include "scenes.hh"

class EndScene : public Scene {
	protected:
		int imageId;
		std::string _imageName;
		static const std::vector<std::string> imageNames;
		static const std::map<std::string,std::tuple<int,int,float>> imageData;// Utilisation d'une map pour associer une image avec ses données
		/*------------------------------------------*/
		sf::Text scoreText;
		sf::Texture texture;
		
	public:
		EndScene(int score, sf::RenderWindow& window);
		/*------------------------------------------*/
		bool scoreMenu(sf::RenderWindow& window);
		/*------------------------------------------*/
		int getGrade() const {return imageId;}
};

const std::vector<std::string> EndScene::imageNames = {"incroyable.png","glad.jpg","I_am_VERY_disappointed.png","tables_multi.png"};
const std::map<std::string,std::tuple<int,int,float>> EndScene::imageData = {{imageNames[0],{250,100,1.0f}}, {imageNames[1],{208,100,2.0f}}, {imageNames[2],{144,0,1.0f}}, {imageNames[3],{200,100,0.5f}}};

EndScene::EndScene(int score, sf::RenderWindow& window) {
	if (!score) {imageId = 0; window.clear(sf::Color::Green);}
	else if (score <= 10) {imageId = 1; window.clear(sf::Color::Yellow);}
	else if (score <= 50) {imageId = 2; window.clear(sf::Color(255, 165, 0, 0));} // Orange : R(Red), G(Green), B(Blue), A(alpha) = transparence
	else {imageId = 3; window.clear(sf::Color::Red);}
	_imageName = imageNames[imageId];
	
	scoreText = sf::Text("SCORE : " + std::to_string(score), globalFont, 40);
	scoreText.setPosition(250, 50); // Centrer
	scoreText.setFillColor(sf::Color::Black);
	window.draw(scoreText);
	
	if (!texture.loadFromFile(_imageName)) { // L'image doit etre dans le meme répertoire
        std::cout << "Erreur : image non disponible (" << imageNames[imageId] << ")" << std::endl;
    }
}

bool EndScene::scoreMenu(sf::RenderWindow& window) {
	sf::Sprite sprite;
	sprite.setTexture(texture);
    auto t = imageData.find(_imageName)->second;
    sprite.setPosition(std::get<0>(t),std::get<1>(t)); // std::get<x>(t) est une méthode pour extraire un élément en position x d'un tuple t
    sprite.scale(std::get<2>(t),std::get<2>(t));
	window.draw(sprite);
	
	ActionButton replayButton{"Rejouer", 250, 540, 100, 50, globalFont, 0, 15}; // Bouton pour relancer directement une partie
	ActionButton menuButton{"Menu", 450, 540, 100, 50, globalFont, 0, 25}; // Bouton pour revenir au menu
	replayButton.draw(window);
	menuButton.draw(window);
				    
	window.display();
	
	sf::Event event;
	while(window.isOpen())
		while(window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        		if (replayButton.isClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) return true;
        		if (menuButton.isClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) return false;
        	}
        }
	
	// On attend que le bonton soit pressé ou que la fenêtre soit fermée	
	return false;
}
