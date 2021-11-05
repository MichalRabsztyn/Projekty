#include "TextBoxSmall.h"
#include "App.h"

using namespace sf;

TextBoxSmall::TextBoxSmall(const std::string& _str, const Font& _font, float _offsetX, float _offsetY, float _scaleX, float _scaleY)
	: TextBoxBase(_str, _font, _offsetX, _offsetY, _scaleX, _scaleY)
{

	rect.setPosition(_offsetX, _offsetY);
	rect.setSize(sf::Vector2f((app.resX * 0.2f) - 2.f * _scaleX, (app.resY * 0.0625f * _scaleY) - 2.f));
	rect.setFillColor(Color(192, 192, 192));

	text.setCharacterSize(12);
	text.setFillColor(Color::Black);

	text.setPosition(rect.getPosition() + rect.getSize() / 2.0f);
	FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}
