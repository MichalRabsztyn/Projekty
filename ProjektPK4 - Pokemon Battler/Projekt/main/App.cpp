#include "App.h"

void App::initWindow()
{
	window.create(VideoMode(static_cast<unsigned int>(resX), static_cast<unsigned int>(resY)), "Battler");
	window.setActive(true);
	window.setFramerateLimit(60);
}

App::App()
{
	initWindow();
}

Color App::colorShift(const Color& currentColor, Color& desiredColor, float shiftSpeed)
{
	if (shiftSpeed > 1)
	{
		shiftSpeed = 1;
	}
	else if (shiftSpeed < 0)
	{
		shiftSpeed = 0;
	}

	int c_r = currentColor.r;
	int c_g = currentColor.g;
	int c_b = currentColor.b;
	int d_r = desiredColor.r;
	int d_g = desiredColor.g;
	int d_b = desiredColor.b;
	int dif_r = d_r - c_r;
	int dif_g = d_r - c_b;
	int dif_b = d_r - c_b;

	if (c_r < d_r)
	{
		c_r += (int)ceil(dif_r * shiftSpeed);
	}
	else if (c_r > d_r)
	{
		c_r -= (int)ceil(dif_r * shiftSpeed);
	}
	if (c_g < d_g)
	{
		c_g += (int)ceil(dif_g * shiftSpeed);
	}
	else if (c_g > d_g)
	{
		c_g -= (int)ceil(dif_g * shiftSpeed);
	}
	if (c_b < d_b)
	{
		c_b += (int)ceil(dif_b * shiftSpeed);
	}
	else if (c_b > d_b)
	{
		c_b -= (int)ceil(dif_b * shiftSpeed);
	}

	return sf::Color(c_r, c_g, c_b);
}

void App::exitGame()
{
	std::cout << "Bye, bye" << std::endl;
}

void App::handleException(int ex)
{
	if (ex == -1)
	{
		std::cout << "Window closed" << std::endl;
		exitGame();
		return;
	}
		
	std::cout << "Error: " << ex << ": ";
	switch (ex)
	{
	case 0:
		std::cout << "Could not load font" << std::endl;
		break;
	case 1:
		std::cout << "Could not load Pokemon data" << std::endl;
		break;
	case 2:
		std::cout << "Could not load Pokemon sprite" << std::endl;
		break;
	case 3:
		std::cout << "Could not load Moves data" << std::endl;
		break;
	case 4:
		std::cout << "Could not load Evolutions data" << std::endl;
		break;
	case 5:
		std::cout << "File corrupted" << std::endl;
		break;
	default:
		break;
	}
}

void App::Debug(std::string str)
{
	std::cout << "Debug: " << str << std::endl;
}





