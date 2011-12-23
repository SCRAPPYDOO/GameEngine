#ifndef _CUNIT_H_
    #define _CUNIT_H_

#include "CObjectUnit.h"
#include "FeatDefines.h"
#include "PowerDefine.h"
#include "RaceDefine.h"
//#include "CItem.h"
#include "CButton.h"

enum UnitType
{
    ENTITY_TYPE_GENERIC = 0,
    ENTITY_TYPE_PLAYER
};

enum GenderType
{
	GENDER_M,
	GENDER_F,
};

enum AligmentType
{
	AligmentGood,
	AligmentLawfulGood,
	AligmentEvil,
	AligmentChaoticEvil,
	AligmentUnaligned,
};

struct Aligment
{
	int Index;
	std::string Name;
};

static Aligment AligmentTable[5] =
{
	{ 0, "Good"},
	{ 1, "Lawful Good"},
	{ 2, "Evil:"},
	{ 3, "Chaotic Evil"},
	{ 4, "Unaligned:"},
};

enum DeityType
{

};



enum ClassType
{
	CLASS_CLERIC,
	CLASS_FIGHTER,
	CLASS_PALADIN,
	CLASS_RANGER,
	CLASS_ROGUE,
	CLASS_WARLOCK,
	CLASS_WARLORD,
	CLASS_WIZARD,

	CLASS_NOCLASS,
};

enum ParagonClassType
{

};

enum EpicClassType
{

};

enum AbilityType
{
	ABILITY_STRENGHT,
	ABILITY_CONSTITUTION,
	ABILITY_DEXTERITY,
	ABILITY_INTELLIGENCE,
	ABILITY_WISDOM,
	ABILITY_CHARISMA,
	ABILITY_MAX,
};

enum DefenseType
{
	DEF_ARMOR,
	DEF_FORTITUDE,
	DEF_REFLEX,
	DEF_WILL,
};

enum SkillType
{
	SKILL_ACROBATICS = 100,
	SKILL_ARCANA, 
	SKILL_ATHLETICS, 
	SKILL_BLUFF, 
	SKILL_DIPLOMACY, 
	SKILL_DUNGEONEERING, 
	SKILL_ENDURANCE, 
	SKILL_HEAL,
	SKILL_HISTORY,
	SKILL_INSIGHT,
	SKILL_INTIMIDATE, 
	SKILL_NATURE, 
	SKILL_PERCEPTION, 
	SKILL_RELIGION, 
	SKILL_STEALTH, 
	SKILL_STREETWISE,
	SKILL_THIEVERY,
};

enum UnitFlag
{
	ENTITY_FLAG_NONE    = 0x01,
    ENTITY_FLAG_GRAVITY = 0x02,
    ENTITY_FLAG_GHOST   = 0x04,
    ENTITY_FLAG_MAPONLY = 0x08,

    UNIT_FLAG_GOSSIP    = 0x10,
    UNIT_FLAG_VENDOR    = 0x20,
    UNIT_FLAG_LOOTABLE  = 0x40,
};

#define BAG_MAX_X       8
#define BAG_MAX_Y       8

#define MAX_EQUIPED_ITEMS 16

class CItem;

class CUnit : public CObjectUnit
{
    public:
        CUnit();
        ~CUnit() {}

    public:
        bool OnLoad();
        void OnLoop();
        void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();

		std::vector <int> SkillList;
		std::vector <int> FeatList;
		std::vector <int> PowerList;
		std::vector <int> LangList;

		//List of Items In Bag
		CButton* ItemListTable[BAG_MAX_X][BAG_MAX_Y];
		//CItem* ItemList[BAG_MAX_X][BAG_MAX_Y];
		//List of Items Weared On Char
		CButton* ItemEquipedList[MAX_EQUIPED_ITEMS];
		//List of Skills
		std::vector <CButton*> AbilityList;
		//CButton* SkillList


    protected:
		int UnitID;

        std::string cCharacterName;
        int nActualHealth;
        int nMaxHealth;
        int nCharacterLevel;

		RaceType Race;
		SizeType Size;
		ClassType Class;
		ParagonClassType ParagonPath;
		EpicClassType EpicDestiny;
		int Experience;
		int Age;
		GenderType Gender;
		int Height, Weight;
		AligmentType Aligment;
		DeityType Deity;
		VisionType Vision;

		int Speed;

		int Level;
		int Ability[ABILITY_MAX];


        int nUnitFlag;
       
    public: //Atributes Methods
		int GetID() const { return UnitID; }

        std::string GetName() const { return cCharacterName; }
        int GetActualHealth() const { return nActualHealth; }
        void SetActualHealth(int nValue) { nActualHealth = nValue; }
		void ModifyHealth(int nValue) { nActualHealth += nValue; }
        int GetMaxHealth() const { return nMaxHealth; }
        int GetCharacterLevel() const { return nCharacterLevel; }

		//On Race Selection
		void SetRace(RaceType Type);
		RaceType GetRace() const { return Race; }


		void SetClass(ClassType Type);
		ClassType GetClass() const { return Class; }
		void SetClassFeatures();

		//Abilitys
		int GetAbility(AbilityType Abil) const { return Ability[Abil]; }
		void SetAbility(AbilityType Abil, int nValue) { Ability[Abil] = nValue; }
		void IncreaseAbility(AbilityType Abil, int nValue) { Ability[Abil] += nValue; }
		void DecreaseAbility(AbilityType Abil, int nValue) { Ability[Abil] -= nValue; }

		//Skills
		int GetSkill(int index)
		{
			if(SkillList[index])
				return SkillList[index];

			return 0;
		}

		bool IsSkillTrained(int Index) const 
		{ 
			for(int i = 0;i < SkillList.size();i++)
			{
				if(!SkillList[i]) continue;

				if(SkillList[i] == Index)
					return true;
			}

			return false;
		}

		void TrainSkill(int Index)
		{ 
			//If Unit Are Trained Already
			for(int i=0; i<SkillList.size(); ++i)
			{
				if(!SkillList[i]) continue;
				if(SkillList[i] == Index) return;
			}
			SkillList.push_back(Index);
		}

		void UnTrainSkill(int Index)
		{
			for(int i = 0;i < SkillList.size();i++)
			{
				if(!SkillList[i]) continue;

				if(SkillList[i] == Index)
				{
					SkillList.erase(SkillList.begin() + i);
					return;
				}
			}
		}


		//Feats
		int GetFeat(int Index)
		{
			if(FeatList[Index])
				return FeatList[Index];

			return 0;
		}

		bool IsFeatTrained(int Index) const 
		{ 
			for(int i = 0;i < FeatList.size();i++)
			{
				if(!FeatList[i]) continue;

				if(FeatList[i] == Index)
					return true;
			}

			return false;
		}

		void TrainFeat(int Index)
		{ 
			//If Unit Are Trained Already
			for(int i=0; i<FeatList.size(); ++i)
			{
				if(!FeatList[i]) continue;
				if(FeatList[i] == Index) return;
			}
			FeatList.push_back(Index);
		}

		void UnTrainFeat(int Index)
		{
			for(int i = 0;i < FeatList.size();i++)
			{
				if(!FeatList[i]) continue;

				if(FeatList[i] == Index)
				{
					FeatList.erase(FeatList.begin() + i);
					return;
				}
			}
		}

		//Powers
		int GetPower(int Index)
		{
			if(PowerList[Index])
				return PowerList[Index];

			return 0;
		}

		bool IsPowerTrained(int Index)
		{
			for(int i = 0;i < PowerList.size();i++)
			{
				if(!PowerList[i]) continue;

				if(PowerList[i] == Index)
					return true;
			}
			return false;
		}

		void TrainPower(int Index)
		{ 
			//If Unit Are Trained Already
			for(int i=0; i< PowerList.size(); ++i)
			{
				if(!PowerList[i]) continue;
				if(PowerList[i] == Index) return;
			}
			PowerList.push_back(Index);
		}

		void UnTrainPower(int Index)
		{
			for(int i = 0;i < PowerList.size();i++)
			{
				if(!PowerList[i]) continue;

				if(PowerList[i] == Index)
				{
					PowerList.erase(PowerList.begin() + i);
					return;
				}
			}
		}

		//bool CheckSkill(SkillType SkillT, int DificultyClass);
		//AbilityType GetSkillAbility(SkillType SkillT);

		//Abilitys
		int CUnit::GetAbilityMod(AbilityType eAbility) const;

		//Initiative
		int GetInitiativeMod() const;
		int GetInitiative() const;
		//Defenses
		int GetDefense(DefenseType Defense) const;
		//Speed
		void SetSpeed(int nValue) { Speed = nValue; }
		int GetSpeed() const { return Speed; }
		//Languages
		void LearnLanguage(int LangIndex);
		//Size
		SizeType GetSize() const { return Size; }
		VisionType GetVision() const { return Vision; }


        bool HasFlag(UnitFlag Flag) const { if(nUnitFlag & Flag) return true; return false; }
        void SetFlag(UnitFlag Flag) { nUnitFlag = nUnitFlag | Flag; }

    public: //Def Methods
        bool IsAlive() const { if(nActualHealth > 0) return true; return false; }

	//Item Bag Methods Add Delete And Other
	public:
		//void AddItem(CButton* CItemPointer);
};

#endif