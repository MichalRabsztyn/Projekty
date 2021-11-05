#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include "Pokemon.h"

class Pokemon;

class Entity
{
private: //variables
	bool canHeal;
	int faintedPokemons;
	int characterLvl;

public:  //variables
	std::vector<std::shared_ptr<Pokemon>> pokemonList;
	std::shared_ptr <Pokemon> currentlyBattling;
	
private: //methods
	void initVariables();

public:  //methods
	Entity();
	void readFromFile(int tmpList[]);
	void useHeal();
	bool getHeal();
	int getFaintedPokemons();
	void increaseFaintedPokemons();
	void resetFaintedPokemons();
	void resetHeal();
	void resetAllPP();
	std::shared_ptr <Pokemon> getCurrentlyBattling();
	void checkForEvolution();
	void characterLvlUp();
	void setCharacterLvl(int lvl);
	int getCharacterLvl();

};
#endif //ENTITY_H