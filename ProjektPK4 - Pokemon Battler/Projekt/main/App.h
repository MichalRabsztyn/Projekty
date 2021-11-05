#pragma once
#ifndef APP_H
#define APP_H

#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include <iostream>

#define _resX 800
#define _resY 600

using namespace sf;

enum class STATE { SETUP, BATTLE, EXIT, CONTINUE, MAIN_MENU };

class App
{
private: //variables
	//Sprites by r/JordieBo https://i.imgur.com/4QgFYas.png
	//Original logo by Game Freak - Satoshi Tajiri Ken Sugimori Junichi Masuda

public:  //variables
	RenderWindow window;
	Font font;
	const Color defaultBackgroundColor = Color(205, 229, 254);
	const Color defaultButtonColor = Color(200, 200, 200);
	const float resX = _resX,
				 resY = _resY;
	STATE gameState = STATE::MAIN_MENU;
	int pokemonCount = 1;
	std::string movesData = "moves.dat";
	std::string pokemonsData = "pokemon.dat";
	std::string fontData = "assets/fonts/PKMNRBYGSC.ttf";

private: //methods
	void initWindow();

public:  //methods
	App();
	~App() {};
	sf::Color colorShift(const sf::Color& currentColor, sf::Color& desiredColor, float shiftSpeed);
	void exitGame();
	void handleException(int ex);
	void Debug(std::string str); 

};

inline App app;

#endif //APP_H

