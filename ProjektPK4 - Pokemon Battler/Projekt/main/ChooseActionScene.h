#pragma once
#ifndef CHOOSE_ACTION_H
#define CHOOSE_ACTION_H

#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include <memory>

#include "PlayerMenuActions.h" 

class Player;
class PlayerMenuBattleScene;
class PlayerMenuActions;

class ChooseActionScene
{
private: //variables
	int activeCell;
	Player* player;
	PlayerMenuBattleScene* battleScene;
	std::unique_ptr<PlayerMenuActions> menuActions;
	int r = 200, g = 200, b = 200;

public:  //variables

private: //methods
	void initVariables();
	int pollEvents();
	void update();
	void render();

public:  //methods
	ChooseActionScene(Player& _player, PlayerMenuBattleScene& _pmbs);
	int playScene();

};

#endif //CHOOSE_ACTION_H
