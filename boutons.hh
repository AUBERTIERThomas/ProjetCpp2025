#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

class Button {
	protected:
		sf::RectangleShape shape;
		sf::Text text;

	public:
		Button() {
			shape.setPosition(0, 0);
		}
		Button(const std::string& label, float x, float y, float width, float height, sf::Font& font) { // pour font SFML n'autorise pas la copie !
		    shape.setSize(sf::Vector2f(width, height));
		    shape.setPosition(x, y);
		    shape.setFillColor(sf::Color::Blue);

		    text.setFont(font); 
		    text.setString(label);
		    text.setCharacterSize(20);
		    text.setFillColor(sf::Color::White);
		    text.setPosition(x+20,y+10); // pour que le texte soit bien à l'intérieur du bouton
		}
		// A voir si on ajoute d'autres fonctions, j'ai mis seulement celles dont j'avais besoin
		void draw(sf::RenderWindow& window) {
		    window.draw(shape);
		    window.draw(text);
		}
		void new_shape_color(const sf::Color& color){shape.setFillColor(color);}

		bool isClicked(const sf::Vector2f& mousePos) const {return shape.getGlobalBounds().contains(mousePos);}
		std::string getLabel() const {return text.getString();}
		sf::Color getShapeColor() const {return shape.getFillColor();}
};

class NumberButton : public Button {
	public:
		NumberButton(int value, float x, float y, float width, float height, sf::Font& font) : Button(std::to_string(value), x, y, width, height, font), value(value) {}
		int getValue() const {return value;}
	private:
		int value;
};

class OperationButton : public Button {
	public:
		OperationButton(std::string operation, float x, float y, float width, float height, sf::Font& font) : Button(operation, x, y, width, height, font), operation(operation) {}
		std::string getOperation() const {return operation;}
	private:
		std::string operation;
};

// Je vois pas trop son intéret (surtout pour le bouton valider, il y a probablement rien à faire)
class ActionButton : public Button {
	public:
		ActionButton() : Button() {}
		ActionButton(const std::string& label, float x, float y, float width, float height, sf::Font& font) : Button(label, x, y, width, height, font) {}
};
