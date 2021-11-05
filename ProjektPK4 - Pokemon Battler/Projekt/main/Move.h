#pragma once
#ifndef MOVE_H
#define MOVE_H

#include <string>

class Move
{
private: //variables
	std::string name;
	int currentPp, basePp, accuracy, power, status, type, category;

public:  //variables

private: //methods

public:  //methods
	Move(std::string _name, int _pp, int _accuracy, int _power, int _status, int _type, int _category) :
		name(_name), currentPp(_pp), basePp(_pp), accuracy(_accuracy), power(_power), status(_status), type(_type), category(_category) {}
	std::string getName();
	int getCurrentPP();
	int getPP();
	int getType();
	int getAccuracy();
	int getPower();
	int getStatus();
	int getCategory();
	void resetPP();
	void decreasePP();

};

#endif //MOVE_H