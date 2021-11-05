#pragma once
#ifndef POKEMON_H
#define POKEMON_H

#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include <string>
#include <vector>
#include <memory>

#include "Move.h"

class Move;

class Pokemon
{
private: //variables
	std::string name;
	int base_hp, base_attack, base_defence, base_sp_attack, base_sp_defence, base_speed, type1, type2;
	int currentHp, hp, attack, defence, sp_attack, sp_defence, speed;
	int move1, move2, move3, move4, struggle = 1;
	bool fainted = false;
	int status = 0;
	int movesLeft;
	int movesTotal;
	int lvl = 1;
	int evoLvl;
	std::string nextEvoName;

public:  //variables
	std::vector<std::unique_ptr<Move>> moveList;
	sf::Texture texture;

private: //methods
	void calcStats();
	void setTexture();
	void addMove(int move1, int move2, int move3, int move4);

public:  //methods
	Pokemon(std::string _name, int _hp, int _attack, int _defence, int _sp_attack, int _sp_defence, int _speed, int _type1, int _type2, int _move1, int _move2, int _move3, int _move4, std::string _nextEvoName, int _evoLvl);

	std::string getName();
	int getCurrentHP();
	int getBaseHP();
	int getBaseAttack();
	int getBaseDefence();
	int getBaseSpAttack();
	int getBaseSpDefence();
	int getBaseSpeed();
	int getHP();
	int getAttack();
	int getDefence();
	int getSpAttack(); 
	int getSpDefence();
	int getSpeed();
	int getType1();
	int getType2();
	int getStatus();
	int getMovesLeft();
	int getLvl();
	int getEvoLvl();
	bool getFainted();
	void setFainted();
	void revive();
	void setHP(int damage);
	void setMovesLeft();
	void adjustLvl(int _lvl);
	void evolve();
	void resetPP();
};
#endif //POKEMON_H