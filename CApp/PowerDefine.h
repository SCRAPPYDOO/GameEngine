#ifndef _POWER_DEF_H_
    #define _POWER_DEF_H_

#define CLASS_MAX 8

static int ClassPowersBeginEnd[CLASS_MAX][2] =
{
	{ 10000  , 10004  }, //Cleric
	{ 11000  , 11000  }, //
	{ 12000  , 12000  },
	{ 13000  , 13000  },
	{ 14000  , 14000  },
	{ 15000  , 15000  },
	{ 16000  , 16000  },
	{ 17000  , 17000  },
};

enum PowerIndex
{
	//Cleric
	PowerDivineFortune = 10000,
	PowerTurnUndead,
	PowerHealingWord,
	LanceOfFaith,
	PriestsShield,
	//If U add any spell u need to add same in PowerName table

	PowerIndexMax,
};

enum PowerType
{
	TYPE_ATWILL,
	TYPE_ENCOUNTER,
	TYPE_DAILY,
	TYPE_UTILITY,
};

static int ClassFeaturePowers[CLASS_MAX][6] = //Powers Automatically Added To Player with Selected Class
{
	{ 10000, 10001, 10002},
	{ },
};

static struct Power
{
	int Index;
	std::string Name;
	int Class;
	int Type;
	int Level;
};

static Power PowerTable[PowerIndexMax] = 
{
	{ 10000, "Divine Fortune", 0, 1, 1},
	{ 10001, "Turn Undead", 0, 1, 1},
	{ 10002, "Healing Word", 0, 1, 1},
	{ 10003, "Lance of Faith", 0, 0, 1},
	{ 10004, "Priest’s Shield", 0, 0, 1},
};

static std::string GetPowerName(int Index)
{
	for(int i=0; i<PowerIndexMax; ++i)
	{
		if(PowerTable[i].Index == Index)
			return PowerTable[i].Name;
	}

	return "No Name At This Index";
};

#endif

