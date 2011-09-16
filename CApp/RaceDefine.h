#ifndef _RACE_DEF_H_
    #define _RACE_DEF_H_

//Size
enum SizeType
{
	SIZE_SMALL,
	SIZE_MEDIUM,
};

static std::string SizeNameTable[2] =
{
	"Small",
	"Medium",
};

static std::string GetSizeName(int SizeIndex)
{
	return SizeNameTable[SizeIndex];
}

//Vision
enum VisionType
{
	VisionNormal,
	VisionLowLight,
};

static std::string VisionNameTable[2] =
{
	"Normal",
	"Low Light",
};

static std::string GetVisionName(int VisionIndex)
{
	return VisionNameTable[VisionIndex];
}

//Race
enum RaceType
{
	RACE_DRAGONBORN,
	RACE_DWARF,
	RACE_ELADRIN,
	RACE_ELF,
	RACE_HALFELF,
	RACE_HALFLING,
	RACE_HUMAN,
	RACE_TIEFLING,

	RACE_MAX,
	RACE_NORACE,
};

static struct RaceTableStruct
{
	int Index;
	std::string Name;
	SizeType Size;
	VisionType Vision;
	int Speed;
};

static RaceTableStruct RaceTable[RACE_MAX] =
{
	{ 0, "Dragon Born", SIZE_MEDIUM, VisionNormal,   6, },
	{ 1, "Dwarf",		SIZE_MEDIUM, VisionLowLight, 5},
	{ 2, "Eladrin",		SIZE_MEDIUM, VisionLowLight, 6},
	{ 3, "Elf",			SIZE_MEDIUM, VisionLowLight, 7},
	{ 4, "Half Elf",	SIZE_MEDIUM, VisionLowLight, 6},
	{ 5, "Halfling",	SIZE_SMALL , VisionNormal,   6},
	{ 6, "Human",		SIZE_MEDIUM, VisionNormal,   6},
	{ 7, "Tiefling",	SIZE_MEDIUM, VisionLowLight, 6},
};

//Methods of access to race table
static std::string GetRaceName(int RaceIndex)
{
	for(int i=0; i<RACE_MAX; ++i)
	{
		if(RaceTable[i].Index == RaceIndex)
			return RaceTable[i].Name;
	}

	return "No Name At This Index";
}

static SizeType GetRaceSize(int RaceIndex)
{
	for(int i=0; i<RACE_MAX; ++i)
	{
		if(RaceTable[i].Index == RaceIndex)
			return RaceTable[i].Size;
	}

	return SIZE_MEDIUM;
}

static VisionType GetRaceVision(int RaceIndex)
{
	for(int i=0; i<RACE_MAX; ++i)
	{
		if(RaceTable[i].Index == RaceIndex)
			return RaceTable[i].Vision;
	}

	return VisionNormal;
}

static int GetRaceSpeed(int RaceIndex)
{
	for(int i=0; i<RACE_MAX; ++i)
	{
		if(RaceTable[i].Index == RaceIndex)
			return RaceTable[i].Speed;
	}

	return 0;
}

//Language
enum LanguageType
{
	LangCommon = 1,	
	LangDeepSpeech,
	LangDraconic,	
	LangDwarven,	
	LangElven,	
	LangGiant,
	LangGoblin,	
	LangPrimordial,
	LangSupernal,
	LangAbyssal,
};

struct AditionalLangTableStruct
{
	int Index;
	int Lang;
};

static AditionalLangTableStruct AditionalLangTable[8] = 
{
	//race index    //race lang
	{ 0, 3, },
	{ 1, 4, },
	{ 2, 5, },
	{ 3, 5, },
	{ 4, 5, },
	{ 5, 1, },
	{ 6, 1, },
	{ 7, 1, },
};

static int GetRaceLang(int RaceIndex)
{
	for(int i=0; i<8; ++i)
	{
		if(AditionalLangTable[i].Index == RaceIndex)
			return AditionalLangTable[i].Lang;
	}

	return 99;
}

struct LangTableStruct
{
	int Index;
	std::string Name;
};

static LangTableStruct LangTable[10] = 
{
	{ 1, "Common" },
	{ 2, "DeepSpeech" },
	{ 3, "Draconic" },
	{ 4, "Dwarven", },
	{ 5, "Elven", },
	{ 6, "Giant", },
	{ 7, "Goblin", },
	{ 8, "Primordial", },
	{ 9, "Supernal", },
	{ 10, "Abyssal", },
};

static std::string GetLangName(int LangIndex)
{
	for(int i=0; i<10; ++i)
	{
		if(LangTable[i].Index == LangIndex)
			return LangTable[i].Name;
	}

	return "There is no such language name";
}

//Abilitys Bonus
static int RaceAbility[RACE_MAX][2] =
{
	//ability type// abi type   //alll abilities gain +2
	{ 0, 5, }, { 1, 4, }, { 2, 3, }, { 2, 4, }, { 1, 5, }, { 2, 5, }, { 0, 0, }, { 3, 5, },
};

static int GetRaceAbility(int RaceIndex, int AbiNumber = 0/* 0 or 1*/)
{
	return RaceAbility[RaceIndex][AbiNumber];
}

#endif