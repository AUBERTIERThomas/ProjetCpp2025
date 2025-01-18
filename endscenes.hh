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
		const std::vector<std::string> imageNames = {"incroyable.png","incroyable.png","incroyable.png","tables_multi.png"};
		const std::map<std::string,std::tuple<int,int>> imageLoc = {{imageNames[0],{250, 100}}, {imageNames[1],{250,100}}, {imageNames[2],{250,100}}, {imageNames[3],{200, 100}}};
		const std::map<std::string,float> imageScale = {{imageNames[0],1.0f}, {imageNames[1],1.0f}, {imageNames[2],1.0f}, {imageNames[3],0.5f}};
		/*------------------------------------------*/
		sf::Text scoreText;
		sf::Texture texture;
		
	public:
		EndScene(int score, sf::RenderWindow& window);
		/*------------------------------------------*/
		bool scoreMenu(sf::RenderWindow& window);
		void displayImage(sf::RenderWindow& window);
		/*------------------------------------------*/
		int getGrade() const {return imageId;}
		
		
};

EndScene::EndScene(int score, sf::RenderWindow& window) {
	if (!score) {imageId = 0; window.clear(sf::Color::Green);}
	else if (score <= 10) {imageId = 1; window.clear(sf::Color::Yellow);}
	else if (score <= 50) {imageId = 2; window.clear(sf::Color(255, 165, 0, 0));} // Orange (j'ai trouvé sur un site) : R(Red), G(Green), B(Blue), A(alpha) = transparence
		// https://www.webfx.com/web-design/color-picker/color-chart/ si tu veux regarder d'autres couleurs
	else {imageId = 3; window.clear(sf::Color::Red);}
	_imageName = imageNames[imageId];
	
	scoreText = sf::Text("SCORE : " + std::to_string(score), globalFont, 40);
	scoreText.setPosition(250, 50); // Centrer
	scoreText.setFillColor(sf::Color::Black);
	window.draw(scoreText);
	
	if (!texture.loadFromFile(_imageName)) { // l'image doit etre dans le meme répertoire
        std::cout << "Erreur : image non disponible (" << imageNames[imageId] << ")" << std::endl;
    }
}

bool EndScene::scoreMenu(sf::RenderWindow& window) {
	sf::Sprite sprite;
	sprite.setTexture(texture);
    auto t = imageLoc.find(_imageName)->second;
    std::cout << "x = " << std::get<0>(t) << " y = " << std::get<1>(t) << std::endl;
    sprite.setPosition(std::get<0>(t),std::get<1>(t));
    float f = imageScale.find(_imageName)->second;
    std::cout << "f = " << f << std::endl;
    sprite.scale(f, f);
	window.draw(sprite);
	
	ActionButton replayButton{"Rejouer", 350, 540, 100, 50, globalFont}; //Bouton pour relancer une partie
	replayButton.draw(window);
				    
	window.display();
	
	sf::Event event;
	while(!replayButton.isClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
		//std::cout << "hehehaha" << std::endl;
		if (window.pollEvent(event) && (event.type == sf::Event::Closed)) {
        	window.close();
			return false;
    	}
	}; //On attend que le bonton soit pressé ou que la fenêtre soit fermée
		
	return true;
}
