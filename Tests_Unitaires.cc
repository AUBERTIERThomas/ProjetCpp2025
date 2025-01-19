#include <iostream>
#include <string>
#include <cassert>

#include "buttons.hh"
#include "numberbuttons.hh"
#include "operationbuttons.hh"
#include "actionbuttons.hh"

#include "scenes.hh"
#include "numberscenes.hh"
#include "endscenes.hh"

void CHECK(bool cond) {
	assert(cond);
	std::cout << "."; // Un point est affiché par nombre de test passé pour chaque section
}

/* TestCase fait maison. Par soucis de ressemblance, on utilise une fonction CHECK mais le vrai test est fait via un assert. */
int main() {

	std::cout << "--------------------------------------------" << std::endl;
	std::cout << "1: Boutons chiffres" << std::endl << "   ";
	
	sf::Font globalFont;
	CHECK(globalFont.loadFromFile("arial.ttf") == true);
	NumberButton n_but_1(10, 0, 0, 100, 100, globalFont);
  CHECK(n_but_1.getValue() == 10);
  CHECK(n_but_1.getId() == 0);
  NumberButton n_but_2(42, 100, 100, 1, 2, globalFont);
  CHECK(n_but_2.getValue() == 42);
  CHECK(n_but_2.getId() == 1);
  n_but_1.setGlobalId(0);
  NumberButton n_but_3(5, 69, 420, 120, 120, globalFont);
  CHECK(n_but_3.getValue() == 5);
  CHECK(n_but_3.getId() == 0);
  n_but_1.setGlobalId(42);
  NumberButton n_but_4(-1, 0, 0, 120, 120, globalFont);
  CHECK(n_but_4.getValue() == -1);
  CHECK(n_but_4.getId() == 42);
  std::cout << std::endl << "   OK" << std::endl;
  
  std::cout << "--------------------------------------------" << std::endl;
  std::cout << "2: Boutons opérations" << std::endl << "   ";
  
  AdditionButton add(50, 500, 50, 50, globalFont);
  SubstractionButton sub(110, 500, 50, 50, globalFont);
  MultiplicationButton mul(170, 500, 50, 50, globalFont);
  DivisionButton div(230, 500, 50, 50, globalFont);
  CHECK(add.compute(&n_but_1,&n_but_2) == 52);
  CHECK(add.compute(&n_but_3,&n_but_4) == 4);
  CHECK(sub.compute(&n_but_1,&n_but_2) == -32);
  CHECK(sub.compute(&n_but_3,&n_but_4) == 6);
  CHECK(mul.compute(&n_but_1,&n_but_2) == 420);
  CHECK(mul.compute(&n_but_3,&n_but_4) == -5);
  CHECK(div.compute(&n_but_1,&n_but_3) == 2);
  CHECK(div.compute(&n_but_2,&n_but_3) == -1); // Division non entière
  std::cout << std::endl << "   OK" << std::endl;
  
  std::cout << "--------------------------------------------" << std::endl;
  std::cout << "3: Scène principale" << std::endl;
  
  sf::RenderWindow window(sf::VideoMode(800, 600), "Jeu de chiffres");
	window.setFramerateLimit(60);
	NumberScene ns(5, window);
	std::cout << "   " << ns << std::endl << "   ";
	NumberButton b0 = ns[0];
	NumberButton b1 = ns[1];
	CHECK(add.compute(&b0,&b1) == b0.getValue() + b1.getValue());
	ns.AddNumberButton(100);
	CHECK(ns[5].getValue() == 100);
	ns.RemoveNumberButtons(2);
	CHECK(ns.getButNumber() == 2);
  std::cout << std::endl << "   OK" << std::endl;
	
	std::cout << "--------------------------------------------" << std::endl;
	std::cout << "4: Scène finale" << std::endl << "   ";
	// Vérifie si l'image affichée concorde bien avec le score
	EndScene es_1(0, window);
	EndScene es_2(5, window);
	EndScene es_3(20, window);
	EndScene es_4(100, window);
	CHECK(es_1.getGrade() == 0);
	CHECK(es_2.getGrade() == 1);
	CHECK(es_3.getGrade() == 2);
	CHECK(es_4.getGrade() == 3);
  std::cout << std::endl << "   OK" << std::endl;
  
  std::cout << "--------------------------------------------" << std::endl;
  
  return 0;
}



