#pragma once
class cGameResult
{
	int iScore;
	unsigned uTime;
	int iLevel;
	bool bPaused;
public:
	cGameResult(int, unsigned, int, bool);
	~cGameResult();
	int getScore();
	unsigned getTime();
	int getLevel();
	bool isPaused();
};

