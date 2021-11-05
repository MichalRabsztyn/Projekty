#include "GameSystem.h"
#include "App.h"
#include <cstdio>

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");
	srand(static_cast<unsigned int>(time(NULL)));
	
	try
	{
		GameSystem gameSystem;
		gameSystem.gameLoop();
	}
	catch (int ex)
	{
		app.handleException(ex);
		std::getchar();
	}
	return 0;
}