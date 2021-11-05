#include "TextBoxBase.h"
#include "Pokemon.h"
#include "App.h"
#include "Entity.h"
#include <string>


using namespace std;
using namespace sf;

void TextBoxBase::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	app.window.draw(rect);
	app.window.draw(text);
}

TextBoxBase::TextBoxBase(const string& _str, const Font& _font, float _offsetX, float _offsetY, float _scaleX, float _scaleY)
{
	text.setString(_str);
	text.setFont(_font); 
}

void TextBoxBase::select()
{
	rect.setFillColor(Color(128, 128, 128));
}

void TextBoxBase::deselect()
{
	rect.setFillColor(Color(192, 192, 192));
}

void TextBoxBase::activate()
{
	rect.setOutlineColor(Color::Black);
	rect.setOutlineThickness(2);
}

void TextBoxBase::deactivate()
{
	rect.setOutlineThickness(0);
}

void TextBoxBase::markFainted()
{
	RectangleShape faintedMark;
	Text fntdText;
	faintedMark.setPosition(rect.getPosition()+ Vector2f(0.05f*rect.getSize().x, 0.7f*rect.getSize().y));
	faintedMark.setSize(rect.getSize() * 0.2f);
	faintedMark.setFillColor(Color::Red);
	fntdText.setPosition(faintedMark.getPosition());
	fntdText.setFillColor(Color::White);
	fntdText.setCharacterSize(12);
	fntdText.setFont(app.font);
	fntdText.setString("FNTD");

	app.window.draw(faintedMark);
	app.window.draw(fntdText);
}

void TextBoxBase::setString(std::string& _str)
{
	text.setString(_str);
	text.setPosition(rect.getPosition() + rect.getSize() / 2.0f);
	FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}

void TextBoxBase::showHealth(std::shared_ptr<Pokemon> pokemon)
{
	RectangleShape healthBarFull, healthBarEmpty;
	Text healthPoints;
	float healthC = static_cast<float>(pokemon->getCurrentHP());
	float healthM = static_cast<float>(pokemon->getHP());
	float health = healthC / healthM;
	healthBarFull.setPosition(rect.getPosition() + Vector2f(0.45f * rect.getSize().x, 0.7f * rect.getSize().y));
	healthBarFull.setSize(Vector2f(rect.getSize().x * 0.5f * health, rect.getSize().y * 0.15f));
	healthBarFull.setFillColor(Color(0, 215, 31));

	healthBarEmpty.setPosition(rect.getPosition() + Vector2f(0.45f * rect.getSize().x, 0.7f * rect.getSize().y));
	healthBarEmpty.setSize(Vector2f(rect.getSize().x * 0.5f, rect.getSize().y *0.15f));
	healthBarEmpty.setFillColor(Color(0, 129, 14));
	healthBarEmpty.setOutlineThickness(1);
	healthBarEmpty.setOutlineColor(Color(32,32,32));

	healthPoints.setPosition(healthBarEmpty.getPosition()+Vector2f(0.3f*rect.getSize().x, 0.1f*rect.getSize().y));
	healthPoints.setFillColor(Color::Black);
	healthPoints.setCharacterSize(12);
	healthPoints.setFont(app.font);
	healthPoints.setString(to_string(pokemon->getCurrentHP())+"/"+to_string(pokemon->getHP()));


	app.window.draw(healthBarEmpty);
	app.window.draw(healthBarFull);
	app.window.draw(healthPoints);
}
