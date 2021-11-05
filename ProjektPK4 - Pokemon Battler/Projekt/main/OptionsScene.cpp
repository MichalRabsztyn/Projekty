#include "OptionsScene.h"
#include "App.h"
#include "Player.h"
#include "Pokemon.h"
#include "Enemy.h"
#include "TextBoxMedium.h"

void OptionsScene::initVariables()
{
	activeCell = 0;
	saveName = "save.sv";
	info = "";
	menu.push_back(std::make_unique<TextBoxMedium>("Save", app.font, app.resX / 2.85f , app.resY * 1.f / 6.f, 3.f, 1.2f));
	menu.push_back(std::make_unique<TextBoxMedium>("Save & exit", app.font, app.resX / 2.85f, app.resY * 2.f / 6.f, 3.f, 1.2f));
	menu.push_back(std::make_unique<TextBoxMedium>("Exit", app.font, app.resX / 2.85f, app.resY * 3.f / 6.f, 3.f, 1.2f));
	menu.push_back(std::make_unique<TextBoxMedium>("Back", app.font, app.resX / 2.85f, app.resY * 4.f / 6.f, 3.f, 1.2f));
	menu.push_back(std::make_unique<TextBoxMedium>("", app.font, 0.f, 0.f, 10.f, 1.2f));

	menu[0]->activate();
}

int OptionsScene::pollEvents()
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

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && (activeCell != 3)) {
			menu[activeCell]->deactivate();
			activeCell++;
			menu[activeCell]->activate();
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && (activeCell != 0)) {
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

void OptionsScene::update(int action)
{
	if (action == 0 || action == 1)
	{
		info = "saving...";
		menu[4]->setString(info);
		save();
	}
	if (action == 1 || action == 2) throw - 1;
}

void OptionsScene::render()
{
	app.window.clear(app.defaultBackgroundColor);

	for (auto& e : menu)
	{
		app.window.draw(*e);
	}

	app.window.display();
}

void OptionsScene::save()
{
	app.Debug("saving...");
	std::fstream file;
	std::vector<std::string> nameList;
	int indexList[12] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	for (auto& e : player->pokemonList)
	{
		nameList.push_back(e->getName());
	}
	for (auto& e : enemy->pokemonList)
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
	file << player->getCharacterLvl() << "\n";
	for (auto& e : indexList)
	{
		file << e << "\n";
	}
	file.close();
}

OptionsScene::OptionsScene(Player& _player, Enemy& _enemy)
{
	player = &_player;
	enemy = &_enemy;
	initVariables();
}

void OptionsScene::playScene()
{
	int action = -1;
	while (app.window.isOpen() && action == -1)
	{
		action = pollEvents();
		if (action > -1)
		{
			if (action == 3)
			{
				return;
			}
			update(action);
			if (action == 0)
			{
				action = -1;
			}
		}
		render();
		if (info != "")
		{
			sleep(seconds(1));
			info = "";
			menu[4]->setString(info);
		}
	}
}
