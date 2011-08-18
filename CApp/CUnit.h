#ifndef _CUNIT_H_
    #define _CUNIT_H_

#include "CObjectUnit.h"

enum UnitType
{
    ENTITY_TYPE_GENERIC = 0,
    ENTITY_TYPE_PLAYER
};

enum RaceType
{
	RACE_NULL,
	RACE_DRAGONBORN,
	RACE_DWARF,
	RACE_ELADRIN,
	RACE_ELF,
	RACE_HALFELF,
	RACE_HALFLING,
	RACE_HUMAN,
	RACE_TIEFLING,
};

enum ClassType
{
	CLASS_NULL,
	CLASS_CLERIC,
	CLASS_FIGHTER,
	CLASS_PALADIN,
	CLASS_RANGER,
	CLASS_ROGUE,
	CLASS_WARLOCK,
	CLASS_WARLORD,
	CLASS_WIZARD,
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
};

#define MAX_ABILITY 6

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

    protected:
        std::string cCharacterName;
        int nActualHealth;
        int nMaxHealth;
        int nCharacterLevel;

		RaceType Race;
		ClassType Class;
		int Ability[MAX_ABILITY];

        int nUnitFlag;
       
    public: //Atributes Methods
        std::string GetName() const { return cCharacterName; }
        int GetActualHealth() const { return nActualHealth; }
        void SetActualHealth(int nValue) { nActualHealth = nValue; }
        int GetMaxHealth() const { return nMaxHealth; }
        int GetCharacterLevel() const { return nCharacterLevel; }

		RaceType GetRace() const { return Race; }
		ClassType GetClass() const { return Class; }
		int GetAbility(AbilityType Abil) const { return Ability[Abil]; }
		void SetAbility(AbilityType Abil, int nValue) { Ability[Abil] = nValue; }

        bool HasFlag(UnitFlag Flag) const { if(nUnitFlag & Flag) return true; return false; }
        void SetFlag(UnitFlag Flag) { nUnitFlag = nUnitFlag | Flag; }

    public: //Def Methods
        bool IsAlive() const { if(nActualHealth > 0) return true; return false; }
};

#endif