#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "buttons.hh"

class NumberButton : public Button {
	protected:
		int _id;
		static int _cpt_id;
		/*------------------------------------------*/
		static const std::vector<std::string> imageNames;
		static std::vector<sf::Texture> textureList;
		sf::Sprite sprite;
	public:
		void setState(short a);
		/*------------------------------------------*/
		NumberButton(int value, float x, float y, float width, float height, sf::Font& font) : Button(std::to_string(value), x, y, width, height, font), value(value) {
			_id = _cpt_id;
			_cpt_id++;
			sprite.setPosition(x,y);
			this->shape.setFillColor(sf::Color(255, 255, 255, 0));
			this->text.setFillColor(sf::Color::Black);
			setState(0);
		}
		/*------------------------------------------*/
		static std::vector<sf::Texture> loadTextures() {
			std::vector<sf::Texture> tL;
			for (size_t i = 0; i < imageNames.size(); i++) {
				sf::Texture t;
				t.loadFromFile(imageNames[i]);
				tL.push_back(t);
			}
			return tL;
		}
		/*------------------------------------------*/
		void draw(sf::RenderWindow& window) {
		    window.draw(sprite);
		    window.draw(text);
		}
		/*------------------------------------------*/
		int getValue() const {return value;}
		int getId() const {return _id;}
		void setGlobalId(int gid) const {_cpt_id = gid;}
	private:
		int value;
};

int NumberButton::_cpt_id = 0;

const std::vector<std::string> NumberButton::imageNames = {"CPP_button0.png","CPP_button1.png","CPP_button2.png"};
std::vector<sf::Texture> NumberButton::textureList = NumberButton::loadTextures();

void NumberButton::setState(short a) {
	_state = a;
	//std::cout << "ewe " << a << " et " << _id << " et " << imageNames[a] << std::endl;
	sprite.setTexture(textureList[a]);
};
