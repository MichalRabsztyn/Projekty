#pragma once
#ifndef PLAYER_MENU_MOVES_H
#define PLAYER_MENU_MOVES_H

#include "PlayerMenu.h"

class Pokemon;

class PlayerMenuMoves : public PlayerMenu
{
private: //variables
	Pokemon* pokemon;
	std::vector<sf::RectangleShape*> tiles;

public:  //variables

private: //methods
	void ppStatus();
	
public:  //methods
	PlayerMenuMoves(int r, int g, int b, Pokemon& _pokemon);
	void activate(int activeCell);
	void deactivate(int activeCell);

};
#endif //PLAYER_MENU_MOVES_H