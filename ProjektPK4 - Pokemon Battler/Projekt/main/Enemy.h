#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity
{
private: //variables

public:  //variables

private: //methods

public:  //methods
	Enemy() : Entity() {}
	void nextPokemon();
	int enemyAction();
	int enemyAttack();
	void enemySetup();
};
#endif //ENEMY_H

