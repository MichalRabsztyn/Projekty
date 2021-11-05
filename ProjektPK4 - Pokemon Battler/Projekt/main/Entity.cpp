#include "Entity.h"
#include "Pokemon.h"

using namespace std;

void Entity::initVariables()
{
	canHeal = true;
	currentlyBattling = nullptr;
	faintedPokemons = 0;
	characterLvl = 1;
}

Entity::Entity()
{
	initVariables();
}

void Entity::readFromFile(int tmpList[])
{
	if (pokemonList.size() > 0)
	{
		pokemonList.clear();
	}

	ifstream file("pokemon.dat");
	if (file.is_open())
	{
		string name, nextEvoName;
		int hp, attack, defence, sp_attack, sp_defence, speed, type1, type2, move1, move2, move3, move4, evoLvl;
		
		for (int placeInParty = 0; placeInParty < 6; placeInParty++)
		{
			int line = 0;
			while(file >> name >> hp >> attack >> defence >> sp_attack >> sp_defence >> speed >> type1 >> type2 >> move1 >> move2 >> move3 >> move4 >> nextEvoName >> evoLvl)
			{
				if (line == tmpList[placeInParty])
				{
					pokemonList.push_back(make_shared<Pokemon>(name, hp, attack, defence, sp_attack, sp_defence, speed, type1, type2, move1, move2, move3, move4, nextEvoName, evoLvl));
					break;
				}
				line++;
			}
			file.clear();
			file.seekg(0);
		}

		file.close();
	}
}

void Entity::useHeal()
{
	int dif = currentlyBattling->getHP() - currentlyBattling->getCurrentHP();
	if (dif >= 50)
	{
		currentlyBattling->setHP(-50); //setHP() domyœlnie przyjmuje wartoœci dodatnie jako obra¿enia - (-50) oznacza odejmij 50 obra¿eñ, czyli dodaj 50 hp
	}
	else
	{
		currentlyBattling->setHP(-1 * dif);
	}
	canHeal = false;
}

bool Entity::getHeal()
{
	return canHeal;
}

std::shared_ptr <Pokemon> Entity::getCurrentlyBattling()
{
	return currentlyBattling;
}

int Entity::getFaintedPokemons()
{
	return faintedPokemons;
}

void Entity::resetFaintedPokemons()
{
	faintedPokemons = 0;
}

void Entity::resetHeal()
{
	canHeal = true;
}

void Entity::increaseFaintedPokemons()
{
	faintedPokemons++;
}

void Entity::checkForEvolution()
{
	for (int i = 0; i < 6; i++)
	{
		pokemonList[i]->adjustLvl(characterLvl);
		
		if (pokemonList[i]->getEvoLvl() <= characterLvl && pokemonList[i]->getEvoLvl() != 0)
		{
			pokemonList[i]->evolve();
		}
	}
}

void Entity::resetAllPP()
{
	for (auto& e : pokemonList)
	{
		e->resetPP();
	}
}

void Entity::characterLvlUp()
{
	characterLvl++;
}

void Entity::setCharacterLvl(int lvl)
{
	characterLvl = lvl;
}

int Entity::getCharacterLvl()
{
	return characterLvl;
}


