#pragma once
#ifndef SETUP_SCENE_H
#define SETUP_SCENE_H

#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include <memory>
#include <vector>
#include <string>
#include <fstream>

#include "App.h"

class Player;
class Enemy;
class TextBoxLong;
class TextBoxSmall;

class SetupScene
{
private: //variables
	sf::Event event;
	int pokemonChosen;
	int activeCell;
	int indexList[6];
	bool isReady;
	std::shared_ptr<TextBoxLong> banner;
	std::vector < std::shared_ptr<TextBoxSmall> > cellList;
	std::vector < std::shared_ptr<Drawable> > scene;

public:	 //variables

private: //methods
	void initVariables();
	int loadPokemons();
	void pollEvents();
	void update(Player& player, Enemy& enemy);
	void render();

public:	 //methods
	SetupScene();
	void playScene(Player& player, Enemy& enemy);
};

#endif //SETUP_SCENE_H

