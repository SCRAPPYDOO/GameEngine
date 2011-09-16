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
	TYPE_ATTACK,
	TYPE_UTILITY,
};

enum PowerUsageType
{
	TYPE_ATWILL,
	TYPE_ENCOUNTER,
	TYPE_DAILY,
};

static struct Power
{
	int Index;
	std::string Name;
	int Class;
	int Type;		 //PowerType
	int UsageType;	 //PowerUsageType
	int Level;

};

#define PowerMinIndex 10000
#define PowerMaxIndex 20000

static Power PowerTable[PowerMaxIndex] = 
{
	//Index  //Power Name						cl tp ut lvl
	//class feature
	{ 10000, "Divine Fortune",					0, 0, 1, 1,  },
	{ 10001, "Turn Undead",						0, 0, 1, 1,  },
	{ 10002, "Healing Word",					0, 0, 1, 1,  },
	//level1 atwill
	{ 10003, "Lance of Faith",					0, 0, 0, 1,  },
	{ 10004, "Priests Shield",					0, 0, 0, 1,  },
	{ 10005, "Righteous Brand",					0, 0, 0, 1,  },
	{ 10006, "Sacred Flame",					0, 0, 0, 1,  },
	//lvl 1 encountyer
	{ 10007, "Cause Fear",						0, 0, 1, 1,  },
	{ 10008, "Divine Glow",						0, 0, 1, 1,  },
	{ 10009, "Healing Strike",					0, 0, 1, 1,  },
	{ 10010, "Wrathful Thunder",				0, 0, 1, 1,  },
	//lvl 1 daily
	{ 10011, "Avenging Flame",					0, 0, 2, 1,  },
	{ 10012, "Beacon of Hope",					0, 0, 2, 1,  },
	{ 10013, "Cascade of Light",				0, 0, 2, 1,  },
	{ 10014, "Guardian of Faith",				0, 0, 2, 1,  },
	//2 utility
	{ 10015, "Bless",							0, 1, 2, 2,  },
	{ 10016, "Cure Light Wounds",				0, 1, 2, 2,  },
	{ 10017, "Divine Aid",						0, 1, 1, 2,  },
	{ 10018, "Sanctuary",						0, 1, 1, 2,  },
	{ 10019, "Shield of Faith",					0, 1, 2, 2,  },
	//3 encounter
	{ 10020, "Blazing Beacon",					0, 0, 1, 3,  },
	{ 10021, "Command",							0, 0, 1, 3,  },
	{ 10022, "Daunting Light",					0, 0, 1, 3,  },
	{ 10023, "Split the Sky",					0, 0, 1, 3,  },
	//5 dai3ly
	{ 10024, "Consecrated Ground",				0, 0, 2, 5,  },
	{ 10025, "Rune of Peace",					0, 0, 2, 5,  },
	{ 10026, "Spiritual Weapon",				0, 0, 2, 5,  },
	{ 10027, "Weapon of the Gods",				0, 0, 2, 5,  },
	//6 utility
	{ 10028, "Bastion of Health",				0, 1, },
	{ 10029, "Cure Serious Wounds",				0, 1, },
	{ 10030, "Divine Vigor",					0, 1, },
	{ 10031, "Holy Lantern",					0, 1, },
	//7 encounter
	{ 10032, "Awe Strike",						0, 0, 1, 7,  },
	{ 10033, "Break the Spirit",				0, 0, 1, 7,  },
	{ 10034, "Searing Light",					0, 0, 1, 7,  },
	{ 10035, "Strengthen the Faithful",			0, 0, 1, 7,  },
	//9 Daily",		0,
	{ 10036, "Astral Defenders",				0, 0, 2, 9,  },
	{ 10037, "Blade Barrier",					0, 0, 2, 9,  },
	{ 10038, "Divine Power",					0, 0, 2, 9,  },
	{ 10039, "Flame Strike",					0, 0, 2, 9,  },
	//10 utility
	{ 10040, "Astral Refuge",					0, 1, },
	{ 10041, "Knights of Unyielding Valor",		0, 1, },
	{ 10042, "Mass Cure Light Wounds",			0, 1, },
	{ 10043, "Shielding Word",					0, 1, },
	//13 encounter
	{ 10044, "Arc of the Righteous",			0, 0, 1, 13, },
	{ 10045, "Inspiring Strike",				0, 0, 1, 13, },
	{ 10046, "Mantle of Glory",					0, 0, 1, 13, },
	{ 10047, "Plague of Doom",					0, 0, 1, 13, },
	//15 daily
	{ 10048, "Holy Spark",						0, 0, 2, 15, },
	{ 10049, "Purifying Fire",					0, 0, 2, 15, },
	{ 10050, "Seal of Warding",					0, 0, 2, 15, },
	//16 utility
	{ 10051, "Astral Shield",					0, 1, },
	{ 10052, "Cloak of Peace",					0, 1, },
	{ 10053, "Divine Armor",					0, 1, },
	{ 10054, "Hallowed Ground",					0, 1, },
	//17 encopunter
	{ 10055, "Blinding Light",					0, 0, 1, 17, },
	{ 10056, "Enthrall",						0, 0, 1, 17, },
	{ 10057, "Sentinel Strike",					0, 0, 1, 17, },
	{ 10058, "Thunderous Word",					0, 0, 1, 17, },
	//19 daily
	{ 10059, "Fire Storm",						0, 0, 2, 19, },
	{ 10060, "Holy Wrath",						0, 0, 2, 19, },
	{ 10061, "Indomitable Spirit",				0, 0, 2, 19, },
	{ 10062, "Knight of Glory",					0, 0, 2, 19, },
	//22 utility
	{ 10063, "Angel of the Eleven Winds",		0, 1, },
	{ 10064, "Clarion Call of the Astral Sea",	0, 1, },
	{ 10065, "Cloud Chariot",					0, 1, },
	{ 10066, "Purify",							0, 1, },
	{ 10067, "Spirit of Health",				0, 1, },
	//23 encounter
	{ 10068, "Astral Blades of Death",			0, 0, 1, 23, },
	{ 10069, "Divine Censure",					0, 0, 1, 23, },
	{ 10070, "Haunting Strike",					0, 0, 1, 23, },
	{ 10071, "Healing Torch",					0, 0, 1, 23, },
	//25 daily
	{ 10072, "Nimbus of Doom",					0, 0, 2, 25, },
	{ 10073, "Sacred Word",						0, 0, 2, 25, },
	{ 10074, "Seal of Binding",					0, 0, 2, 25, },
	{ 10075, "Seal of Protection",				0, 0, 2, 25, },
	//27 Encounter
	{ 10076, "Punishing Strike",				0, 0, 1, 27, },
	{ 10077, "Sacrificial Healing",				0, 0, 1, 27, },
	{ 10078, "Scourge of the Unworthy",			0, 0, 1, 27, },
	{ 10079, "Sunburst",						0, 0, 1, 27, },
	//29 Daily
	{ 10080, "Astral Storm",					0, 0, 2, 29, },
	{ 10081, "Godstrike",						0, 0, 2, 29, },

	//DragonBorn Racial Power
	{ 10082, "Dragon Breath",				   99, 0, 1, 1,  },
	//Eladrin RacialPower
	{ 10083, "Fey Step",				       99, 0, 1, 1,  },
	//Elf racial
	{ 10084, "Elven Accuracy",				   99, 0, 1, 1,  },
	//halkfliung
	{ 10085, "Second Chance",				   99, 0, 1, 1,  },

	{ 10199, "End Of Power Table",	1, 1, 1,},
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

