#pragma once
#ifndef MAIN_MENU_SCENE
#define MAIN_MENU_SCENE

#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include <vector>
#include <memory>

#include "TextBoxMedium.h"

class TextBoxMedium;

class MainMenuScene
{
private: //variables
	int activeCell;
	bool saveExists;
	std::vector<std::unique_ptr<TextBoxMedium>> menu;
	sf::Texture t_logo;
	sf::Sprite s_logo;

public:  //variables

private: //methods
	void initVariables();
	void checkSaveFile();
	int pollEvents();
	int update();
	void render();

public:  //methods
	MainMenuScene();
	int playScene();

};

#endif //MAIN_MENU_SCENE