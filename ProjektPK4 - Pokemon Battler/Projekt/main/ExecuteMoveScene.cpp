#include "ExecuteMoveScene.h"
#include "Pokemon.h"
#include "Move.h"

void ExecuteMoveScene::calculateDamage()
{
	int accuracyCheck = rand() % 100 + 1;
	if (accuracyCheck <= attacking->moveList[moveID]->getAccuracy())
	{
		int A, D, power = attacking->moveList[moveID]->getPower();
		if (attacking->moveList[moveID]->getCategory() == 0)
		{
			A = attacking->getAttack();
			D = defending->getDefence();
		}
		else
		{
			A = attacking->getSpAttack();
			D = defending->getSpDefence();
		}

		if (moveID == 4)
		{
			if (playersTurn == false)
			{
				moveInfo += "The opposing ";
			}
			moveInfo += attacking->getName() + " has no moves left!";
			//outputQueue.push(std::make_unique<PlayerMenuOutput>());
		}
		moveInfo = "";
	}

}

	void ExecuteMoveScene::playScene(int moveID, Pokemon & attacking, Pokemon & defending, PlayerMenuBattleScene & pmBs, bool playersTurn)
	{

	}
