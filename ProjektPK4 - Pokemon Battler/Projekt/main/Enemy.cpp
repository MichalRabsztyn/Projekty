#include "Enemy.h"
#include "Pokemon.h"
#include "Move.h"
#include "App.h"

using namespace std;

	///// PRZECIWNIK WYSY�A NOWEGO POKEMONA ///// 
void Enemy::nextPokemon()
{
	///// SZUKAJ PIERWSZEGO ZDOLNEGO DO WALKI POKEMONA ///// 
	for (int i = 0; i < 6; i++)
	{
		if (pokemonList[i]->getFainted() == false)
		{
			currentlyBattling = pokemonList[i];
			return;
		}
	}
}

	///// PRZECIWNIK WYBIERA AKCJ� /////
int Enemy::enemyAction()
{
	///// NUMERACJA AKCJI ZGODNA Z ZADEKLAROWAN� W BATTLESYSTEM /////
	enum ACTIONS { STRUGGLE = 4, FIGHT, POKEMON, HEAL};

	///// JE�ELI POKEMON PRZECIWNIKA MA NISKI POZIOM ZDROWIA, SPR�BUJE GO WYLECZY� /////
	if ((currentlyBattling->getHP() * 0.2 > currentlyBattling->getCurrentHP()) && getHeal() == true)
	{
		return HEAL;
	}
	///// JE�ELI POKEMON MA WI�CEJ NI� 0 RUCH�W, PRZEJDZIE DO WYBORU RUCHU /////
	if (currentlyBattling->getMovesLeft() > 0)
	{
		return FIGHT;
	}
	///// JE�ELI POKEMON NIE MA WI�CEJ RUCH�W, U�YJE STRUGGLE /////
	else
	{
		return STRUGGLE;
	}
}

	///// PPRZECIWNIK WYBIERA RUCH /////
int Enemy::enemyAttack()
{
	///// DOP�KI NIE ZNAJDZIE RUCHU, KT�RY MA WI�CEJ NI� 0 PP, LOSUJE RUCH /////
	while (1)
	{
		int attackID = rand() % 4;
		if (currentlyBattling->moveList[attackID]->getCurrentPP() > 0)
		{
			return attackID;
		}
	}	
}

void Enemy::enemySetup()
{
	int indexList[6];

	for (int i = 0; i < 6; i++)
	{
		indexList[i] = (rand() % app.pokemonCount); // +1);
	}

	readFromFile(indexList);
}
	
