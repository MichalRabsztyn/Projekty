#include "ChooseActionScene.h"
#include "App.h"
#include "Player.h"
#include "PlayerMenuBattleScene.h"
#include "PlayerMenuActions.h"
#include "Pokemon.h"

void ChooseActionScene::initVariables()
{
	activeCell = 0;
	menuActions.reset(new PlayerMenuActions(r,g,b, *player));
	menuActions->activate(0);
}

int ChooseActionScene::pollEvents()
{
	enum ACTIONS { STRUGGLE = 4, FIGHT, POKEMON, HEAL, OPTIONS };
	sf::Event event;
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
			menuActions->deactivate(activeCell);
			activeCell += 2;
			menuActions->activate(activeCell);
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && (activeCell == 2 || activeCell == 3)) {
			menuActions->deactivate(activeCell);
			activeCell -= 2;
			menuActions->activate(activeCell);
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left && (activeCell == 1 || activeCell == 3)) {
			menuActions->deactivate(activeCell);
			activeCell--;
			menuActions->activate(activeCell);
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right && (activeCell == 0 || activeCell == 2)) {
			menuActions->deactivate(activeCell);
			activeCell++;
			menuActions->activate(activeCell);
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {

			if (activeCell == 0 && player->currentlyBattling->getMovesLeft()< 1)
			{
				return STRUGGLE;
			}
			else if (activeCell == 2 && player->getHeal() == false)
			{
				menuActions->tiles[2]->setFillColor(Color(127, 32, 0));
			}
			else
			{
				return activeCell + 5;
			}
		}
	}
	if (!app.window.isOpen())
	{
		throw - 1;
	}
	return -1;
}

void ChooseActionScene::update()
{
	Color t(r - 20, g - 20, b - 20);
	menuActions->tiles[2]->setFillColor(app.colorShift(menuActions->tiles[2]->getFillColor(), t, 0.03f));
}

void ChooseActionScene::render()
{
	app.window.clear(Color(100, 150, 200));
	battleScene->draw(app.window, RenderStates::Default);
	menuActions->draw(app.window, RenderStates::Default);
	app.window.display();
}

ChooseActionScene::ChooseActionScene(Player& _player, PlayerMenuBattleScene& _pmbs)
{
	player = &_player;
	battleScene = &_pmbs;
	initVariables();
}

int ChooseActionScene::playScene()
{
	int action = -1;
	menuActions->healStatus(*player);
	while (app.window.isOpen() && action == -1)
	{
		action = pollEvents();
		update();
		render();
	}
	return action;
}
