#include "Controller.h"
#include <iostream>

int main()
{
	Controller game;
	srand(time(NULL));
	game.run();
	return EXIT_SUCCESS;
}