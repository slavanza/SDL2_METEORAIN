#include "cMovingGraphObj.h"
#include <cmath>

#define PI 3.14159265

cMovingGraphObj::cMovingGraphObj(char* szName, int iSpeedInput):cGraphObj(szName)
{
	iSpeed = iSpeedInput;
	dest.x = rect.x;
	dest.y = rect.y;
	iSpeed = xSpeed = ySpeed = 0;
	angle = 0;
}

cMovingGraphObj::cMovingGraphObj(char* szName, int iSpeedInput, int x, int y) : cGraphObj(szName, x, y)
{
	iSpeed = iSpeedInput;
	dest.x = rect.x;
	dest.y = rect.y;
	iSpeed = xSpeed = ySpeed = 0;
	angle = 0;
}

cMovingGraphObj::cMovingGraphObj(char* szName, int iSpeedInput, int x, int y, int xDest, int yDest) : cGraphObj(szName, x, y)
{
	iSpeed = iSpeedInput;
	dest.x = xDest;
	dest.y = yDest;
	double w = abs(dest.x - rect.x);
	double h = abs(dest.y - rect.y);
	double dist = sqrt(w*w + h*h);
	xSpeed = round((iSpeed * w) / dist);
	ySpeed = round((iSpeed * h) / dist);
	double cos = abs(h) / sqrt(w*w + h*h);
	angle = acos(cos) * 180.0 / PI;
}

cMovingGraphObj::cMovingGraphObj(const cMovingGraphObj& copy) : cGraphObj((cGraphObj)copy)
{
	iSpeed = copy.iSpeed;
	xSpeed = copy.xSpeed; 
	ySpeed = copy.ySpeed;
	angle = copy.angle;
	dest = copy.dest;
}

cMovingGraphObj::~cMovingGraphObj()
{
}

void cMovingGraphObj::setSpeed(int iSpeedInput)
{
	iSpeed = iSpeedInput;
}

int cMovingGraphObj::getSpeed()
{
	return iSpeed;
}

SDL_Point cMovingGraphObj::setDest(int x, int y)
{
	dest.x = x;
	dest.y = y;
	double w = abs(dest.x - rect.x);
	double h = abs(dest.y - rect.y);
	double dist = sqrt(w*w + h*h);
	xSpeed = round((iSpeed * w) / dist);
	ySpeed = round((iSpeed * h) / dist);
	double cos = abs(h) / sqrt(w*w + h*h);
	angle = acos(cos) * 180.0 / PI;
	return dest;
}

SDL_Point cMovingGraphObj::getDest()
{
	return dest;
}

bool cMovingGraphObj::move()
{
	if ((dest.x == rect.x) && (dest.y == rect.y))
		return false;
	if (dest.x > rect.x)
	{
		if ((rect.x + xSpeed) > dest.x)
			dest.x = rect.x;
		rect.x += xSpeed;
	}
	else
	{
		if ((rect.x - xSpeed) < dest.x)
			dest.x = rect.x + xSpeed;
		rect.x -= xSpeed;
	}

	if (dest.y > rect.y)
	{
		if ((rect.y + ySpeed) > dest.y)
			dest.y = rect.y;
		rect.y += ySpeed;
	}
	else
	{
		if ((rect.y - ySpeed) < dest.y)
			dest.y = rect.y + ySpeed;
		rect.y -= ySpeed;
	}
	return true;
}

void cMovingGraphObj::paint(SDL_Renderer* lpRenderer)
{
	SDL_Texture* lpTexture = makeTexture(lpRenderer);
	SDL_Point center;
	center.x = rect.w / 2;
	center.y = rect.h / 2;
	SDL_RenderCopyEx(lpRenderer, lpTexture, NULL, &rect, angle, &center, SDL_FLIP_NONE);
	SDL_DestroyTexture(lpTexture);

	move(); // функция перемещения временно вшита в отрисовку
}

cMovingGraphObj cMovingGraphObj::operator=(const cMovingGraphObj& copy)
{
	cGraphObj* lpThis = (cGraphObj*)this;
	*lpThis = (cGraphObj)copy;
	iSpeed = copy.iSpeed;
	xSpeed = copy.xSpeed;
	ySpeed = copy.ySpeed;
	angle = copy.angle;
	dest = copy.dest;
	return *this;
}