#include "cGameField.h"

cGameField::cGameField(int iLevelInput):background("default")
{
	iLevel = iLevelInput;
	switch (iLevel)
	{
	case 0:
	{
		cGraphObj temp("level_0");
		background = temp;
	}
		break;
	case 1:
	{
		cGraphObj temp("level_1");
		background = temp;
	}
		break;
	default:
	}
}


cGameField::~cGameField()
{
}
