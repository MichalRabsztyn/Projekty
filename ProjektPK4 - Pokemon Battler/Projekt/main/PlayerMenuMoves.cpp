#include "PlayerMenuMoves.h"
#include "Move.h"
#include "App.h"
#include "Pokemon.h"

using namespace sf;
PlayerMenuMoves::PlayerMenuMoves(int r, int g, int b, Pokemon &_pokemon) : PlayerMenu(r, g, b)
{
	pokemon = &_pokemon;
	o0.setFillColor(Color(r - 20, g - 20, b - 20));
	o0.setSize(Vector2f(plain.getSize().x * 0.25f, plain.getSize().y * 0.4f));
	back.setFillColor(Color(r - 20, g - 20, b - 20));
	back.setSize(Vector2f(plain.getSize().x * 0.125f, plain.getSize().y * 0.4f));

	o1 = o0;
	o2 = o0;
	o3 = o0;

	auto plainCenter = Vector2f(plain.getPosition().x + plain.getSize().x / 2.f, plain.getPosition().y + plain.getSize().y / 2.f);
	o0.setPosition(plainCenter.x - o0.getSize().x - 0.0125f * plainCenter.x, plainCenter.y - o0.getSize().y - 0.0125f * plainCenter.y);
	o1.setPosition(plainCenter.x + 0.0125f * plainCenter.x, plainCenter.y - o1.getSize().y - 0.0125f * plainCenter.y);
	o2.setPosition(plainCenter.x - o2.getSize().x - 0.0125f * plainCenter.x, plainCenter.y + 0.0125f * plainCenter.y);
	o3.setPosition(plainCenter.x + 0.0125f * plainCenter.x, plainCenter.y + 0.0125f * plainCenter.y);
	back.setPosition(plainCenter.x + (2.f* 0.0125f * plainCenter.x) + o0.getSize().x, plainCenter.y + 0.0125f * plainCenter.y);

	tiles.push_back(&o0);
	tiles.push_back(&o1);
	tiles.push_back(&o2);
	tiles.push_back(&o3);
	tiles.push_back(&back);

	t_o0.setFont(app.font);
	t_o0.setCharacterSize(14);
	t_o0.setFillColor(Color::Black);

	t_o1 = t_o0;
	t_o2 = t_o0;
	t_o3 = t_o0;
	t_back = t_o0;

	t_o0.setString(pokemon->moveList[0]->getName() + " " + std::to_string(pokemon->moveList[0]->getCurrentPP()) + "/" + std::to_string(pokemon->moveList[0]->getPP()));
	t_o1.setString(pokemon->moveList[1]->getName() + " " + std::to_string(pokemon->moveList[1]->getCurrentPP()) + "/" + std::to_string(pokemon->moveList[1]->getPP()));
	t_o2.setString(pokemon->moveList[2]->getName() + " " + std::to_string(pokemon->moveList[2]->getCurrentPP()) + "/" + std::to_string(pokemon->moveList[2]->getPP()));
	t_o3.setString(pokemon->moveList[3]->getName() + " " + std::to_string(pokemon->moveList[3]->getCurrentPP()) + "/" + std::to_string(pokemon->moveList[3]->getPP()));
	t_back.setString("Back");

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

	t_back.setPosition(back.getPosition() + back.getSize() / 2.0f);
	textRect = t_back.getLocalBounds();
	t_back.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}

void PlayerMenuMoves::ppStatus()
{
	t_o0.setString(pokemon->moveList[0]->getName() + " " + std::to_string(pokemon->moveList[0]->getCurrentPP()) + "/" + std::to_string(pokemon->moveList[0]->getPP()));
	t_o1.setString(pokemon->moveList[1]->getName() + " " + std::to_string(pokemon->moveList[1]->getCurrentPP()) + "/" + std::to_string(pokemon->moveList[1]->getPP()));
	t_o2.setString(pokemon->moveList[2]->getName() + " " + std::to_string(pokemon->moveList[2]->getCurrentPP()) + "/" + std::to_string(pokemon->moveList[2]->getPP()));
	t_o3.setString(pokemon->moveList[3]->getName() + " " + std::to_string(pokemon->moveList[3]->getCurrentPP()) + "/" + std::to_string(pokemon->moveList[3]->getPP()));
}

void PlayerMenuMoves::activate(int activeCell)
{
	tiles[activeCell]->setOutlineColor(Color::Black);
	tiles[activeCell]->setOutlineThickness(2);
}

void PlayerMenuMoves::deactivate(int activeCell)
{
	tiles[activeCell]->setOutlineThickness(0);
}