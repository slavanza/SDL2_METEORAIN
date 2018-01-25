#pragma once

#include "cGraphObj.h"

class cMovingGraphObj : public cGraphObj
{
	int iSpeed; // ��������
	int xSpeed, ySpeed; // �������� �� x � y ����
	double angle; // ���� �������� �����������
	SDL_Point dest; // �������� �����
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

