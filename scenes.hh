#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include <SFML/Graphics.hpp>

#include "buttons.hh"
#include "numberbuttons.hh"
#include "operationbuttons.hh"
#include "actionbuttons.hh"

class Scene {
	protected:
		sf::Font globalFont;
	public:
		Scene();
};

Scene::Scene() {
	if (!globalFont.loadFromFile("arial.ttf")) {
        std::cout << "Erreur : police non disponible (arial.ttf)" << std::endl;
    }
}







