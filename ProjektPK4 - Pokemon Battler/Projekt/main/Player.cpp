#include "Player.h"
#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include "PlayerMenuActions.h"
#include "PlayerMenuMoves.h"
#include "App.h"
#include "TextBoxMedium.h"
#include "TextBoxLong.h"
#include "PlayerMenuBattleScene.h"

#include "Pokemon.h"
#include "ChoosePokemonScene.h"
#include "ChooseActionScene.h"
#include "ChooseMoveScene.h"
#include "OptionsScene.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <string>

using namespace std;
using namespace sf;

void Player::initVariables()
{
	winStreak = 0;
}

Player::Player():Entity()
{
	initVariables();
}

int Player::getWinStreak()
{
	return winStreak;
}

void Player::healAll()
{
	for (auto& e : pokemonList)
	{
		e->setHP(-1* e->getHP());
		e->revive();
	}
}

int Player::playersTurn(ChooseActionScene& chooseAction, ChoosePokemonScene& choosePokemon, ChooseMoveScene& chooseMove, OptionsScene& optionsMenu)
{
	enum ACITONS {move1, move2, moev3, move4, struggle, fight, pokemon, heal, options, back};
	int action = back;
	while (app.window.isOpen()&& action == back)
	{
		action = chooseAction.playScene();
		if (action == fight)
		{
			action = chooseMove.playScene();
		}
		else if (action == pokemon)
		{
			action = choosePokemon.playScene();
		}
		else if (action == options)
		{
			optionsMenu.playScene();
			action = back;
		}
	}
	return action;
}

