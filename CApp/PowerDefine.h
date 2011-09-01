#ifndef _POWER_DEF_H_
    #define _POWER_DEF_H_

#include "CUnit.h"

#define PowerIndexBegin 10000
 
enum PowerIndex
{
	//Cleric
	PowerDivineFortune = 10000,
	PowerTurnUndead,
	PowerHealingWord,

	PowerIndexMax,
};

static int ClassFeaturePowers[6][6] =
{
	{ 10000, 10001, 10002},
	{ },
};

static std::string GetPowerString[PowerIndexMax - 1] =
{
	//Cleric
	"Divine Fortune",
	"Turn Undead",
	"Healing Word",
};

#endif

