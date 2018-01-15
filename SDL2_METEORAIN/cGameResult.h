#pragma once
class cGameResult
{
	int iScore;
	unsigned uTime;
	int iLevel;
public:
	cGameResult(int, unsigned, int);
	~cGameResult();
	int getScore();
	unsigned getTime();
	int getLevel();
};

