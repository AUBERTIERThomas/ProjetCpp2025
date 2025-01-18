#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "buttons.hh"

class OperationButton : public Button {
	protected:
		int _id; // id du bouton
		static int _cpt_id; // Compteur de l'id de la classe (sert à attribuer un nouvel id dans le constructeur)
		/*------------------------------------------*/
		std::string operation; // Sert de libellé au bouton
	public:
		OperationButton(std::string operation, float x, float y, float width, float height, sf::Font& font) : Button(operation, x, y, width, height, font), operation(operation) {
			_id = _cpt_id;
			_cpt_id++;
	
			/* Rectangle de couleur (si le bouton n'a pas de texture custom) */
			shape.setFillColor(sf::Color::Blue);
			text.setPosition(x+width/2-5,y+12);
		}
		/*------------------------------------------*/
		void draw(sf::RenderWindow& window) {
		    window.draw(shape);
		    window.draw(text);
		}
		/*------------------------------------------*/
		std::string getOperation() const {return operation;}
		int getId() const {return _id;}
		void setGlobalId(int gid) const {_cpt_id = gid;}
		void setState(short a);
		/*------------------------------------------*/
		virtual int compute(NumberButton *a, NumberButton *b) {return 0;}; // Est redéfini pour chaque opération (n'est pas virtuel pure car la liste contenant les boutons opérations doit être déclaré de ce type)
};

int OperationButton::_cpt_id = 0;

void OperationButton::setState(short a) {
	_state = a;
	switch (_state) {
		case 0 : shape.setFillColor(sf::Color::Blue); break; 				// État 0 : NON ACTIVÉ
		case 1 : shape.setFillColor(sf::Color(20, 175, 20, 255)); break;	// État 1 : ACTIVÉ
	}
};

class AdditionButton : public OperationButton {
	public:
		AdditionButton(float x, float y, float width, float height, sf::Font& font) : OperationButton("+", x, y, width, height, font){}
		int compute(NumberButton *a, NumberButton *b) {return a->getValue() + b->getValue();}
};

class SubstractionButton : public OperationButton {
	public:
		SubstractionButton(float x, float y, float width, float height, sf::Font& font) : OperationButton("-", x, y, width, height, font){}
		int compute(NumberButton *a, NumberButton *b) {return a->getValue() - b->getValue();}
};

class MultiplicationButton : public OperationButton {
	public:
		MultiplicationButton(float x, float y, float width, float height, sf::Font& font) : OperationButton("x", x, y, width, height, font){}
		int compute(NumberButton *a, NumberButton *b) {return a->getValue() * b->getValue();}
};

class DivisionButton : public OperationButton {
	public:
		DivisionButton(float x, float y, float width, float height, sf::Font& font) : OperationButton("/", x, y, width, height, font){}
		int compute(NumberButton *a, NumberButton *b) {
			/* Si la division est entière (et b != 0)*/
			if (b->getValue() && !(a->getValue() % b->getValue()))
				return a->getValue() / b->getValue();
			/* Sinon, on ne fait rien et déselectionne les deux boutons */
			a->setState(0);
			b->setState(0);
			return -1; // Valeur symbolique de la division interdite (c'est poétique)
		}
};
