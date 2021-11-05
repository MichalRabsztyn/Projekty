#include "PlayerMenu.h"
#include "App.h"

using namespace sf;

PlayerMenu::PlayerMenu(int r, int g, int b)
{
	plain.setOutlineColor(Color::Black);
	plain.setOutlineThickness(5);
	plain.setFillColor(Color(r, g, b));
	plain.setPosition(0, 0.65f * app.resY);
	plain.setSize(Vector2f(app.resX, 0.35f * app.resY));
}

void PlayerMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	o0.getFillColor();
	app.window.draw(plain);
	app.window.draw(o0);
	app.window.draw(o1);
	app.window.draw(o2);
	app.window.draw(o3);
	app.window.draw(t_o0);
	app.window.draw(t_o1);
	app.window.draw(t_o2);
	app.window.draw(t_o3);
	app.window.draw(back);
	app.window.draw(t_back);
}
