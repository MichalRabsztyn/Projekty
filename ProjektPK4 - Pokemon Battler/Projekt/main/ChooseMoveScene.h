#pragma once
#ifndef CHOOSE_MOVE_INFO
#define CHOOSE_MOVE_INFO

#include <memory>

#include "PlayerMenuMoves.h"

class Player;
class PlayerMenuBattleScene;
class PlayerMenuMoves;

class ChooseMoveScene
{ 
private: //variables
	int activeCell;
	Player* player;
	PlayerMenuBattleScene* battleScene;
	std::unique_ptr<PlayerMenuMoves> menuMoves;
	int r = 200, g = 200, b = 200;

public:  //variables

private: //methods
	void initVariables();
	int pollEvents();
	int update(int action);
	void render();

public:  //methods
	ChooseMoveScene(Player& _player, PlayerMenuBattleScene& _pmbs);
	int playScene();

};
#endif //CHOOSE_MOVE_INFO




