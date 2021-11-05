#include "PlayerMenuYesNo.h"
#include "TextBoxMedium.h"
#include "App.h"

using namespace sf;
PlayerMenuYesNo::PlayerMenuYesNo(std::vector<std::shared_ptr<Drawable>> _scene, float posX, float posY, std::string _text)
{
	s_scene = _scene;
	rect.setFillColor(Color(170, 170, 170));
	rect.setSize(Vector2f(app.resX * 0.34f, app.resY * 0.4f));
	rect.setPosition(Vector2f(posX - 0.05f * app.resX, posY * 0.7f));
	rect.setOutlineThickness(2.0f);
	rect.setOutlineColor(Color::Black);

	text.setCharacterSize(18);
	text.setFont(app.font);
	text.setString(_text);
	text.setFillColor(Color::Black);
	text.setPosition(rect.getPosition() + Vector2f(rect.getSize().x / 2.0f, rect.getSize().y * 0.18f));
	FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	s_scene.push_back(std::make_shared<RectangleShape>(rect));
	s_scene.push_back(std::make_shared<Text>(text));

	////////////////////////////// INICJALIZACJA OBIEKTÓW PRZYCISKÓW //////////////////////////////
	s_yes_button = std::make_shared< TextBoxMedium > ("YES", app.font, posX, posY, 1.f, 1.f);
	s_no_button = std::make_shared< TextBoxMedium > ("NO", app.font, posX + s_yes_button->rect.getSize().x + 0.04f * app.resX, posY, 1.f, 1.f);
	s_yes_button->activate();

	s_scene.push_back(s_yes_button);
	s_scene.push_back(s_no_button);
}

bool PlayerMenuYesNo::yesNo()
{
	////////////////////////////// INICJALIZACJA WARTOŒCI WSTÊPNYCH //////////////////////////////
	Event event;
	bool choice = true;
	
	////////////////////////////////// OPERACJE NA OKNIE YES/NO //////////////////////////////////
	while (app.window.isOpen())
	{
		while (app.window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				app.gameState = STATE::EXIT;
				app.window.close();
				return true;
			}

			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				app.gameState = STATE::EXIT;
				app.window.close();
				return true;
			}

			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
				s_no_button->deactivate();
				s_yes_button->activate();
				choice = true;
			}

			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
				s_yes_button->deactivate();
				s_no_button->activate();
				choice = false;
			}

			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
				return choice;
			}
		}

		////////////////////////////////// WYŒWIETLANIE OKNA YES/NO /////////////////////////////////
		app.window.clear(app.defaultBackgroundColor);
		
		for (auto& e : s_scene)
		{
			app.window.draw(*e);
		}

		app.window.display();
	}
	return true;
}
