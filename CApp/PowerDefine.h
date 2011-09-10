#ifndef _POWER_DEF_H_
    #define _POWER_DEF_H_

#define CLASS_MAX 8

static int ClassFeaturePowers[CLASS_MAX][6] = //Powers Automatically Added To Player with Selected Class
{
	{ 10000, 10001, 10002},
	{ },
};

enum PowerType
{
	TYPE_ATWILL,
	TYPE_ENCOUNTER,
	TYPE_DAILY,
	TYPE_UTILITY,
};

static struct Power
{
	int Index;
	std::string Name;
	int Class;
	int Type;
	int Level;

};

#define PowerMinIndex 10000
#define PowerMaxIndex 20000

static Power PowerTable[PowerMaxIndex] = 
{
	{ 10000, "Divine Fortune",		0, 1, 1},
	{ 10001, "Turn Undead",			0, 1, 1},
	{ 10002, "Healing Word",		0, 1, 1},
	{ 10003, "Lance of Faith",		0, 0, 1},
	{ 10004, "Priests Shield",		0, 0, 1},
	{ 10005, "Righteous Brand",		0, 0, 1},
	{ 10006, "Sacred Flame",		0, 0, 1},
	{ 10007, "Cause Fear",			0, 1, 1},
	{ 10008, "Divine Glow",			0, 1, 1},
	{ 10009, "Healing Strike",		0, 1, 1,},
	{ 10010, "Wrathful Thunder",	0, 1, 1,},
	{ 10011, "Avenging Flame",		0, 2, 1,},
	{ 10012, "Beacon of Hope",		0, 2, 1,},
	{ 10013, "Cascade of Light",	0, 2, 1,},
	{ 10014, "Guardian of Faith",	0, 2, 1,},



	{ 10017, "End Of Power Table",	1, 1, 1,},
};

static std::string GetPowerName(int Index)
{
	for(int i=0; i<PowerMaxIndex; ++i)
	{
		if(PowerTable[i].Index == Index)
			return PowerTable[i].Name;
	}

	return "No Name At This Index";
};

static int GetPowerType(int Index)
{
	for(int i=0; i<PowerMaxIndex; ++i)
	{
		if(PowerTable[i].Index == Index)
			return PowerTable[i].Type;
	}

	return NULL;
};

#endif

