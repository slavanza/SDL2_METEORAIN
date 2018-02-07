#include "cMain.h"
#include "cRecordsMenu.h"
#include "cGameField.h"
#include "cInput.h"
#include <iostream>


cMain::cMain()
{
	if(SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_SHOWN, &lpWindow, &lpRenderer) < 0)
	{
		std::cout << "Window/Renderer creating error" << std::endl;
	}
}


cMain::~cMain()
{
	SDL_DestroyWindow(lpWindow);
	SDL_DestroyRenderer(lpRenderer);
}

int cMain::main()
{
	/// Основная функция всей игры
	cMenu mainMenu(4, "Играть", "Рекорды", "Помощь", "Выход");
	mainMenu.setTitle("Главное меню");
	bool bFlag = false;
	while(!bFlag)
	switch (mainMenu.choose(lpRenderer))
	{
	case 0:
	{
		cMenu difficulty(4, "Легко", "Нормально", "Сложно", "Назад");
		difficulty.setTitle("Выберите сложность");
		int iStartLevel = difficulty.choose(lpRenderer);
		if ((iStartLevel >= 0) && (iStartLevel < 3))
		{
			bool bGame = false;
			cGameField game(iStartLevel);
			while (!bGame)
			{
				cGameResult result = game.start(lpRenderer);
				if (result.isPaused())
				{
					cMenu pause(2, "Продолжить", "Выход");
					pause.setTitle("Меню паузы");
					if (pause.choose(lpRenderer))
					{
						cInput input("Введите имя");
						cPlayer player(input.input(lpRenderer));
						player.updateFromResult(result);
						cRecords records;
						records.load("records.bin");
						records.add(player);
						records.save("records.bin");
						bGame = true;
					}
				}
				else
				{
					cInput input("Введите имя");
					cPlayer player(input.input(lpRenderer));
					player.updateFromResult(result);
					cRecords records;
					records.load("records.bin");
					records.add(player);
					records.save("records.bin");
					bGame = true;
				}
			}
		}
	}
		break;
	case 1:
	{
		cRecordsMenu records;
		records.choose(lpRenderer);
	}
		break;
	case 2:
		break;
	case 3:
		bFlag = true;
		break;
	default:
		std::cout << "Menu function error" << std::endl;
	}
	return 0;
}