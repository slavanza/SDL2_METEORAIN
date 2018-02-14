#include "cRecords.h"
#include <fstream>
#include <iostream>


cRecords::cRecords()
{
}


cRecords::~cRecords()
{
}

bool cRecords::add(cPlayer & player)
{
	for (int i = 0; i < 10; i++)
	{
		if (player.getTotalScore() >= records[i].getTotalScore())
		{
			if (player.getTotalScore() != records[i].getTotalScore())
			{
				for (int j = 9; j > i; j--)
				{
					records[j] = records[j - 1];
				}
				records[i] = player;
				return true;
			}
			else
			{
				if (player.getMaxLevel() >= records[i].getMaxLevel())
				{
					if (player.getMaxLevel() != records[i].getMaxLevel())
					{
						for (int j = 9; j > i; j--)
						{
							records[j] = records[j - 1];
						}
						records[i] = player;
						return true;
					}
					else
					{
						if (player.getTotalTime() >= records[i].getTotalTime())
						{
							if (player.getTotalTime() != records[i].getTotalTime())
							{
								for (int j = 9; j > i; j--)
								{
									records[j] = records[j - 1];
								}
								records[i] = player;
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

cPlayer cRecords::get(int iNumber)
{
	if ((iNumber < 10) && (iNumber >= 0))
	{
		return records[iNumber];
	}
	cPlayer nullPlayer;
	return nullPlayer;
}

void cRecords::save(char* szFile)
{
	std::ofstream output(szFile, std::ios::binary | std::ios::out);
	if (!output.is_open())
	{
		std::cout << "Couldn't open records file to write" << std::endl;
		return;
	}
	for (int i = 0; i < 10; i++)
	{
		output.write((char*)&(records[i]), sizeof(cPlayer));
	}
	output.close();
}

void cRecords::load(char* szFile)
{
	std::ifstream input(szFile, std::ios::binary | std::ios::in);
	if (!input.is_open())
	{
		std::cout << "Couldn't open records file to read" << std::endl;
		return;
	}
	for (int i = 0; i < 10; i++)
	{
		input.read((char*)&(records[i]), sizeof(cPlayer));
	}
	input.close();
}

bool cRecords::isAddable(cPlayer& player)
{
	for (int i = 0; i < 10; i++)
	{
		if (player.getTotalScore() >= records[i].getTotalScore())
		{
			if (player.getMaxLevel() >= records[i].getMaxLevel())
			{
				if (player.getTotalTime() >= records[i].getTotalTime())			
				{
					return true;
				}
			}
			
		}
	}
	return false;
}