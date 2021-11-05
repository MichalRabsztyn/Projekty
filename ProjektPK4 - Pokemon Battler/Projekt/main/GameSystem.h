#pragma once
#ifndef GAME_SYSTEM_H
#define GAME_SYSTEM_H

#include <memory>

class Pokemon;
class Player;
class Enemy;
class Entity;
class PlayerMenuOutput;
class PlayerMenuBattleScene;

////////////////////////////////////////////////////////////////
/// \brief Class for whole game system
////////////////////////////////////////////////////////////////
class GameSystem
{
private: //variables
	////////////////////////////////////////////////////////////
	/// Array containing types dependencies 
	////////////////////////////////////////////////////////////
	double typeChart[19][19] = {
		{   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1},  //1-type modifier[0]
		{   1,   1,   1,   1,   1,   1, 0.5,   2,   2,   1, 0.5, 0.5,   1,   1,   1,   1,   2,   1,   1},  //Bug			[1]
		{   1,   2, 0.5,   1,   1,   2,   2,   1,   1, 0.5,   1,   1,   1,   1,   1,   0,   1,   1,   1},  //Dark			[2]
		{   1,   1,   1,   2, 0.5,   2,   1, 0.5,   1,   1, 0.5,   1,   2,   0,   1,   1,   1,   1, 0.5},  //Dragon			[3]
		{   1,   1,   1,   1, 0.5,   1,   1,   1, 0.5,   1,   1,   2,   1,   1,   1,   1,   1, 0.5,   1},  //Electric		[4]
		{   1, 0.5, 0.5,   0,   1,   1, 0.5,   1,   1,   1,   1,   1,   1,   1,   2,   1,   1,   2,   1},  //Fairy			[5]
		{   1, 0.5, 0.5,   1,   1,   2,   1,   1,   2,   1,   1,   1,   1,   1,   1,   2, 0.5,   1,   1},  //Fighting		[6]
		{   1, 0.5,   1,   1,   1, 0.5,   1, 0.5,   1,   1, 0.5,   2, 0.5,   1,   1,   1,   2, 0.5,   2},  //Fire			[7]
		{   1, 0.5,   1,   1,   2,   1, 0.5,   1,   1,   1, 0.5,   0,   2,   1,   1,   1,   2,   1,   1},  //Flying			[8]
		{   1, 0.5,   2,   1,   1,   1,   0,   1,   1,   2,   1,   1,   1,   0, 0.5,   1,   1,   1,   1},  //Ghost			[9]
		{   1,   2,   1,   1, 0.5,   1,   1,   2,   2,   1, 0.5, 0.5,   2,   1,   2,   1,   1,   1, 0.5},  //Grass			[10]
		{   1,   1,   1,   1,   0,   1,   1,   1,   1,   1,   2,   1,   2,   1, 0.5,   1, 0.5,   1,   2},  //Ground			[11]
		{   1,   1,   1,   1,   1,   1,   2,   2,   1,   1,   1,   1, 0.5,   1,   1,   1,   2,   2,   1},  //Ice			[12]
		{   1,   1,   1,   1,   1,   1,   2,   1,   1,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1},  //Normal			[13]
		{   1, 0.5,   1,   1,   1, 0.5, 0.5,   1,   1,   1, 0.5,   2,   1,   1, 0.5,   2,   1,   1,   1},  //Poison			[14]
		{   1,   2,   2,   1,   1,   1, 0.5,   1,   1,   2,   1,   1,   1,   1,   1, 0.5,   1,   1,   1},  //Psychic		[15]
		{   1,   1,   1,   1,   1,   1,   2, 0.5, 0.5,   1,   2,   2,   1, 0.5, 0.5,   1,   1,   2,   2},  //Rock			[16]
		{   1, 0.5,   1, 0.5,   1, 0.5,   2,   2, 0.5,   1, 0.5,   2, 0.5, 0.5,   0, 0.5, 0.5, 0.5,   1},  //Steel			[17]
		{   1,   1,   1,   1,   2,   1,   1, 0.5,   1,   1,   2,   1, 0.5,   0,   1,   1,   1, 0.5, 0.5}   //Water			[18]
	};

public:  //variables

private: //methods

public:  //methods
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	////////////////////////////////////////////////////////////
	GameSystem();
	
	////////////////////////////////////////////////////////////
	/// \brief Default destructor
	////////////////////////////////////////////////////////////
	~GameSystem() {}

	////////////////////////////////////////////////////////////
	/// \brief Before starting game, check if all files exist
	/// and can be opened. If not, throw exception
	////////////////////////////////////////////////////////////
	void checkFiles();

	////////////////////////////////////////////////////////////
	/// \brief Control the state of game: SETUP, BATTLE, EXIT
	////////////////////////////////////////////////////////////
	void gameLoop();

	////////////////////////////////////////////////////////////
	/// \brief Proper system of battle
	/// 
	/// \param p1 Player object
	/// \param e1 Enemy object
	/// 
	/// \return 0 if successful or exception code
	////////////////////////////////////////////////////////////
	int battle(Player& p1, Enemy& e1);

	////////////////////////////////////////////////////////////
	/// \brief Calculate damage, create appropriate message 
	/// and play right animation
	/// 
	/// \param moveID identifier of move to execute
	/// \param attacking current attacker
	/// \param defending current defender
	/// \param playersTurn used for adjucting messages
	/// \param pmO player output object
	/// \param pmBs battle scene object 
	////////////////////////////////////////////////////////////
	void executeMove(int moveID, std::shared_ptr<Pokemon> attacking, std::shared_ptr<Pokemon> defending, bool playersTurn, PlayerMenuOutput &pmO, PlayerMenuBattleScene& pmBs);

	////////////////////////////////////////////////////////////
	/// \brief Calculate modifier for damage calculation
	/// 
	/// \param moveID identifier of move to execute
	/// \param attacking current attacker
	/// \param defending current defender
	/// 
	/// \return modifier value
	////////////////////////////////////////////////////////////
	int getModifier(int moveID, std::shared_ptr<Pokemon> attacking, std::shared_ptr <Pokemon> defending, PlayerMenuOutput& pmo, PlayerMenuBattleScene& pmBs);

	void continueGame(Player& player, Enemy& enemy);

};
#endif //GAME_SYSTEM_H 