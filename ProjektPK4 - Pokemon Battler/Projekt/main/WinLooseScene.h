#pragma once
#ifndef WIN_LOOSE_SCENE_H
#define WIN_LOOSE_SCENE_H

#include <memory>
#include <vector>

#include "TextBoxMedium.h"

class Player;
class Enemy;

class WinLooseScene
{
private: //variables
	int activeCell;
	std::string saveName;
	std::string bannerText;
	std::vector<std::unique_ptr<TextBoxMedium>> menu;

public:	 //variables

private: //methods
	void initVariables();
	int pollEvents();
	void update(int action, Player& player, Enemy& enemy);
	void render();
	void autosave(Player& player, Enemy& enemy);

public:  //methods 
	WinLooseScene();
	void playScene(std::string _bannerText, Player& player, Enemy& enemy);

};

#endif //WIN_LOOSE_SCENE_H




