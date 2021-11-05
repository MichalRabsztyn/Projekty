#include "ChoosePokemonScene.h"
#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include "App.h"
#include "TextBoxLong.h"
#include "TextBoxMedium.h"
#include "Player.h"
#include "Pokemon.h"

void ChoosePokemonScene::initVariables()
{
	activeCell = 0;
	outputInfo = "";
	createCellLayout();
}

void ChoosePokemonScene::createCellLayout()
{
	int oddOrNot = 0;
	float posX = 0.f * app.resX;
	float posY = 0.1f * app.resY;
	for (int i = 0; i<6; i++)
	{
		if (oddOrNot % 2 == 0)
		{
			posX = 0.19f * app.resX;
		}
		else
		{
			posX = 0.51f * app.resX;
		}
		posY += 0.08f * app.resY;
		scene.push_back(std::make_unique<TextBoxMedium>(player->pokemonList[oddOrNot]->getName(), app.font, posX, posY, 3.f, 1.5f));
		oddOrNot++;
	}
	scene.push_back(std::make_unique<TextBoxMedium>("Back", app.font, 0.7f * app.resX, 0.85f * app.resY, 3.f, 1.5f));
	scene.push_back(std::make_unique<TextBoxLong>("Choose a Pokemon.", app.font, 0.f, 0.f, 1.f, 2.f));
	scene.push_back(std::make_unique <TextBoxMedium>(outputInfo, app.font, 0.f, app.resY * 0.85f, 6.9f, 1.5f));
	scene[0]->activate();
}

int ChoosePokemonScene::pollEvents()
{
	Event event;
	enum actions {doNothing, input, pokemon=6, back=9};
	int action = doNothing;
	while (app.window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			app.gameState = STATE::EXIT;
			app.window.close();
			break;
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			app.gameState = STATE::EXIT;
			app.window.close();
			break;
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && activeCell < 6) {
			scene[activeCell]->deactivate();
			if (activeCell == 5)
			{
				activeCell++;
			}
			else
			{
				activeCell += 2;
			}
			scene[activeCell]->activate();
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && activeCell > 1) {
			scene[activeCell]->deactivate();
			if (activeCell == 6) activeCell--;
			else activeCell -= 2;
			scene[activeCell]->activate();
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left && (activeCell == 1 || activeCell == 3 || activeCell == 5)) {
			scene[activeCell]->deactivate();
			activeCell--;
			scene[activeCell]->activate();
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right && (activeCell == 0 || activeCell == 2 || activeCell == 4)) {
			scene[activeCell]->deactivate();
			activeCell++;
			scene[activeCell]->activate();
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {

			if ((player->currentlyBattling == nullptr || player->currentlyBattling->getCurrentHP()<=0) && activeCell == 6)
			{
				outputInfo = "Can't go back";
				action = input;
			}
			else if (activeCell <6 && player->currentlyBattling == player->pokemonList[activeCell] && player->currentlyBattling->getFainted() == false)
			{
				outputInfo = player->pokemonList[activeCell]->getName() + " is already in battle!";
				action = input;
			}
			else if (activeCell < 6 && player->pokemonList[activeCell]->getFainted() == false)
			{
				player->currentlyBattling = player->pokemonList[activeCell];
				outputInfo = "GO! " + player->pokemonList[activeCell]->getName() + "!";
				action = pokemon;
			}
			else if (activeCell == 6)
			{
				action = back;
			}
			else
			{
				outputInfo = player->pokemonList[activeCell]->getName() + " has no energy left to battle!";
				action = input;
			}
		}
	}
	if (!app.window.isOpen())
	{
		throw - 1;
	}
	return action;
}

void ChoosePokemonScene::update()
{
	scene[8]->setString(outputInfo);
}

void ChoosePokemonScene::render()
{
	app.window.clear(app.defaultBackgroundColor);

	for (int i = 0; i < static_cast<int>(scene.size()); i++)
	{
		app.window.draw(*scene[i]);
		if (i < 6)
		{
			scene[i]->showHealth(player->pokemonList[i]);
		}
	}

	app.window.display();
}

ChoosePokemonScene::ChoosePokemonScene(Player& _player)
{
	player = &_player;
	initVariables();
}

int ChoosePokemonScene::playScene()
{
	outputInfo = "";
	scene[8]->setString(outputInfo);
	while (app.window.isOpen())
	{
		int pe = pollEvents();
		if (pe != 0)
		{
			update();
		}
		if (pe == 6)
		{
			render();
			sleep(seconds(0.5));
			return 6;
		}
		if (pe == 9) return 9;
		render();
	}
	if (!app.window.isOpen())
	{
		throw - 1;
	}
	return -1;
}


