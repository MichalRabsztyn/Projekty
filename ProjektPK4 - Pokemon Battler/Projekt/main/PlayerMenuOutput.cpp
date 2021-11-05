#include "PlayerMenuOutput.h"
#include "PlayerMenuBattleScene.h"
#include "App.h"

using namespace sf;

PlayerMenuOutput::PlayerMenuOutput(int r, int g, int b)
{
	plain.setPosition(0, app.resY * 0.65f);
	plain.setSize(Vector2f(app.resX, app.resY * 0.35f));
	plain.setFillColor(Color(r, g, b));
	plain.setOutlineColor(Color::Black);
	plain.setOutlineThickness(5);
	t_o0.setFont(app.font);
	t_o0.setCharacterSize(18);
	t_o0.setFillColor(Color::Black);
}

void PlayerMenuOutput::printOut(std::string _str, PlayerMenuBattleScene& pmBs)
{
	t_o0.setString(_str);
	t_o0.setPosition(plain.getPosition() + plain.getSize() / 2.0f);
	FloatRect textRect = t_o0.getLocalBounds();
	t_o0.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	app.window.clear();
	app.window.draw(pmBs);
	app.window.draw(plain);
	app.window.draw(t_o0);
	app.window.display();
	sleep(seconds(1));
}

void PlayerMenuOutput::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	app.window.draw(plain);
	app.window.draw(t_o0);
}
