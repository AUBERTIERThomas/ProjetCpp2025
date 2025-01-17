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
		sf::RectangleShape shape;
		sf::Text text;
		/*------------------------------------------*/
		short _state;
	public:
		Button(const std::string& label, float x, float y, float width, float height, sf::Font& font);
		/*------------------------------------------*/
		void draw(sf::RenderWindow& window) {
		    window.draw(shape);
		    window.draw(text);
		}
		/*------------------------------------------*/
		bool isClicked(const sf::Vector2f& mousePos);
		/*------------------------------------------*/
		std::string getLabel() const {return text.getString();}
		sf::Color getShapeColor() const {return shape.getFillColor();}
		short getState() const {return _state;}
		void setState(short a);
};

Button::Button(const std::string& label, float x, float y, float width, float height, sf::Font& font) { // pour font SFML n'autorise pas la copie !
	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(x, y);
	shape.setFillColor(sf::Color::Blue);
	
	int l = label.length();
	
	text.setFont(font); 
	text.setString(label);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	text.setPosition(x+width/2-6*l,y+12); // pour que le texte soit bien à l'intérieur du bouton
		    
	_state = 0;
}

bool Button::isClicked(const sf::Vector2f& mousePos) {
	if (getState())
		return 0;
	if (shape.getGlobalBounds().contains(mousePos)){
		_state = 1;
		std::cout << "huh" << std::endl;
		return 1;
	}
	return 0;
}

void Button::setState(short a) {
	_state = a;
	switch (_state) {
		case 0 : shape.setFillColor(sf::Color::Blue); break;
		case 1 : shape.setFillColor(sf::Color(20, 175, 20, 255)); break;
		case 2 : shape.setFillColor(sf::Color::Red);
	}
};



