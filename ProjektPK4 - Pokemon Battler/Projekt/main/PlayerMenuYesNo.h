#pragma once
#ifndef PLAYER_MENU_YES_NO_H
#define PLAYER_MENU_YES_NO_H

#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)

class TextBoxMedium;

class PlayerMenuYesNo
{
private: //variables
	sf::RectangleShape rect;
	sf::Text text;
	TextBoxMedium *yes_button;
	TextBoxMedium *no_button;
	std::shared_ptr<TextBoxMedium> s_yes_button;
	std::shared_ptr<TextBoxMedium> s_no_button;

	std::vector<sf::Drawable*> scene;
	std::vector<std::shared_ptr<sf::Drawable>> s_scene;

public:  //variables

private: //methods

public:  //methods
	PlayerMenuYesNo(std::vector<std::shared_ptr<sf::Drawable>> _scene, float posX, float posY, std::string _text);

	bool yesNo();
};
#endif //PLAYER_MENU_YES_NO