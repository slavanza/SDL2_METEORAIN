#include "cMessage.h"
#include <cstring>


cMessage::cMessage(char* szText, msgType typeInput) : background("Textures/Message.jpg", 160, 120)
{
	message.setSize(40);
	message.setFont("a_AlternaSw.ttf");
	message.setText(szText);
	message.setPos(320 - message.getRect().w / 2, 240 - message.getRect().h / 2);
	type = typeInput;
	switch (type)
	{
	case MSG_OK:
		buttons = new cTextObj;
		buttons->setSize(40);
		buttons->setFont("a_AlternaSw.ttf");
		buttons->setText("OK");
		buttons->setPos(320 - buttons->getRect().w / 2, 300);
		break;
	case MSG_YESNO:
		buttons = new cTextObj[2];
		for (int i = 0; i < 2; i++)
		{
			buttons[i].setSize(40);
			buttons[i].setFont("a_AlternaSw.ttf");
		}
		buttons[0].setText("Да");
		buttons[0].setPos(240 - buttons[0].getRect().w / 2, 300);
		buttons[1].setText("Нет");
		buttons[1].setPos(400 - buttons[1].getRect().w / 2, 300);
		break;
	case MSG_GREETING:
		background.changeImg("Textures/Menu.jpg");
		background.setPos(0, 0);
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
		SDL_Point cur;
		SDL_GetMouseState(&cur.x, &cur.y);
		switch (type)
		{
		case MSG_OK:
			if (SDL_EnclosePoints(&cur, 1, &(buttons->getRect()), NULL))
				buttons->setColor(128, 128, 128);
			else
				buttons->setColor();
			break;
		case MSG_YESNO:
			if (SDL_EnclosePoints(&cur, 1, &(buttons[0].getRect()), NULL))
				buttons[0].setColor(128, 128, 128);
			else
				buttons[0].setColor();
			if (SDL_EnclosePoints(&cur, 1, &(buttons[1].getRect()), NULL))
				buttons[1].setColor(128, 128, 128);
			else
				buttons[1].setColor();
		}
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_MOUSEBUTTONDOWN:
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
						case MSG_GREETING:
							bFlag = true;
						}
					}
				}
				break;
			case SDL_KEYDOWN:
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
	background.paint(lpRenderer);
	message.paint(lpRenderer);
	switch (type)
	{
	case MSG_OK:
	{
		SDL_Color old_color;
		SDL_GetRenderDrawColor(lpRenderer, &old_color.r, &old_color.g, &old_color.b, &old_color.a);
		SDL_Rect rect = buttons->getRect();
		rect.x -= 10;
		rect.y -= 10;
		rect.h += 20;
		rect.w += 20;
		SDL_SetRenderDrawColor(lpRenderer, 255, 255, 255, 255);
		SDL_RenderFillRect(lpRenderer, &rect);
		rect.x += 3;
		rect.y += 3;
		rect.h -= 6;
		rect.w -= 6;
		SDL_SetRenderDrawColor(lpRenderer, 0, 0, 0, 255);
		SDL_RenderFillRect(lpRenderer, &rect);
		SDL_SetRenderDrawColor(lpRenderer, old_color.r, old_color.g, old_color.b, old_color.a);
		buttons->paint(lpRenderer);
	}
		break;
	case MSG_YESNO:
	{
		SDL_Color old_color;
		SDL_GetRenderDrawColor(lpRenderer, &old_color.r, &old_color.g, &old_color.b, &old_color.a);
		for (int i = 0; i < 2; i++)
		{
			SDL_Rect rect = buttons[i].getRect();
			rect.x -= 10;
			rect.y -= 10;
			rect.h += 20;
			rect.w += 20;
			SDL_SetRenderDrawColor(lpRenderer, 255, 255, 255, 255);
			SDL_RenderFillRect(lpRenderer, &rect);
			rect.x += 3;
			rect.y += 3;
			rect.h -= 6;
			rect.w -= 6;
			SDL_SetRenderDrawColor(lpRenderer, 0, 0, 0, 255);
			SDL_RenderFillRect(lpRenderer, &rect);
			buttons[i].paint(lpRenderer);
		}
		SDL_SetRenderDrawColor(lpRenderer, old_color.r, old_color.g, old_color.b, old_color.a);
	}
	}
	SDL_RenderPresent(lpRenderer);
}