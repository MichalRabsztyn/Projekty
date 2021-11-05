#pragma once
#ifndef PLAYER_MENU_ACTIONS_H
#define PLAYER_MENU_ACTIONS_H

#include <vector>

#include "PlayerMenu.h"

class Player;

class PlayerMenuActions : public PlayerMenu
{
private: //variables
	
public:  //variables
	std::vector<sf::RectangleShape*> tiles;

private: //methods
	
public:  //methods
	PlayerMenuActions(int r, int g, int b, Player& player);
	void activate(int activeCell);
	void deactivate(int activeCell);
	void healStatus(Player& player);

};
#endif //PLAYER_MENU_ACTIONS_H