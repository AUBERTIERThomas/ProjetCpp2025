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
		int _id;
		static int _cpt_id;
		std::string operation;
	public:
		OperationButton(std::string operation, float x, float y, float width, float height, sf::Font& font) : Button(operation, x, y, width, height, font), operation(operation) {_id = _cpt_id; _cpt_id++;}
		std::string getOperation() const {return operation;}
		int getId() const {return _id;}
		void setGlobalId(int gid) const {_cpt_id = gid;}
		virtual int compute(NumberButton *a, NumberButton *b) {return 0;};
};

int OperationButton::_cpt_id = 0;

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
			if (b->getValue() && !(a->getValue() % b->getValue()))
				return a->getValue() / b->getValue();
			a->setState(0);
			b->setState(0);
			return -1;
		}
};
