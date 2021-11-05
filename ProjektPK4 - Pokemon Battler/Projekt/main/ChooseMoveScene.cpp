#include "ChooseMoveScene.h"
#include "PlayerMenuMoves.h"
#include "PlayerMenuBattleScene.h"
#include "Player.h"
#include "Pokemon.h"
#include "Move.h"
#include "App.h"

void ChooseMoveScene::initVariables()
{
	activeCell = 0;
	menuMoves.reset(new PlayerMenuMoves(r,g,b, *player->currentlyBattling));
	menuMoves->activate(0);
}

int ChooseMoveScene::pollEvents()
{
	Event event;
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

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && (activeCell == 0 || activeCell == 1)) {
			menuMoves->deactivate(activeCell);
			activeCell += 2;
			menuMoves->activate(activeCell);
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && (activeCell == 2 || activeCell == 3)) {
			menuMoves->deactivate(activeCell);
			activeCell -= 2;
			menuMoves->activate(activeCell);
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left && (activeCell == 1 || activeCell == 3 || activeCell == 4)) {
			menuMoves->deactivate(activeCell);
			activeCell--;
			menuMoves->activate(activeCell);
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right && (activeCell == 0 || activeCell == 2 || activeCell == 3)) {
			menuMoves->deactivate(activeCell);
			activeCell++;
			menuMoves->activate(activeCell);
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
			
			if (activeCell == 4)
			{
				return activeCell + 5;
			}
			return activeCell;
		}
	}
	if (!app.window.isOpen())
	{
		throw - 1;
	}
	return -1;
}

int ChooseMoveScene::update(int action)
{
	if (player->currentlyBattling->moveList[action]->getCurrentPP() <= 0)
	{
		return -1;
	}
	return action;
}

void ChooseMoveScene::render()
{
	app.window.clear(app.defaultBackgroundColor);

	battleScene->draw(app.window, RenderStates::Default);
	menuMoves->draw(app.window, RenderStates::Default);

	app.window.display();
}

ChooseMoveScene::ChooseMoveScene(Player& _player, PlayerMenuBattleScene& _pmbs)
{
	player = &_player;
	battleScene = &_pmbs;
	initVariables();
}

int ChooseMoveScene::playScene()
{
	menuMoves.reset(new PlayerMenuMoves(r, g, b, *player->currentlyBattling));
	menuMoves->activate(0);
	activeCell = 0;

	int action = -1;
	while (app.window.isOpen() && action == -1)
	{
		action = pollEvents();
		if (action > -1 && action <4)
		{
			action = update(action);
		}
		render();
	}
	return action;
}