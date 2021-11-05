#include "WinLooseScene.h"
#include "App.h"
#include "Player.h"
#include "Enemy.h"
#include "Pokemon.h"

void WinLooseScene::initVariables()
{
	activeCell = 0;
	bannerText = "";
	saveName = "save.sv";
	menu.push_back(std::make_unique<TextBoxMedium>("Continue", app.font, app.resX / 2.85f, app.resY * 3.f / 6.f, 3.f, 1.2f));
	menu.push_back(std::make_unique<TextBoxMedium>("Exit to main menu", app.font, app.resX / 2.85f, app.resY * 4.f / 6.f, 3.f, 1.2f));
	menu.push_back(std::make_unique<TextBoxMedium>("", app.font, app.resX / 5.f, app.resY * 1.f / 6.f, 6.f, 2.f));
	menu[0]->activate();
}

int WinLooseScene::pollEvents()
{
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

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && activeCell != 1) {
			menu[activeCell]->deactivate();
			activeCell++;
			menu[activeCell]->activate();
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && activeCell != 0) {
			menu[activeCell]->deactivate();
			activeCell--;
			menu[activeCell]->activate();
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
			return activeCell;
		}
	}
	if (!app.window.isOpen())
	{
		throw - 1;
	}
	return -1;
}

void WinLooseScene::update(int action, Player& player, Enemy& enemy)
{
	if (action == 0)
	{
		player.healAll();
		enemy.enemySetup();
		autosave(player, enemy);
		player.resetFaintedPokemons();
		enemy.resetFaintedPokemons();
		player.resetHeal();
		enemy.resetHeal();
		player.resetAllPP();
		enemy.resetAllPP();
		app.gameState = STATE::BATTLE;
	}

	if (action == 1)
	{
		enemy.enemySetup();
		autosave(player, enemy);
		player.resetFaintedPokemons();
		enemy.resetFaintedPokemons();
		app.gameState = STATE::MAIN_MENU;
	}	
}

void WinLooseScene::render()
{
	app.window.clear(app.defaultBackgroundColor);

	for (auto& e : menu)
	{
		app.window.draw(*e);
	}
	
	app.window.display();
}

void WinLooseScene::autosave(Player& player, Enemy& enemy)
{
	app.Debug("saving...");
	std::fstream file;
	std::vector<std::string> nameList;
	int indexList[12] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
	for (auto& e : player.pokemonList)
	{
		nameList.push_back(e->getName());
	}
	for (auto& e : enemy.pokemonList)
	{
		nameList.push_back(e->getName());
	}

	file.open("pokemon.dat");
	std::string line;
	for (int i = 0; i < 12; i++)
	{
		int iterFile = 0;
		while (getline(file, line))
		{
			int strpos = line.find(" ");
			std::string input = line.substr(0, strpos);
			if (input == nameList[i])
			{
				indexList[i] = iterFile;
				break;
			}
			iterFile++;
		}
		file.clear();
		file.seekg(0);
	}
	file.close();

	file.open(saveName, std::ios::out | std::ios::trunc);
	file.close();
	file.open(saveName, std::ios::in | std::ios::out | std::ios::trunc);
	file << player.getCharacterLvl() <<"\n";
	for (auto& e : indexList)
	{
		file << e << "\n";
	}
	file.close();
}

WinLooseScene::WinLooseScene()
{
	initVariables();
}

void WinLooseScene::playScene(std::string _bannerText, Player& player, Enemy& enemy)
{
	menu[2]->setString(_bannerText);
	int action = -1;
	while (app.window.isOpen() && action == -1)
	{
		action = pollEvents();
		update(action, player, enemy);
		render();
	}
}
