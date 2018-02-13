#include "cMain.h"
#include "cRecordsMenu.h"
#include "cGameField.h"
#include "cInput.h"
#include "cMessage.h"
#include <iostream>


cMain::cMain()
{
	if(SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_SHOWN, &lpWindow, &lpRenderer) < 0)
	{
		std::cout << "Window/Renderer creating error" << std::endl;
	}
	cGraphObj background("Textures/Menu.jpg");
	background.paint(lpRenderer);
}


cMain::~cMain()
{
	SDL_DestroyWindow(lpWindow);
	SDL_DestroyRenderer(lpRenderer);
}

int cMain::main() // Основная функция всей игры
{
	cMenu mainMenu(4, "Играть", "Рекорды", "Помощь", "Выход");
	mainMenu.setTitle("Главное меню");
	cMessage msg1("Игра \"Метеоритный дождь\"", MSG_GREETING);
	cMessage msg2("Зайченко В.А. И964", MSG_GREETING);
	msg1.show(lpRenderer, 1500);
	msg2.show(lpRenderer, 1500);
	bool bFlag = false;
	while(!bFlag)
	switch (mainMenu.choose(lpRenderer))
	{
	case 0: // Играть
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
						cMessage msg("Вы уверены?", MSG_YESNO);
						if (!msg.show(lpRenderer))
						{
							cRecords records;
							records.load("records.bin");
							cPlayer player;
							player.updateFromResult(result);
							if (records.isAddable(player))
							{
								cInput input("Введите имя");
								cPlayer player(input.input(lpRenderer));
								player.updateFromResult(result);
								records.add(player);
								records.save("records.bin");
							}
							bGame = true;
						}
					}
				}
				else
				{	cRecords records;
					records.load("records.bin");
					cPlayer player;
					player.updateFromResult(result);
					if (records.isAddable(player))
					{
						cInput input("Введите имя");
						cPlayer player(input.input(lpRenderer));
						player.updateFromResult(result);
						records.add(player);
						records.save("records.bin");
					}
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
	{
		cGraphObj help("Textures/Info.jpg");
		help.paint(lpRenderer);
		SDL_RenderPresent(lpRenderer);
		SDL_Event event;
		bool bFlag = false;
		while (!bFlag)
		{
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					exit(0);
					break;
				case SDL_KEYDOWN:
				case SDL_MOUSEBUTTONDOWN:
					bFlag = true;
				}
			}
		}
	}
		break;
	case 3:
	{	
		cMessage msg("Вы уверены?", MSG_YESNO);
		if (!msg.show(lpRenderer))
		{
			bFlag = true;
		}
	}
		break;
	default:
		std::cout << "Menu function error" << std::endl;
	}
	return 0;
}