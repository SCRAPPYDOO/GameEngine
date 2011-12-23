#ifndef _ITEMTABLE_DEF_H_
    #define _ITEMTABLE_DEF_H_

enum ItemTableRows
{
	ItemTableID,
	ItemTableName,
};

enum ItemType
{
	ItemTypeHead,
	ItemTypeChest,
	ItemTypeWrists,
	ItemTypeRing,	
	ItemTypeBoots,
	ItemTypeHands,
	ItemTypeBelt,
	ItemTypeCloak,
	ItemTypeNecklace,
	ItemTypeWeapon,
	ItemTypeShield,
	ItemTypeAmmo,

	ItemTypeTrincket,
	ItemTypeEyes,
	ItemTypeQuiver,

	ItemTypeMisc,
	ItemTypeCrafting,
};

enum ItemSubType
{
	LightArmor,

};

struct Item
{
	int ItemID;
	std::string Name;
	int ItemType; //slot type
	int GoldValue;
	float Weight;

	//int ItemSubType;
	//int ArmorBonus;
	//int MaxDexBonus;
	//int ArmorPenality;
	//int SpellFailure;
	//int SpeedMod;
};

#define ItemMaxIndex 2000

static Item ItemTable[ItemMaxIndex] = 
{
	//Index  //Power Name						cl tp ut lvl
	{ 0,    "Przeszywanica"   ,  1,  5,  5.0 },
	{ 1,    "Rêkawica"        ,  9,  2,  0.5 },
};

static Item ItemTableArmor[ItemMaxIndex] = 
{
	//Index  //Power Name						cl tp ut lvl
	{ 0, "Zwykly Item", },
	{ 1, "Zwykly Item", },
};

static Item ItemTableWeapon[ItemMaxIndex] = 
{
	//Index  //Power Name						cl tp ut lvl
	{ 0, "Zwykly Item", },
	{ 1, "Zwykly Item", },
};


//static std::string GetPowerName(int Index)
//{
//	for(int i=0; i<PowerMaxIndex; ++i)
//	{
//		if(PowerTable[i].Index == Index)
//			return PowerTable[i].Name;
//	}
//
//	return "No Name At This Index";
//};
//
//static int GetPowerType(int Index)
//{
//	for(int i=0; i<PowerMaxIndex; ++i)
//	{
//		if(PowerTable[i].Index == Index)
//			return PowerTable[i].Type;
//	}
//
//	return NULL;
//};

#endif
