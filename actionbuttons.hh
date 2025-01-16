#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "buttons.hh"

class ActionButton : public Button {
	public:
		ActionButton(const std::string& label, float x, float y, float width, float height, sf::Font& font) : Button(label, x, y, width, height, font) {}
		bool isClicked(const sf::Vector2f& mousePos);
};

bool ActionButton::isClicked(const sf::Vector2f& mousePos) {
	if (getState())
		return 0;
	if (shape.getGlobalBounds().contains(mousePos)){
		std::cout << "hah" << std::endl;
		return 1;
	}
	return 0;
}
