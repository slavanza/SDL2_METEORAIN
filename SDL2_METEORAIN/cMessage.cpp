#include "cMessage.h"
#include <cstring>


cMessage::cMessage(char* szText, msgType typeInput) : background("Textures/Message.jpg", 160, 120)
{
	message.setSize(40);
	message.setFont("a_AlternaSw.ttf");
	message.setText(szText);
	message.setPos(320 - strlen(szText) * 20, 140);
	type = typeInput;
	switch (type)
	{
	case MSG_OK:
		buttons = new cTextObj;
		buttons->setSize(40);
		buttons->setFont("a_AlternaSw.ttf");
		buttons->setText("OK");
		buttons->setPos(320 - strlen("OK") * 20, 300);
		break;
	case MSG_YESNO:
		buttons = new cTextObj[2];
		for (int i = 0; i < 2; i++)
		{
			buttons[i].setSize(40);
			buttons[i].setFont("a_AlternaSw.ttf");
		}
		buttons[0].setText("Yes");
		buttons[0].setPos(300 - strlen("Yes") * 20, 300);
		buttons[1].setText("No");
		buttons[1].setPos(340 - strlen("No") * 20, 300);
		break;
	case MSG_INFO:
		buttons = nullptr;
	}
}


cMessage::~cMessage()
{
	delete[] buttons;
}

int cMessage::show(SDL_Renderer* lpRenderer, unsigned uTime)
{
	int iReturn = 0;
	unsigned uTimer = 0;
	if (uTime != 0)
		uTimer = SDL_GetTicks();
	bool bFlag = false;
	SDL_Event event;
	while (!bFlag)
	{
		if (uTime)
		{
			if ((SDL_GetTicks() - uTimer) >= uTime)
				bFlag = true;
		}
		draw(lpRenderer);
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			SDL_QUIT:
				exit(0);
				break;
			SDL_MOUSEBUTTONDOWN:
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						SDL_Point click;
						click.x = event.button.x;
						click.y = event.button.y;
						switch (type)
						{
						case MSG_OK:
							if (SDL_EnclosePoints(&click, 1, &(buttons->getRect()), NULL))
								bFlag = true;
							break;
						case MSG_YESNO:
							if (SDL_EnclosePoints(&click, 1, &(buttons[0].getRect()), NULL))
								bFlag = true;
							if (SDL_EnclosePoints(&click, 1, &(buttons[1].getRect()), NULL))
							{
								iReturn = 1;
								bFlag = true;
							}
							break;
						case MSG_INFO:
							bFlag = true;
						}
					}
				}
				break;
			SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_RETURN) // по умолчанию : принять
					bFlag = true;
				break;
				if (event.key.keysym.sym == SDLK_ESCAPE) // по умолчанию : отмена
				{
					if (type == MSG_YESNO)
						iReturn = 1;
					bFlag = true;
				}
				break;
			}
		}
	}
	return iReturn;
}

void cMessage::draw(SDL_Renderer* lpRenderer)
{
	SDL_RenderClear(lpRenderer);
	background.paint(lpRenderer);
	message.paint(lpRenderer);
	switch (type)
	{
	case MSG_OK:
		buttons->paint(lpRenderer);
		break;
	case MSG_YESNO:
		for (int i = 0; i < 2; i++)
			buttons[i].paint(lpRenderer);
	}
	SDL_RenderPresent(lpRenderer);
}