#pragma once
#ifndef TEXT_BOX_MEDIUM_H
#define TEXT_BOX_MEDIUM_H

#include "TextBoxBase.h"

class TextBoxMedium : public TextBoxBase
{
private: //variables

public:  //variables

private: //methods

public:  //methods
	TextBoxMedium(const std::string& _str, const sf::Font& _font, float _offsetX, float _offsetY, float _scaleX, float _scaleY);
};
#endif //TEXT_BOX_MEDIUM_H