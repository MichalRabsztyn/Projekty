#pragma once
#ifndef PLAYER_MENU_BATTLE_SCENE_H
#define PLAYER_MENU_BATTLE_SCENE_H

#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include <memory>

#include "Pokemon.h"

class Pokemon;

class PlayerMenuBattleScene : public sf::Drawable
{
private: //variables
	sf::RectangleShape plainSky,
		playersHealthBarEmpty, playersHealthBox, playersHealthBar,
		enemysHealthBarEmpty, enemysHealthBox, enemysHealthBar;
	sf::CircleShape playersPlatform, enemysPlatform;
	sf::Text playersPokemonName, playersHealthText,
		enemysPokemonName, enemysHealthText;
	sf::Texture t_PlayersPokemon, t_EnemysPokemon;
	sf::Sprite s_playersPokemon, s_enemysPokemon;

public:  //variables

private: //methods

public:  //methods
	PlayerMenuBattleScene(std::shared_ptr < Pokemon> playersPokemon, std::shared_ptr < Pokemon> enemysPokemon);

	void update(std::shared_ptr < Pokemon> playersPokemon, std::shared_ptr < Pokemon> enemysPokemon);
	void playPlayersAttack();
	void playEnemysAttack();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
};
#endif //PLAYER_MENU_BATTLE_SCENE_H