#pragma once
#ifndef OPTIONS_SCENE_H
#define OPTIONS_SCENE_H

#include <fstream> 
#include <vector>
#include <memory>
#include <string>

#include "TextBoxMedium.h"

class Player;
class Enemy; 
class Pokemon;
class TextBoxMedium;

class OptionsScene
{
private: //variables
	int activeCell;
	std::vector<std::unique_ptr<TextBoxMedium>> menu;
	std::string saveName;
	Player* player;
	Enemy* enemy;
	std::string info;

public:  //variables

private: //methods
	void initVariables();
	int pollEvents();
	void update(int action);
	void render();

public:  //methods
	OptionsScene(Player& _player, Enemy& _enemy);
	void playScene();
	void save();

};
#endif //OPTIONS_SCENE_H



