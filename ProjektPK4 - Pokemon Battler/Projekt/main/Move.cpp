#include "Move.h"

using namespace std;

string Move::getName()
{
	return name;
}

int Move::getCurrentPP()
{
	return currentPp;
}

int Move::getPP()
{
	return basePp;
}

int Move::getAccuracy()
{
	return accuracy;
}

int Move::getPower()
{
	return power;
}

int Move::getStatus()
{
	return status;
}

int Move::getType()
{
	return type;
}

int Move::getCategory()
{
	return category;
}

void Move::decreasePP()
{
	currentPp--;
}

void Move::resetPP()
{
	currentPp = basePp;
}
