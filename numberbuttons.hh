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
		int _id; // id du bouton
		static int _cpt_id; // Compteur de l'id de la classe (sert à attribuer un nouvel id dans le constructeur)
		/*------------------------------------------*/
		static const std::vector<std::string> imageNames; // Liste des images pouvant être appliqué au bouton
		static std::vector<sf::Texture> textureList; // Les textures sont en static pour ne pas les charger plusieurs fois (très coûteux !)
		sf::Sprite sprite;
	public:
		void setState(short a);
		/*------------------------------------------*/
		NumberButton(int value, float x, float y, float width, float height, sf::Font& font) : Button(std::to_string(value), x, y, width, height, font), value(value) {
			_id = _cpt_id;
			_cpt_id++;
			
			sprite.setPosition(x,y);
			
			int l = std::to_string(value).length();
			text.setPosition(x+width/2-6*l,y+12); // Pour que le texte soit bien à l'intérieur du bouton
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
		    window.draw(sprite); // La redéfinition de draw sert à afficher la texture du bouton plutôt que sa couleur
		    window.draw(text);
		}
		/*------------------------------------------*/
		int getValue() const {return value;}
		int getId() const {return _id;}
		void setGlobalId(int gid) const {_cpt_id = gid;}
	private:
		int value; // Valeur chiffrée du bouton
};

int NumberButton::_cpt_id = 0;

const std::vector<std::string> NumberButton::imageNames = {"CPP_button0.png","CPP_button1.png","CPP_button2.png"};
std::vector<sf::Texture> NumberButton::textureList = NumberButton::loadTextures(); // Effectue l'opération qu'une seule fois

void NumberButton::setState(short a) {
	_state = a;
	sprite.setTexture(textureList[a]); // La redéfinition de setState sert à changer la texture du bouton plutôt que sa couleur
};
