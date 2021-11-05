#pragma once
#ifndef PLAYER_MENU_H
#define PLAYER_MENU_H

#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)

class PlayerMenu : public sf::Drawable
{
private: //variables

public:  //variables
	sf::RectangleShape plain, o0, o1, o2, o3, back;
	sf::Text t_o0, t_o1, t_o2, t_o3, t_back;

private: //methods

public:  //methods
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected: //methods
	PlayerMenu(int r, int g, int b);	

};
#endif //PLAYER_MENU_H