#pragma once
#ifndef PLAYER_MENU_OUTPUT_H
#define PLAYER_MENU_OUTPUT_H

#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)

class PlayerMenuBattleScene;

class PlayerMenuOutput : public sf::Drawable
{
private: //variables
	sf::RectangleShape plain;
	sf::Text t_o0;

public:  //variables

private: //methods

public:  //methods
	PlayerMenuOutput(int r, int g, int b);

	void printOut(std::string _str, PlayerMenuBattleScene& pmBs);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
};
#endif //PLAYER_MENU_OUTPUT_H