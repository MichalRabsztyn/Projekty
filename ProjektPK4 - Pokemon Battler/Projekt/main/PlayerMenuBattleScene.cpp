#include "PlayerMenuBattleScene.h"
#include "App.h"
#include "Pokemon.h"

using namespace std;
using namespace sf;
PlayerMenuBattleScene::PlayerMenuBattleScene(std::shared_ptr<Pokemon> playersPokemon, std::shared_ptr<Pokemon> enemysPokemon)
{
	plainSky.setFillColor(Color(179, 230, 255));
	plainSky.setSize(Vector2f(app.resX, app.resY*0.65f));
	plainSky.setOutlineColor(Color::Black);
	plainSky.setOutlineThickness(5);

	playersHealthBox.setSize(Vector2f(app.resX*0.3f, app.resY*0.1f));
	playersHealthBox.setFillColor(Color(100, 100, 100));
	playersHealthBox.setOutlineColor(Color::Black);
	playersHealthBox.setOutlineThickness(2);

	enemysHealthBox = playersHealthBox;

	playersHealthBox.setPosition(plainSky.getSize() - playersHealthBox.getSize() - Vector2f(plainSky.getSize() * 0.03f));
	enemysHealthBox.setPosition(plainSky.getPosition() + Vector2f(plainSky.getSize() * 0.03f));

	playersHealthBarEmpty.setSize(Vector2f(playersHealthBox.getSize().x * 0.7f, playersHealthBox.getSize().y * 0.15f));
	playersHealthBarEmpty.setFillColor(Color(0, 129, 14));
	playersHealthBarEmpty.setOutlineThickness(1);
	playersHealthBarEmpty.setOutlineColor(Color(32, 32, 32));

	enemysHealthBarEmpty = playersHealthBarEmpty;

	playersHealthBarEmpty.setPosition(playersHealthBox.getPosition() + Vector2f(0.25f * playersHealthBox.getSize().x, 0.5f * playersHealthBox.getSize().y));
	enemysHealthBarEmpty.setPosition(enemysHealthBox.getPosition() + Vector2f(0.25f * enemysHealthBox.getSize().x, 0.5f * enemysHealthBox.getSize().y));

	playersHealthBar.setPosition(playersHealthBarEmpty.getPosition());
	playersHealthBar.setSize(Vector2f(playersHealthBarEmpty.getSize()));
	playersHealthBar.setFillColor(Color(0, 215, 31));

	enemysHealthBar.setPosition(enemysHealthBarEmpty.getPosition());
	enemysHealthBar.setSize(Vector2f(enemysHealthBarEmpty.getSize()));
	enemysHealthBar.setFillColor(Color(0, 215, 31));

	playersHealthText.setCharacterSize(18);
	playersHealthText.setFont(app.font);

	enemysHealthText = playersHealthText;
	playersPokemonName = playersHealthText;
	enemysPokemonName = playersHealthText;

	playersHealthText.setString(to_string(playersPokemon->getCurrentHP()) + "/" + to_string(playersPokemon->getHP()));
	playersHealthText.setPosition(playersHealthBarEmpty.getPosition() + playersHealthBarEmpty.getSize());
	FloatRect textRect = playersHealthText.getLocalBounds();
	playersHealthText.setOrigin(textRect.left + textRect.width, 0);
	
	enemysHealthText.setString(to_string(enemysPokemon->getCurrentHP()) + "/" + to_string(enemysPokemon->getHP()));
	enemysHealthText.setPosition(enemysHealthBarEmpty.getPosition() + enemysHealthBarEmpty.getSize());
			  textRect = enemysHealthText.getLocalBounds();
	enemysHealthText.setOrigin(textRect.left + textRect.width, 0);

	playersPokemonName.setString(playersPokemon->getName());
	playersPokemonName.setPosition(playersHealthBox.getPosition() + Vector2f(playersHealthBox.getSize()*0.01f));

	enemysPokemonName.setString(enemysPokemon->getName());
	enemysPokemonName.setPosition(enemysHealthBox.getPosition() + Vector2f(enemysHealthBox.getSize() * 0.01f));

	t_PlayersPokemon = playersPokemon->texture;
	t_EnemysPokemon = enemysPokemon->texture;
	
	s_playersPokemon.setTexture(t_PlayersPokemon);
	s_enemysPokemon.setTexture(t_EnemysPokemon);

	s_playersPokemon.setScale(4.0f, 4.0f);
	s_enemysPokemon.setScale(3.0f, 3.0f);

	s_playersPokemon.setTextureRect(sf::IntRect(t_PlayersPokemon.getSize().x, 0, -1*t_PlayersPokemon.getSize().x, t_PlayersPokemon.getSize().y));

	s_playersPokemon.setPosition(0, playersHealthBar.getPosition().y - t_PlayersPokemon.getSize().y * s_playersPokemon.getScale().y);
	s_enemysPokemon.setPosition(app.resX - t_EnemysPokemon.getSize().x * s_playersPokemon.getScale().x, 0);

	playersPlatform.setFillColor(Color(0, 153, 0));
	playersPlatform.setOutlineColor(Color::Green);
	playersPlatform.setOutlineThickness(10);
	playersPlatform.setScale(1, 0.5);

	enemysPlatform = playersPlatform;

	playersPlatform.setRadius(app.resX * 0.16f);
	playersPlatform.setPosition(0.f,s_playersPokemon.getPosition().y + t_PlayersPokemon.getSize().y * s_playersPokemon.getScale().y/1.7f);

	enemysPlatform.setRadius(app.resX * 0.12f);
	enemysPlatform.setPosition(s_enemysPokemon.getPosition().x, s_enemysPokemon.getPosition().y + t_EnemysPokemon.getSize().y * s_enemysPokemon.getScale().y / 1.7f);
}

void PlayerMenuBattleScene::update(std::shared_ptr < Pokemon> playersPokemon, std::shared_ptr < Pokemon> enemysPokemon)
{
	float playersHealthC = static_cast<float>(playersPokemon->getCurrentHP());
	float playersHealthM = static_cast<float>(playersPokemon->getHP());
	float playersHealth = static_cast<float>(playersHealthC / playersHealthM);

	float enemysHealthC = static_cast<float>(enemysPokemon->getCurrentHP());
	float enemysHealthM = static_cast<float>(enemysPokemon->getHP());
	float enemysHealth = static_cast<float>(enemysHealthC / enemysHealthM);

	playersHealthBar.setSize(Vector2f(playersHealthBarEmpty.getSize().x * playersHealth, playersHealthBarEmpty.getSize().y));
	enemysHealthBar.setSize(Vector2f(enemysHealthBarEmpty.getSize().x * enemysHealth, enemysHealthBarEmpty.getSize().y));

	playersHealthText.setString(to_string(playersPokemon->getCurrentHP()) + "/" + to_string(playersPokemon->getHP()));
	playersHealthText.setPosition(playersHealthBarEmpty.getPosition() + playersHealthBarEmpty.getSize());
	FloatRect textRect = playersHealthText.getLocalBounds();
	playersHealthText.setOrigin(textRect.left + textRect.width, 0.f);

	enemysHealthText.setString(to_string(enemysPokemon->getCurrentHP()) + "/" + to_string(enemysPokemon->getHP()));
	enemysHealthText.setPosition(enemysHealthBarEmpty.getPosition() + enemysHealthBarEmpty.getSize());
	textRect = enemysHealthText.getLocalBounds();
	enemysHealthText.setOrigin(textRect.left + textRect.width, 0);

	playersPokemonName.setString(playersPokemon->getName());
	playersPokemonName.setPosition(playersHealthBox.getPosition() + Vector2f(playersHealthBox.getSize() * 0.01f));

	enemysPokemonName.setString(enemysPokemon->getName());
	enemysPokemonName.setPosition(enemysHealthBox.getPosition() + Vector2f(enemysHealthBox.getSize() * 0.01f));

	t_PlayersPokemon = playersPokemon->texture;
	t_EnemysPokemon = enemysPokemon->texture;

	s_playersPokemon.setTexture(t_PlayersPokemon);
	s_enemysPokemon.setTexture(t_EnemysPokemon);
}

void PlayerMenuBattleScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	app.window.draw(plainSky);

	app.window.draw(playersHealthBox);
	app.window.draw(playersHealthBarEmpty);
	app.window.draw(playersHealthBar);

	app.window.draw(enemysHealthBox);
	app.window.draw(enemysHealthBarEmpty);
	app.window.draw(enemysHealthBar);

	app.window.draw(playersPokemonName);
	app.window.draw(playersHealthText);

	app.window.draw(enemysPokemonName);
	app.window.draw(enemysHealthText);

	app.window.draw(playersPlatform);
	app.window.draw(enemysPlatform);

	app.window.draw(s_playersPokemon);
	app.window.draw(s_enemysPokemon);
}

void PlayerMenuBattleScene::playPlayersAttack()
{
	Event event;
	Vector2f start_pos = s_playersPokemon.getPosition();
	RectangleShape emptyOutput;
	emptyOutput.setFillColor(app.defaultButtonColor);
	emptyOutput.setSize(Vector2f(app.resX, app.resY - plainSky.getSize().y));
	emptyOutput.setPosition(0, plainSky.getSize().y);
	

	while (app.window.isOpen())
	{
		while (s_playersPokemon.getPosition().x <= s_enemysPokemon.getPosition().x)
		{
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
			}

			s_playersPokemon.setPosition((s_playersPokemon.getPosition() + Vector2f((s_enemysPokemon.getPosition() - s_playersPokemon.getPosition()) * 0.2f) + Vector2f(1.0f, 1.0f)));
			
			app.window.clear();
			app.window.draw(emptyOutput);
			app.window.draw(*this);
			app.window.display();
		}
		while (s_playersPokemon.getPosition().x > start_pos.x)
		{
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
			}

			s_playersPokemon.setPosition((s_playersPokemon.getPosition() + Vector2f((start_pos - s_playersPokemon.getPosition()) * 0.2f)));
			app.window.draw(*this);
			app.window.display();
			if (s_playersPokemon.getPosition().x <= start_pos.x + 3.0f)
			{
				s_playersPokemon.setPosition(start_pos);
				break;
			}
		}
		break;
	}
}

void PlayerMenuBattleScene::playEnemysAttack()
{
	Event event;
	Vector2f start_pos = s_enemysPokemon.getPosition();
	RectangleShape emptyOutput;
	emptyOutput.setFillColor(app.defaultButtonColor);
	emptyOutput.setSize(Vector2f(app.resX, app.resY - plainSky.getSize().y));
	emptyOutput.setPosition(0, plainSky.getSize().y);

	while (app.window.isOpen())
	{
		while (s_enemysPokemon.getPosition().x >= s_playersPokemon.getPosition().x)
		{
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
			}
			s_enemysPokemon.setPosition((s_enemysPokemon.getPosition() + Vector2f((s_playersPokemon.getPosition() - s_enemysPokemon.getPosition()) * 0.2f) - Vector2f(1.0f, 1.0f)));

			app.window.clear();
			app.window.draw(emptyOutput);
			app.window.draw(*this);
			app.window.display();
		}

		while (s_enemysPokemon.getPosition().x < start_pos.x)
		{
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
			}
			s_enemysPokemon.setPosition((s_enemysPokemon.getPosition() + Vector2f((start_pos - s_enemysPokemon.getPosition()) * 0.2f)));
			app.window.clear();
			app.window.draw(emptyOutput);
			app.window.draw(*this);
			app.window.display();
			if (s_enemysPokemon.getPosition().x >= start_pos.x - 3.0f)
			{
				s_enemysPokemon.setPosition(start_pos);
				break;
			}
		}
		break;
	}
}
