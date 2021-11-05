#include "GameSystem.h"
#include "App.h"
#include "Enemy.h"

#include "TextBoxSmall.h"
#include "TextBoxLong.h"
#include "PlayerMenu.h"
#include "PlayerMenuOutput.h"
#include "PlayerMenuYesNo.h"
#include "SetupScene.h"
#include "MainMenuScene.h"
#include "OptionsScene.h"
#include "ChooseMoveScene.h"
#include "ChoosePokemonScene.h"
#include "ChooseActionScene.h"
#include "PlayerMenuBattleScene.h"
#include "WinLooseScene.h"
#include "Move.h"
#include "Player.h"
#include "Entity.h"
#include "Pokemon.h"
#include <regex>

using namespace std;

enum MOVES {MOVE1, MOVE2, MOVE3, MOVE4, STRUGGLE};
enum ACTIONS {FIGHT=5, POKEMON, HEAL, OPTIONS};

GameSystem::GameSystem()
{
	checkFiles();
}

void GameSystem::checkFiles()
{
	Font font;
	if (!font.loadFromFile(app.fontData))
	{
		throw 0;
	}
	else
	{
		app.font = font;
	}

	ifstream file(app.pokemonsData);
	if (!file.is_open())
	{
		throw 1;
	}
	else
	{	
		int check = 0;
		bool evos = false;
		string line;
		while (getline(file, line))
		{
			if (!(line.find('=') != std::string::npos))
			{
				if (evos == false)
				{
					check++;
				}
				int strpos = line.find(" ");
				string input = line.substr(0, strpos);
				Texture texture;

				string path = "assets/sprites/placeholder.png";
				regex placeHolder("placeholder");
				path = regex_replace(path, placeHolder, input);
				if (!texture.loadFromFile(path)) throw 2;
			
			}
			else
			{
				evos = true;
			}
		}
		file.close();
		if (check < 6) throw 5;
	}

	file.open(app.movesData);
	if (!file.is_open())
	{
		throw 3;
	}
	else
	{
		int check = 0;
		string line;
		while (getline(file, line))
		{
			check++;
		}
		file.close();
		if (check < 1)
			throw 5;
	}
}

void GameSystem::gameLoop()
{
	Player player;
	Enemy enemy;
	MainMenuScene mainMenu;
	while (app.window.isOpen())
	{
		cout << "State code: " << static_cast<int>(app.gameState) << endl;
		switch (app.gameState) {
			case STATE::MAIN_MENU:
			{
				mainMenu.playScene();
				break;
			}
			case STATE::SETUP:
			{
				SetupScene setupScene;
				setupScene.playScene(player, enemy);
				break;
			}
			case STATE::CONTINUE:
			{
				continueGame(player, enemy);
				break;
			}
			case STATE::BATTLE:
			{
				battle(player, enemy);
				break;
			}
			case STATE::EXIT:
			{
				throw - 1;
			}
			default:
			{
				break;
			}
		}
	}
}

int GameSystem::battle(Player& player, Enemy& enemy)
{
	enemy.checkForEvolution();
	player.checkForEvolution();

	ChoosePokemonScene choosePokemon(player);
	choosePokemon.playScene();
	enemy.nextPokemon();

	PlayerMenuOutput pmO(200, 200, 200);
	PlayerMenuBattleScene pmB(player.getCurrentlyBattling(), enemy.getCurrentlyBattling());
	OptionsScene options(player, enemy);
	ChooseActionScene chooseAction(player, pmB);
	ChooseMoveScene choooseMove(player, pmB);

	while (app.window.isOpen())
	{
		if (enemy.getFaintedPokemons() <= 6 && player.getFaintedPokemons() <= 6)
		{
			int playersAction = player.playersTurn(chooseAction, choosePokemon, choooseMove, options);
			int enemysAction = enemy.enemyAction();
			
			bool playersTurn = true;
			bool enemysTurn = true;
			int playersMoveID = 0;

			if (playersAction == POKEMON)
			{
				pmB.update(player.getCurrentlyBattling(), enemy.getCurrentlyBattling());
				playersTurn = false;
			}
			
			
			else if (playersAction <= 4)
			{
				playersMoveID = playersAction;
			}

			else if (playersAction == HEAL)
			{
				player.useHeal();
				pmB.update(player.getCurrentlyBattling(), enemy.getCurrentlyBattling());
				pmO.printOut("You've used the Hyper Potion", pmB);
				playersTurn = false;
			}
			int enemysMoveID;
			if (enemysAction == HEAL)
			{
				enemy.useHeal();
				pmB.update(player.getCurrentlyBattling(), enemy.getCurrentlyBattling());
				pmO.printOut("Enemy used the Hyper Potion", pmB);
				enemysTurn = false;
			}
			else if (enemysAction == FIGHT)
			{
				enemysMoveID = enemy.enemyAttack();
			}
			else
			{
				enemysMoveID = STRUGGLE;
			}

			if (playersTurn == true && enemysTurn == true)
			{
				if (player.getCurrentlyBattling()->getSpeed() >= enemy.getCurrentlyBattling()->getSpeed())
				{
					executeMove(playersMoveID, player.getCurrentlyBattling(), enemy.getCurrentlyBattling(), true, pmO, pmB);
					pmB.update(player.getCurrentlyBattling(), enemy.getCurrentlyBattling());
					
					if (enemy.getCurrentlyBattling()->getCurrentHP() > 0)
					{
						executeMove(enemysMoveID, enemy.getCurrentlyBattling(), player.getCurrentlyBattling(), false, pmO, pmB);
						pmB.update(player.getCurrentlyBattling(), enemy.getCurrentlyBattling());
					}
				}
				else
				{
					executeMove(enemysMoveID, enemy.getCurrentlyBattling(), player.getCurrentlyBattling(), false, pmO, pmB);
					pmB.update(player.getCurrentlyBattling(), enemy.getCurrentlyBattling());
					if (player.getCurrentlyBattling()->getCurrentHP() > 0)
					{
						executeMove(playersMoveID, player.getCurrentlyBattling(), enemy.getCurrentlyBattling(), true, pmO, pmB);
						pmB.update(player.getCurrentlyBattling(), enemy.getCurrentlyBattling());
						
					}
				}
			}
			else if (playersTurn == true)
			{
				executeMove(playersMoveID, player.getCurrentlyBattling(), enemy.getCurrentlyBattling(), true, pmO, pmB);
				pmB.update(player.getCurrentlyBattling(), enemy.getCurrentlyBattling());
			}
			else if (enemysTurn == true)
			{
				executeMove(enemysMoveID, enemy.getCurrentlyBattling(), player.getCurrentlyBattling(), false, pmO, pmB);
				pmB.update(player.getCurrentlyBattling(), enemy.getCurrentlyBattling());
			}

			if (player.getCurrentlyBattling()->getCurrentHP() <= 0)
			{
				pmO.printOut(player.getCurrentlyBattling()->getName() + " fainted.", pmB);
				player.getCurrentlyBattling()->setFainted();
				player.increaseFaintedPokemons();

				if (player.getFaintedPokemons() < 6)
				{
					choosePokemon.playScene();
					pmB.update(player.getCurrentlyBattling(), enemy.getCurrentlyBattling());
				}
			}

			if (enemy.getCurrentlyBattling()->getCurrentHP() <= 0 && enemy.getFaintedPokemons() < 6)
			{
				pmO.printOut("Opposing " + enemy.getCurrentlyBattling()->getName() + " fainted.", pmB);
				enemy.getCurrentlyBattling()->setFainted();
				enemy.increaseFaintedPokemons();
				if (enemy.getFaintedPokemons() < 6)
				{
					enemy.nextPokemon();
					pmO.printOut("Opponent is about to sent out: " + enemy.getCurrentlyBattling()->getName() + "!", pmB);
					pmB.update(player.getCurrentlyBattling(), enemy.getCurrentlyBattling());
				}
			}
		}

		if (enemy.getFaintedPokemons() == 6)
		{
			if (player.getCharacterLvl() < 100)
			{
				player.characterLvlUp();
				enemy.characterLvlUp();
			}
			WinLooseScene winLoose;
			winLoose.playScene("YOU WON!", player, enemy);
			break;
		}
		else if (player.getFaintedPokemons() == 6)
		{
			WinLooseScene winLoose;
			winLoose.playScene("YOU LOOSE...", player, enemy);
			break;
		}
	}
	if (!app.window.isOpen())
	{
		throw - 1;
	}
return -1;
}

void GameSystem::executeMove(int moveID, std::shared_ptr<Pokemon> attacking, std::shared_ptr<Pokemon> defending, bool playersTurn, PlayerMenuOutput &pmO, PlayerMenuBattleScene &pmBs)
{
	string moveInfo = "";
	int accuracyCheck = rand() % 100 + 1;
	///////////////////  /////////////////// 
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

			pmO.printOut(moveInfo, pmBs);
		}
		moveInfo = "";
		if (playersTurn == false)
		{
			moveInfo += "The opposing ";
		}
		moveInfo += attacking->getName() + " used " + attacking->moveList[moveID]->getName() + "!";
		pmO.printOut(moveInfo, pmBs);
		moveInfo = "";

		if (playersTurn == true)
		{
			pmBs.playPlayersAttack();
		}
		else
		{
			pmBs.playEnemysAttack();
		}

		int modifier = getModifier(moveID, attacking, defending, pmO, pmBs);
		int critHitChance = attacking->getBaseSpeed() / 512;

		if ((rand() % 256) < critHitChance)
		{
			A = A * 2;
			pmO.printOut("Critical hit!", pmBs);
		}

		int damage = static_cast<int>(ceil(((((((2*attacking->getLvl())/5) * power * (A / D)) / 50) + 2) * modifier) / 255));
		if (damage == 0)
		{
			damage = 1;
		}

		defending->setHP(damage);
		if (moveID == 4)
		{
			attacking->setHP(static_cast<int>(ceil(0.25*damage)));
		}
	}
	else
	{
		if (playersTurn == false)
		{
			moveInfo += "The opposing ";
		}
		moveInfo += attacking->getName() + "'s attack missed!";
		pmO.printOut(moveInfo, pmBs);
	}

	if (moveID != 4)
	{
		attacking->moveList[moveID]->decreasePP();
		attacking->setMovesLeft();
	}
}

int GameSystem::getModifier(int moveID, std::shared_ptr < Pokemon> attacking, std::shared_ptr<Pokemon> defending, PlayerMenuOutput& pmO, PlayerMenuBattleScene& pmBs)
{
	double modifier = 1;
	if (moveID != 4)
	{
		if (attacking->moveList[moveID]->getType() == attacking->getType1() || attacking->moveList[moveID]->getType() == attacking->getType2())
		{
			modifier = modifier * 1.5;
		}

		double typeModifier = typeChart[defending->getType1()][attacking->moveList[moveID]->getType()] * typeChart[defending->getType2()][attacking->moveList[moveID]->getType()];
		modifier = modifier * typeModifier;
		
		if (typeModifier <= 0.5 && typeModifier != 0)
		{
			pmO.printOut("It's not very effective...", pmBs);
		}
		if (typeModifier >= 2)
		{
			pmO.printOut("It's super effective!", pmBs);
		}
		if (typeModifier == 0)
		{
			pmO.printOut("It doesn't affect", pmBs);
		}
	}

	int randNo = rand() % 39 + 217;
	modifier = modifier * randNo;
	
	return static_cast<int>(ceil(modifier));
}

void GameSystem::continueGame(Player& player, Enemy& enemy)
{
	int indexList[6] = { -1,-1,-1,-1,-1,-1};
	int t_lvl;
	std::fstream file;
	file.open("save.sv");
	file >> t_lvl;
	player.setCharacterLvl(t_lvl);
	enemy.setCharacterLvl(t_lvl);
	for (int i = 0; i < 6; i++)
	{
		file >> indexList[i];
	}
	player.readFromFile(indexList);
	for (int i = 0; i < 6; i++)
	{
		file >> indexList[i];
	}
	enemy.readFromFile(indexList);
	file.close();
	app.gameState = STATE::BATTLE;
}
