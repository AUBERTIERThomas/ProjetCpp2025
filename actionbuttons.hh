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
	protected:
		static const std::vector<std::string> imageNames; // Vecteur contenant des images pouvant être appliqués aux boutons
		static std::vector<sf::Texture> textureList; // Les textures sont en static pour ne pas les charger plusieurs fois (très coûteux !)
		sf::Sprite sprite;
		
	public:
		ActionButton(const std::string& label, float x, float y, float width, float height, sf::Font& font, const int imageId, const int dec) : Button(label, x, y, width, height, font) {
			sprite.setPosition(x,y);
			sprite.setTexture(textureList[imageId]);
			
			text.setPosition(x+dec,y+12);
		};
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
		bool isClicked(const sf::Vector2f& mousePos);
};

const std::vector<std::string> ActionButton::imageNames = {"CPP_button3.png","CPP_button3b.png"};
std::vector<sf::Texture> ActionButton::textureList = ActionButton::loadTextures(); // Effectue l'opération qu'une seule fois

bool ActionButton::isClicked(const sf::Vector2f& mousePos) { // La redéfinition de isClicked sert à ignorer l'état (ce type de bouton ne s'en sert pas)
	if (getState())
		return 0;
	if (shape.getGlobalBounds().contains(mousePos)){
		return 1;
	}
	return 0;
}
