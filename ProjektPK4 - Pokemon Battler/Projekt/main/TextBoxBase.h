#pragma once
#ifndef TEXT_BOX_BASE_H
#define TEXT_BOX_BASE_H
#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include <string>
#include <memory>
#include "Pokemon.h"

class Pokemon;

class TextBoxBase : public sf::Drawable
{
private: //variables
	bool isActive = false;

public:  //variables
	sf::Text text;
	sf::RectangleShape rect;

private: //methods
	void markFainted();

public:  //methods
	void showHealth(std::shared_ptr <Pokemon> pokemon);
	void setString(std::string& _str);
	void select();
	void deselect();
	void activate();
	void deactivate();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected://methods
	TextBoxBase(const std::string& _str, const sf::Font& _font, float _offsetX, float _offsetY, float _scaleX, float _scaleY);
	
};
#endif //TEXT_BOX_BASE_H