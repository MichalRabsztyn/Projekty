#include "Pokemon.h"
#include "App.h"
#include <iostream>
#include <fstream>
#include <vector>
#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include <regex>

#include "Move.h"

using namespace std;

Pokemon::Pokemon(std::string _name, int _hp, int _attack, int _defence, int _sp_attack, int _sp_defence, int _speed, int _type1, int _type2, int _move1, int _move2, int _move3, int _move4, std::string _nextEvoName, int _evoLvl) :
	name(_name), base_hp(_hp), base_attack(_attack), base_defence(_defence), base_sp_attack(_sp_attack), base_sp_defence(_sp_defence), base_speed(_speed), type1(_type1), type2(_type2), move1(_move1), move2(_move2), move3(_move3), move4(_move4), nextEvoName(_nextEvoName), evoLvl(_evoLvl)
{
	calcStats();
	currentHp = hp;
	addMove(move1, move2, move3, move4);
	movesLeft = moveList[0]->getPP() + moveList[1]->getPP() + moveList[2]->getPP() + moveList[3]->getPP();
	setTexture();
}

std::string Pokemon::getName()
{
	return name;
}

int Pokemon::getCurrentHP()
{
	return currentHp;
}

int Pokemon::getBaseHP()
{
	return base_hp;
}

int Pokemon::getBaseAttack()
{
	return base_attack;
}

int Pokemon::getBaseDefence()
{
	return base_defence;
}

int Pokemon::getBaseSpAttack()
{
	return base_sp_attack;
}

int Pokemon::getBaseSpDefence()
{
	return base_sp_defence;
} 

int Pokemon::getBaseSpeed()
{
	return base_speed;
}

int Pokemon::getHP()
{
	return hp;
}

int Pokemon::getAttack()
{
	return attack;
}

int Pokemon::getDefence()
{
	return defence;
}

int Pokemon::getSpAttack()
{
	return sp_attack;
}

int Pokemon::getSpDefence()
{
	return sp_defence;
}

int Pokemon::getSpeed()
{
	return speed;
}

int Pokemon::getType1()
{
	return type1;
}

int Pokemon::getType2()
{
	return type2;
}

int Pokemon::getStatus()
{
	return status;
}

int Pokemon::getMovesLeft()
{
	return movesLeft;
}

int Pokemon::getLvl()
{
	return lvl;
}

int Pokemon::getEvoLvl()
{
	return evoLvl;
}

bool Pokemon::getFainted()
{
	return fainted;
}

void Pokemon::setFainted()
{
	fainted = true;
}

void Pokemon::revive()
{
	this->fainted = false;
}

void Pokemon::addMove(int move1, int move2, int move3, int move4)
{
	int movesFound = 0;
	ifstream file("moves.dat");
	if (file.is_open())
	{
		int iter = 0;
		string name, name2;
		int pp, accuracy, power, status, type, category;
		while (file >> name >> name2 >> pp >> accuracy >> power >> status >> type >> category && movesFound <4)
		{
			iter++;
			if (name2 != "_")
			{
				name = name + " " + name2;
			}
			if (iter == move1 || iter == move2 || iter == move3 || iter == move4)
			{
				this->moveList.push_back(make_unique <Move>(name, pp, accuracy, power, status, type, category));
				movesFound++;
			}
		}
		file.clear();
		file.seekg(0);
		file.close();
	}
	if (movesFound < 4)
	{
		for (int i = 0; i < (4 - movesFound); i++)
		{
			moveList.push_back(make_unique < Move>("tackle", 35, 100, 40, 0, 13, 0));
		}
	}
	moveList.push_back(make_unique < Move>("struggle", 1, 100, 50, 0, 0, 0));
}

void Pokemon::setHP(int damage)
{
	if (damage > currentHp) currentHp = 0;
	else
	{
		currentHp -= damage;
		if (currentHp > hp)
		{
			currentHp = hp;
		}
	}
}

void Pokemon::setMovesLeft()
{
	movesLeft--;
}

void Pokemon::adjustLvl(int _lvl)
{
	lvl = _lvl;
}

void Pokemon::evolve()
{
	string t_name, t_nextEvoName;

	int t_hp, t_attack, t_defence, t_sp_attack, t_sp_defence,t_speed,
		t_type1, t_type2, t_move1, t_move2, t_move3, t_move4,
		t_evoLvl;

	std::ifstream file("pokemons.dat");
	if (file.is_open())
	{
		std::string line;
		while (file >> t_name >> t_hp >> t_attack >> t_defence >> t_sp_attack >> t_sp_defence >> t_speed >> t_type1 >> t_type2 >> t_move1 >> t_move2 >> t_move3 >> t_move4 >> t_nextEvoName >> t_evoLvl)
		{
			if (t_name == nextEvoName)
			{
				name = t_name, hp = t_hp, attack = t_attack, defence = t_defence, sp_attack = t_sp_attack, sp_defence = t_sp_defence,speed = t_speed,
					type1 = t_type1, type2 = t_type2, move1 = t_move1, move2 = t_move2, move3 = t_move3, move4 = t_move4,
						nextEvoName = t_nextEvoName, evoLvl = t_evoLvl;
				setTexture();
				calcStats();
				break;
			}
		}
		file.close();
	}
}

void Pokemon::resetPP()
{
	for (auto &e : moveList)
	{
		e->resetPP();
	}
	movesLeft = moveList[0]->getPP() + moveList[1]->getPP() + moveList[2]->getPP() + moveList[3]->getPP();
}

void Pokemon::calcStats()
{
	hp = (((2 * base_hp) * lvl)/100) + lvl + 10;
	attack = (((2 * base_attack) * lvl) / 100) + 5;
	defence = (((2 * base_defence) * lvl) / 100) + 5;
	sp_attack = (((2 * base_sp_attack) * lvl) / 100) + 5;
	sp_defence = (((2 * base_sp_defence) * lvl) / 100) + 5;
	speed = (((2 * base_speed) * lvl) / 100) + 5;
}

void Pokemon::setTexture()
{
	string path = "assets/sprites/placeholder.png";
	regex placeHolder ("placeholder");
	path = regex_replace(path, placeHolder, name);
	texture.loadFromFile(path);
}