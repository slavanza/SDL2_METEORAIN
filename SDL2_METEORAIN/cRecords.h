#pragma once

#include "cPlayer.h"

class cRecords
{
	cPlayer records[10];
public:
	cRecords();
	~cRecords();
	bool add(cPlayer&);
	cPlayer get(int);
	void save(char*);
	void load(char*);
};

