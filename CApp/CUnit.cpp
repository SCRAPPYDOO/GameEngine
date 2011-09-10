#include "CUnit.h"
#include "CUnitMenager.h"
#include "CInterface.h"
#include "CInterfaceMenager.h"
#include "CDice.h"
#include "RaceDefine.h"

CUnit::CUnit()
{
    Surf_Unit = NULL;

    fPosX = 50;
    fPosY = 50;
    nWidth = 50;
    nHeight = 50;

    fRadius = 0;  //radius of colision box
    fGoX = 0;   // destination point
    fGoY = 0;   
    fNewX = 0;  //position where we are going to
    fNewY = 0;  
    fSpeed = 0; 

    nUnitFlag = 0;
    nUnitMovementFlag = 0;

    CurrentFrameCol = 0;
    CurrentFrameRow = 0;

	Level = 1;

	for(int i=0; i<ABILITY_MAX; ++i)
	{
		if(i > 4)
			Ability[i] = 8;
		else
			Ability[i] = 10;
	}

	LangList.clear();
}

bool CUnit::OnLoad() 
{
    CObjectUnit::OnLoad();

    if((Surf_Unit = CSurface::OnLoad("./anim/1.png")) == NULL) 
    {
        //CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Unit Image Not Loaded");
        return false;
    }

    nUnitFlag = nUnitFlag | UNIT_FLAG_GOSSIP | UNIT_FLAG_LOOTABLE;

    //CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Unit Image Loaded");

    return true;
}

void CUnit::OnLoop() 
{
    CObjectUnit::OnLoop();
}

void CUnit::OnRender(SDL_Surface* Surf_Display) 
{
    CObjectUnit::OnRender(Surf_Display);
}

void CUnit::OnCleanup() 
{
    CObjectUnit::OnCleanup();
}

void CUnit::SetRace(RaceType Type) 
{ 
	Race = Type;
	Size = GetRaceSize(Race);
	Speed = GetRaceSpeed(Race);
	Vision = GetRaceVision(Race);

	LangList.clear();
	LearnLanguage(LangCommon);
	LearnLanguage(GetRaceLang(Race));

	//BUG:: Staty dodaja sie kilka razy podczas powrotu
	if(Race != RACE_HUMAN)
	{
		Ability[GetRaceAbility(Race)] +=2;
		Ability[GetRaceAbility(Race,1)] +=2;
	}

	//if(Race == RACE_DRAGONBORN)
	//	TrainPower(PowerDragonBreath);
}

void CUnit::LearnLanguage(int LangIndex)
{
	for(int i=0; i< LangList.size(); ++i)
	{
		if(!LangList[i]) continue;
		if(LangList[i] == LangIndex) return;
	}	
	LangList.push_back(LangIndex);
}

void CUnit::SetClass(ClassType Type) 
{ 
	Class = Type; 

}

//Abilitys
int CUnit::GetAbilityMod(AbilityType eAbility) const
{
    int nMod;

    switch(Ability[eAbility])
    {
          case 1: nMod = -5; break;
          case 2: nMod = -4; break;       
          case 3: nMod = -4; break;
          case 4: nMod = -3; break;
          case 5: nMod = -3; break;
          case 6: nMod = -2; break;
          case 7: nMod = -2; break;
          case 8: nMod = -1; break;
          case 9: nMod = -1; break;
          case 10: nMod = 0; break;
          case 11: nMod = 0; break;
          case 12: nMod = 1; break;
          case 13: nMod = 1; break;
          case 14: nMod = 2; break;
          case 15: nMod = 2; break;
          case 16: nMod = 3; break;
          case 17: nMod = 3; break;
          case 18: nMod = 4; break;
          case 19: nMod = 4; break;
          case 20: nMod = 5; break;
          case 21: nMod = 5; break;
          case 22: nMod = 6; break;
          case 23: nMod = 6; break;
          case 24: nMod = 7; break;
          case 25: nMod = 7; break;   
          case 26: nMod = 8; break;
          case 27: nMod = 8; break;
          case 28: nMod = 9; break;
          case 29: nMod = 9; break;
          case 30: nMod = 10; break;
          default: nMod = 0; break;
    };
    
    return nMod;
};

//Initiative
int CUnit::GetInitiativeMod() const
{
	int Basic = 0.5 * Level + GetAbilityMod(ABILITY_DEXTERITY);
	int Mod = 0;

	//Aditional Bonuses
	Mod = 0;

	Basic += Mod;
	return Basic;
}

int CUnit::GetInitiative() const
{
	int Basic = RollDice(1, D20);
	int Mod = GetInitiativeMod();

	Basic += Mod;
	return Basic;
}

//Defenses
int CUnit::GetDefense(DefenseType Defense) const
{
	int Basic = 10 + 0.5 * Level;
    int nDefense, nRacialBonus, nFeatBonus = 0, nPowerBonus = 0, nClassBonus = 0;

    switch(Defense)
    {
         case DEF_ARMOR:
         {        
               //nDefense = nArmorBonus + nShieldBonus;       
               //if(GetArmorType() == ARMOR_LIGHT)
               //{
               //    if(CharAbility.nDexterity > CharAbility.nIntelligence)
               //        nDefense = +GetAbilityMod(AB_DEXTERITY); 
               //    else
               //        nDefense = +GetAbilityMod(AB_INTELIGENCE);                               
               //};
               break;
         };
         case DEF_REFLEX:
         {   
               //if(CharAbility.nDexterity > CharAbility.nIntelligence)
               //    nDefense = GetAbilityMod(AB_DEXTERITY); 
               //else
               //    nDefense = GetAbilityMod(AB_INTELIGENCE);
               //
               //if(eClass == CLASS_RANGER)
               //    nClassBonus = 1;
               //if(IsEqupped(EQUIP_SHIELD)
               //   add bonus from shield to defense roll
               //nDefense = +GetBonus(BONUS_SHIELD, NULL_BONUS);    
               break;
         };
         case DEF_FORTITUDE: 
         {
               //if(CharAbility.nStrength > CharAbility.nConstitution)             
               //    nDefense = GetAbilityMod(AB_STRENGHT); 
               //else
               //    nDefense = GetAbilityMod(AB_CONSTITUTION);
               //    
               //if(eClass == CLASS_FIGHTER)
               //    nClassBonus = 2;    
               //    
               //if(eClass == CLASS_RANGER)
               //    nClassBonus = 1;          
               break;
         };
         
         case DEF_WILL:
         {   
               //if(CharAbility.nCharisma > CharAbility.nWisdom)
               //    nDefense = GetAbilityMod(AB_CHARISMA); 
               //else
               //    nDefense = GetAbilityMod(AB_WISDOM);
               ////+1 eladrin_race racial bonus
               //if(eRace == RACE_ELADRIN)
               //    nRacialBonus = 1; 
               //if(eClass == CLASS_CLERIC)
               //    nClassBonus = 2;      
               break;
         };          
    };
    
    ////Bold: You gain a +5 racial bonus to saving throws against fear. 
    //if(eRace == RACE_HALFLING && pPower->HaveEffectType(PWR_EFF_FEAR) && eDefense != DEFENSE_AC)
    //    nRacialBonus = 5;
    //    
    ////Eladrin Will:In addition, you gain a +5 racial bonus to saving throws against charm effects. 
    //if(eRace == RACE_ELADRIN && pPower->HaveEffectType(PWR_EFF_CHARM) && eDefense != DEFENSE_AC)
    //    nRacialBonus = 5;
    //    
    ////Cast-Iron Stomach: +5 racial bonus to saving throws against poison.
    //if(eRace == RACE_DWARF && eDefense != DEFENSE_AC && (pPower->HaveDamageType(PWR_DMG_POISON) || pPower->HaveEffectType(PWR_EFF_POISON)))
    //    nRacialBonus = 5;

    ////Human Defense Bonuses: +1 to Fortitude, Reflex, and Will defenses.
    //if(eRace == RACE_HUMAN && eDefense != DEFENSE_AC)
    //    nRacialBonus = 1;
    //    
    ////Paladins Bonus to Defense: +1 Fortitude, +1 Reflex, +1 Will    
    //if(eClass == CLASS_PALADIN && eDefense != DEFENSE_AC)
    //    nClassBonus = 1;    

    //You gain a +2 bonus to AC against opportunity attacks.
    //if(GetFeat(DEFENSIVE_MOBILITY))
        //nDefense = +2;  


	//Aditional Bonuses
	int Mod = 0;

	return Basic;
}
