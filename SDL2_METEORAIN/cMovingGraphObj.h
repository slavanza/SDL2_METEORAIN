#pragma once

#include "cGraphObj.h"

class cMovingGraphObj : public cGraphObj
{
	int iSpeed; // скорость
	int xSpeed, ySpeed; // скорости по x и y осям
	double angle; // угол поворота изображения
	SDL_Point dest; // конечная точка
public:
	cMovingGraphObj(char*, int);
	cMovingGraphObj(char*, int, int, int);
	cMovingGraphObj(char*, int, int, int, int, int);
	cMovingGraphObj(const cMovingGraphObj&);
	~cMovingGraphObj();
	void setSpeed(int);
	int getSpeed();
	SDL_Point setDest(int, int);
	SDL_Point getDest();
	bool move();
	virtual void paint(SDL_Renderer*);
	cMovingGraphObj operator=(const cMovingGraphObj&);
	bool isMoving();
};

