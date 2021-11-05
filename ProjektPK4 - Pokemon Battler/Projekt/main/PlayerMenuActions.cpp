#include "PlayerMenuActions.h"
#include "Player.h"
#include "App.h"

PlayerMenuActions::PlayerMenuActions(int r, int g, int b, Player &player) : PlayerMenu(r, g, b)
{
	o0.setFillColor(Color(r - 20, g - 20, b - 20));
	o0.setSize(Vector2f(plain.getSize().x * 0.25f, plain.getSize().y * 0.4f));

	o1 = o0;
	o2 = o0;
	o3 = o0;

	auto plainCenter = Vector2f(plain.getPosition().x + plain.getSize().x / 2, plain.getPosition().y + plain.getSize().y / 2);
	o0.setPosition(plainCenter.x - o0.getSize().x - 0.0125f * plainCenter.x, plainCenter.y - o0.getSize().y - 0.0125f * plainCenter.y);
	o1.setPosition(plainCenter.x + 0.0125f * plainCenter.x, plainCenter.y - o1.getSize().y - 0.0125f * plainCenter.y);
	o2.setPosition(plainCenter.x - o2.getSize().x - 0.0125f * plainCenter.x, plainCenter.y + 0.0125f * plainCenter.y);
	o3.setPosition(plainCenter.x + 0.0125f * plainCenter.x, plainCenter.y + 0.0125f * plainCenter.y);

	tiles.push_back(&o0);
	tiles.push_back(&o1);
	tiles.push_back(&o2);
	tiles.push_back(&o3);

	t_o0.setFont(app.font);
	t_o0.setCharacterSize(18);
	t_o0.setFillColor(Color::Black);

	t_o1 = t_o0;
	t_o2 = t_o0;
	t_o3 = t_o0;

	t_o0.setString("Fight");
	t_o1.setString("Pokemon");
	t_o2.setString("Heal\n"+ std::to_string(int(player.getHeal()))+"/1");
	t_o3.setString("Options");

	t_o0.setPosition(o0.getPosition() + o0.getSize() / 2.0f);
	FloatRect textRect = t_o0.getLocalBounds();
	t_o0.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	t_o1.setPosition(o1.getPosition() + o1.getSize() / 2.0f);
	textRect = t_o1.getLocalBounds();
	t_o1.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	t_o2.setPosition(o2.getPosition() + o2.getSize() / 2.0f);
	textRect = t_o2.getLocalBounds();
	t_o2.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	t_o3.setPosition(o3.getPosition() + o3.getSize() / 2.0f);
	textRect = t_o3.getLocalBounds();
	t_o3.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}

void PlayerMenuActions::healStatus(Player& player)
{
	t_o2.setString("Heal\n" + std::to_string(int(player.getHeal())) + "/1");
}

void PlayerMenuActions::activate(int activeCell)
{
	tiles[activeCell]->setOutlineColor(Color::Black);
	tiles[activeCell]->setOutlineThickness(2);
}

void PlayerMenuActions::deactivate(int activeCell)
{
	tiles[activeCell]->setOutlineThickness(0);
}