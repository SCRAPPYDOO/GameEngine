#ifndef _CUNIT_H_
    #define _CUNIT_H_

#include "CObjectUnit.h"
#include "FeatDefines.h"

enum UnitType
{
    ENTITY_TYPE_GENERIC = 0,
    ENTITY_TYPE_PLAYER
};

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

	RACE_NORACE,
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

struct Spell
{
	int SpellIndex;
};

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
		std::vector <Spell> SpellBook;

    protected:
		int UnitID;

        std::string cCharacterName;
        int nActualHealth;
        int nMaxHealth;
        int nCharacterLevel;

		RaceType Race;

		ClassType Class;

		int Ability[ABILITY_MAX];


        int nUnitFlag;
       
    public: //Atributes Methods
		int GetID() const { return UnitID; }

        std::string GetName() const { return cCharacterName; }
        int GetActualHealth() const { return nActualHealth; }
        void SetActualHealth(int nValue) { nActualHealth = nValue; }
        int GetMaxHealth() const { return nMaxHealth; }
        int GetCharacterLevel() const { return nCharacterLevel; }

		void SetRace(RaceType Type) { Race = Type; }
		RaceType GetRace() const { return Race; }
		void SetClass(ClassType Type) { Class = Type; }
		ClassType GetClass() const { return Class; }

		//Abilitys
		int GetAbility(AbilityType Abil) const { return Ability[Abil]; }
		void SetAbility(AbilityType Abil, int nValue) { Ability[Abil] = nValue; }

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
		int GetFeat(int index)
		{
			if(FeatList[index])
				return FeatList[index];

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




		//bool CheckSkill(SkillType SkillT, int DificultyClass);
		//AbilityType GetSkillAbility(SkillType SkillT);





        bool HasFlag(UnitFlag Flag) const { if(nUnitFlag & Flag) return true; return false; }
        void SetFlag(UnitFlag Flag) { nUnitFlag = nUnitFlag | Flag; }

    public: //Def Methods
        bool IsAlive() const { if(nActualHealth > 0) return true; return false; }
};

#endif