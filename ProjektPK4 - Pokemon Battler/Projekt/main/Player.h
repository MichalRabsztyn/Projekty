#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class PlayerMenuBattleScene;
class ChoosePokemonScene;
class ChooseActionScene;
class ChooseMoveScene;
class OptionsScene;

class Player : public Entity
{
private: //variables
	int winStreak;
	std::unique_ptr<ChoosePokemonScene> choosePokemon;

public: //variables

private: //methods
	void initVariables();

public: //methods
	Player();
	int getWinStreak();
	int playersTurn(ChooseActionScene& _chooseAction, ChoosePokemonScene& _choosePokemon, ChooseMoveScene& _chooseMove, OptionsScene& options);
	void healAll();

};

#endif //PLAYER_H