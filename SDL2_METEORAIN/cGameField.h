#pragma once

#include "cGame.h"
#include "cObjList.h"
#include "cMovingObjList.h"
#include "cGameResult.h"

class cGameField : public cGame
{
	cObjList objList;
	cMovingObjList movingObjList;
	cGraphObj background;
	int iLevel;
	// ��������
	int compare();
public:
	cGameField(int);
	~cGameField();
	cGameResult start(); // �� ���� ������ ����� ����� ����������� ��������� '�����'
};

