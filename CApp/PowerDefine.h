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

static int ClassFeaturePowers[CLASS_MAX][6] = //Powers Automatically Added To Player with Selected Class
{
	{ 10000, 10001, 10002},
	{ },
};

static std::string PowerName[PowerIndexMax - 1] =
{
	"Divine Fortune", //Cleric
	"Turn Undead",
	"Healing Word",
	"Lance of Faith",
	"Priest’s Shield",
};

static std::string GetPowerName(int Index)
{
	return PowerName[Index - 10000];
}

#endif

