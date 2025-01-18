#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <SFML/Graphics.hpp>

class Button {
	protected:
		sf::Text text;
		sf::RectangleShape shape;
		/*------------------------------------------*/
		short _state;
	public:
		Button(const std::string& label, float x, float y, float width, float height, sf::Font& font);
		/*------------------------------------------*/
		virtual void draw(sf::RenderWindow& window) = 0; // L'affichage est géré différament selon les classes enfant
		/*------------------------------------------*/
		bool isClicked(const sf::Vector2f& mousePos);
		/*------------------------------------------*/
		std::string getLabel() const {return text.getString();}
		short getState() const {return _state;}
};

Button::Button(const std::string& label, float x, float y, float width, float height, sf::Font& font) { // Pour font SFML n'autorise pas la copie !
	/* Rectangle (forme du bouton) */
	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(x, y);
	shape.setFillColor(sf::Color(255, 255, 255, 0)); // Si le rectangle de couleur est remplacé par une texture, on le rend transparent
	
	/* Libellé du bouton */
	text.setFont(font); 
	text.setString(label);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	
	/* Par défaut, un bouton comment à l'état 0 (non activé) */    
	_state = 0;
}

bool Button::isClicked(const sf::Vector2f& mousePos) {
	if (getState()) // Ne peut être appuyé que si son état est à 0
		return 0;
	if (shape.getGlobalBounds().contains(mousePos)){
		_state = 1; // Le bonton passe à l'état 1 (activé)
		return 1;
	}
	return 0;
}



