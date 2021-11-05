#include "TextBoxMedium.h"
#include "App.h"

using namespace sf;
TextBoxMedium::TextBoxMedium(const std::string& _str, const sf::Font& _font, float _offsetX, float _offsetY, float _scaleX, float _scaleY)
	: TextBoxBase(_str, _font, _offsetX, _offsetY, _scaleX, _scaleY)
{
	rect.setPosition(_offsetX, _offsetY);
	rect.setSize(sf::Vector2f(app.resX * 0.1f * _scaleX, app.resY * 0.1f * _scaleY));
	rect.setFillColor(Color(200, 200, 200));

	text.setCharacterSize(18);
	text.setFillColor(Color::Black);

	text.setPosition(rect.getPosition() + rect.getSize() / 2.0f);
	FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}
