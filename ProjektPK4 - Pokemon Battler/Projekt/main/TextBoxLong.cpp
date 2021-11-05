#include "TextBoxLong.h"
#include "App.h"

TextBoxLong::TextBoxLong(const std::string& _str, const sf::Font& _font, float _offsetX, float _offsetY, float _scaleX, float _scaleY)
	: TextBoxBase(_str, _font, _offsetX, _offsetY, _scaleX, _scaleY)
{
	rect.setPosition(_offsetX, _offsetY);
	rect.setSize(sf::Vector2f(app.resX * _scaleX * 1.0f, ((app.resY * 0.0625f * _scaleY) - 2.f) * 1.0f));
	rect.setFillColor(sf::Color(180, 180, 180));

	text.setCharacterSize(16);
	text.setFillColor(sf::Color::Black);

	text.setPosition(rect.getPosition() + rect.getSize() / 2.0f);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}