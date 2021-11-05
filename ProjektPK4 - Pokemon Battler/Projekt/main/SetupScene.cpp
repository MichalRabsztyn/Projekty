#include "SetupScene.h"
#include "Player.h"
#include "Enemy.h"
#include "TextBoxLong.h"
#include "TextBoxSmall.h"
#include "PlayerMenuYesNo.h"

void SetupScene::initVariables()
{
	app.pokemonCount = loadPokemons();
	for (int i = 0; i < 6; i++)
	{
		indexList[i] = -1;
	}
	for (auto& e : cellList)
	{
		scene.push_back(e);
	}
	activeCell = 0;
	cellList[0]->activate();
	isReady = false;
	banner.reset(new TextBoxLong("Choose 6 pokemon for your team!", app.font, 0, 0, 1, 1));
	scene.push_back(banner);
}

int SetupScene::loadPokemons()
{
	int pokemonCount = 0;
	float posX=1.f;
	float posY=0.f;
	std::ifstream file("pokemon.dat");
	if (file.is_open())
	{
		std::string line;
		int blocksInCollumn = 0;
		while (getline(file, line) && pokemonCount < 75)
		{
			if (line.find('=') != std::string::npos)
			{
				break;
			}
			else
			{
				int strpos = line.find(" ");
				std::string input = line.substr(0, strpos);
				
				if (blocksInCollumn == 15)
				{
					posX += app.resX * 0.2f;
					posY = 0.f;
					blocksInCollumn = 0;
				}
				posY += app.resY * 0.0625f;
				blocksInCollumn++;
				cellList.push_back(std::make_shared<TextBoxSmall>(input, app.font, posX, posY, 1.f, 1.f));
				pokemonCount++;
			}
		}
		file.close();
		std::cout << pokemonCount << std::endl;
	}
	return pokemonCount;
}

void SetupScene::pollEvents()
{
	while (app.window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			app.gameState = STATE::EXIT;
			app.window.close();
			return;
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			app.gameState = STATE::EXIT;
			app.window.close();
			return;
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && activeCell != cellList.size() - 1) {
			cellList[activeCell]->deactivate();
			activeCell++;
			cellList[activeCell]->activate();
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && activeCell != 0) {
			cellList[activeCell]->deactivate();
			activeCell--;
			cellList[activeCell]->activate();
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left && (activeCell - 15 >= 0)) {
			cellList[activeCell]->deactivate();
			activeCell -= 15;
			cellList[activeCell]->activate();
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right && (static_cast<unsigned int>(activeCell + 15) < cellList.size())) {
			cellList[activeCell]->deactivate();
			activeCell += 15;
			cellList[activeCell]->activate();
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
			bool contains = false;
			for (int i = 0; i < 6; i++)
			{
				if (indexList[i] == activeCell)
				{
					indexList[i] = -1;
					cellList[activeCell]->deselect();
					contains = true;
					pokemonChosen--;
					break;
				}
			}
			if (contains == false)
			{
				for (int i = 0; i < 6; i++)
				{
					if (indexList[i] == -1)
					{
						pokemonChosen++;
						indexList[i] = activeCell;
						cellList[activeCell]->select();
						if (pokemonChosen == 6)
						{
							isReady = true;
						}
						break;
					}
				}
			}
		}
	}
	if (!app.window.isOpen())
	{
		throw - 1;
	}
}

void SetupScene::update(Player& player, Enemy &enemy)
{
	if (isReady == true)
	{
		PlayerMenuYesNo pmyn(scene, app.resX / 2 - app.resX * 0.12f, app.resY / 2.0f, "Are you ready?");
		isReady = pmyn.yesNo();
	}
	if (isReady == true)
	{
		player.readFromFile(indexList);
		enemy.enemySetup();
		app.gameState = STATE::BATTLE;
	}
}

void SetupScene::render()
{
	app.window.clear(app.defaultBackgroundColor);

	for (auto& e : cellList)
	{
		app.window.draw(*e);
	}
	app.window.draw(*banner);

	app.window.display();
}

SetupScene::SetupScene()
{
	initVariables();
}

void SetupScene::playScene(Player& _player, Enemy& _enemy)
{
	while (app.window.isOpen() && app.gameState==STATE::SETUP)
	{
		pollEvents();
		update(_player, _enemy);
		render();
	}
}

