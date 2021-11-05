#include "MainMenuScene.h"
#include "App.h"

#include <fstream>

void MainMenuScene::initVariables()
{
	activeCell = 0;
	saveExists = true;
	menu.push_back(std::make_unique<TextBoxMedium>("New Game", app.font, app.resX / 2.85f, app.resY * 3.5f / 6.f, 3.f, 1.2f));
	menu.push_back(std::make_unique<TextBoxMedium>("Continue", app.font, app.resX / 2.85f, app.resY * 4.35f / 6.f, 3.f, 1.2f));
	menu.push_back(std::make_unique<TextBoxMedium>("Exit", app.font, app.resX / 2.85f, app.resY * 5.2f / 6.f, 3.f, 1.2f));
	if (!t_logo.loadFromFile("assets/sprites/logo.png", sf::IntRect(0, 0, 800, 600)))
	{
		menu.push_back(std::make_unique<TextBoxMedium>("Pokemon Battler", app.font, app.resX / 3.f, app.resY * 1.f / 6.f, 3.f, 1.2f));
	}
	menu[0]->activate();
	s_logo.setTexture(t_logo);
}

void MainMenuScene::checkSaveFile()
{
	std::fstream file;
	file.open("save.sv");
	if(file.is_open())
	{
		int counter = 0;
		int check;
		while (file >> check)
		{
			counter++;
		}
		if (counter != 13)
		{
			saveExists = false;
		}
		file.close();
	}
	else
	{
		saveExists == false;
	}

	if(saveExists == false)
	{
		menu[1]->rect.setFillColor(sf::Color(100, 100, 100));
	}
}

int MainMenuScene::pollEvents()
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

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && activeCell != 2) {
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

int MainMenuScene::update()
{
	if (activeCell == 0) app.gameState = STATE::SETUP;
	else if (activeCell == 1)
	{
		if(saveExists == true)
		{
			app.gameState = STATE::CONTINUE;
		}
		else
		{
			return -1;
		}
	}
	else if (activeCell == 2) throw - 1;
	return activeCell;
}

void MainMenuScene::render()
{
	app.window.clear(app.defaultBackgroundColor);

	app.window.draw(s_logo);
	for (auto& e : menu)
	{
		app.window.draw(*e);
	}

	app.window.display();
}

MainMenuScene::MainMenuScene()
{
	initVariables();
	checkSaveFile();
}

int MainMenuScene::playScene()
{
	int action = -1;
	while (app.window.isOpen() && action == -1)
	{
		action = pollEvents();
		if (action > -1)
		{
			update();
		}
		render();
	}
	if(!app.window.isOpen())
	{
		throw - 1;
	}
	return action;
}
