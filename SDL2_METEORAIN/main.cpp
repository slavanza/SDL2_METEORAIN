#include "stdafx.h"

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL_Init error" << std::endl;
		return -1;
	}

	SDL_Quit();
	system("pause");
	return 0;
}