#include "stdafx.h"

#undef main

#define WIDTH 640
#define HEIGHT 480

bool bSDL_Init = false;
bool bTTF_Init = false;

void InitAll();
void QuitAll();

int main(int argc, char** argv)
{
	std::cout << "Application started" << std::endl;
	InitAll();
	atexit(QuitAll);

	SDL_Window* mainWnd = nullptr;
	SDL_Renderer* mainRnd = nullptr;

	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &mainWnd, &mainRnd) < 0)
	{
		std::cout << "Window/Renderer creating error" << std::endl;
		return -3;
	}

	system("pause");
	SDL_DestroyRenderer(mainRnd);
	SDL_DestroyWindow(mainWnd);
	std::cout << "Applicaion ended" << std::endl;
	return 0;
}

void InitAll()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
		exit(-1);
	}
	std::cout << "[ InitAll ] : SDL Initialized" << std::endl;
	bSDL_Init = true;
	if (TTF_Init() < 0)
	{
		std::cout << "TTF_Init error: " << TTF_GetError() << std::endl;
		exit(-2);
	}
	std::cout << "[ InitAll ] : TTF Initialized" << std::endl;
	bTTF_Init = true;
}

void QuitAll()
{
	if (bSDL_Init)
	{
		SDL_Quit();
		std::cout << "[ InitAll ] : SDL Uninitialized" << std::endl;
	}
	if (bTTF_Init)
	{
		TTF_Quit();
		std::cout << "[ InitAll ] : TTF Uninitialized" << std::endl;
	}
}