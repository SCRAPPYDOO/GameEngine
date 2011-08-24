#ifndef _CINTERFACECHARACTERCREATOR_H_
	#define _CINTERFACECHARACTERCREATOR_H_

#include "CInterface.h"
#include "CUnit.h"

#define INTERFACE_CHARACTERCREATOR_W 1280
#define INTERFACE_CHARACTERCREATOR_H 720

enum StepType
{
    STEP_RACE,
    STEP_CLASS,
	STEP_ABILITY,
	STEP_SKILLS,
	STEP_FEATS,
	STEP_POWERS,
	STEP_EQUIP,
	STEP_CALCULATE,
	STEP_DETAILS,

    STEP_NAME = 10,
};

enum CharacterCreatorParameters
{
	MAX_RACE = 8,
	MAX_CLASS = 8,
	MAX_ABI	= 8,
};

class CInterfaceCharacterCreator : public CInterface
{
    public:
        CInterfaceCharacterCreator();
        ~CInterfaceCharacterCreator() {}

    public: //Virtual
        bool OnLoad();
		void OnLoop();
		void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();
        void OnButtonActivate(ButtonType Type);

        void LoadStep();
        void CleanupStep();
		void IncreaseAbility();
		void DecreaseAbility();
		void LoadStepSurface();
		void CleanupStepSurface();

		//Step Skills
		void GetTrainedSkills();
		int GetClassSkillPoints();
		void GetAvailableSkills();
		int GetRaceSkillPoints();

    protected:
        int nActualStep;

        SDL_Surface* Surf_StepTitle;

		//Selected Variables
		RaceType Race;
		ClassType Class;

		//Abilitys Step
		int Ability[ABILITY_MAX];  //abilitys for char
		int AbilityPoints;  //points to spend
		AbilityType SelectedAbi;
		SDL_Surface* SurfAbilityPoints;
		SDL_Surface* SurfAbility[ABILITY_MAX]; //surface for showing aabilitys points

		//Step Skills
		int SkillPoints;
		bool Skill[SKILL_MAX];
};

#endif