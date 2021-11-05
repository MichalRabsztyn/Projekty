#pragma once
#ifndef CHOOSE_POKEMON_SCENE_H
#define CHOOSE_POKEMON_SCENE_H

#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include <memory>
#include <vector>
#include <string>

class TextBoxBase;
class TextBoxLong;
class TextBoxMedium;
class Player;

class ChoosePokemonScene
{
private: //variables
	int activeCell;
	Player* player;
	std::string outputInfo;
	std::vector<std::unique_ptr<TextBoxBase>> scene;

public:	 //variables

private: //methods
	void initVariables();
	void createCellLayout();
	int pollEvents();
	void update();
	void render();

public:	 //methods
	ChoosePokemonScene(Player& _player);
	int playScene();

};

#endif //CHOOSE_POKEMON_SCENE_H