#include "CInterfaceCharacterCreator.h"
#include "CInterfaceMenager.h"

CInterfaceCharacterCreator::CInterfaceCharacterCreator()
{
	OldX = 0;
    OldY = 0;
	eInterfaceType = INTERFACE_CHARACTERCREATOR;

    nPosX = 0;
    nPosY = 0;
    nWidht = INTERFACE_CHARACTERCREATOR_W;
    nHeight = INTERFACE_CHARACTERCREATOR_H;

    nActualStep = 0;
    Surf_StepTitle = NULL;


	//Selected Variables
	Race = RACE_NULL;
	Class = CLASS_NULL;

	//Abilitys Step
	for(int i=0; i<ABILITY_MAX; ++i)
	{
		if(i > 4)
			Ability[i] = 8;
		else
			Ability[i] = 10;
	}

	AbilityPoints = 0;  //points to spend
	SelectedAbi = ABILITY_STRENGHT;
	SurfAbilityPoints = NULL;

	for(int i=0; i<ABILITY_MAX; ++i)
	{
		SurfAbility[i] = NULL;
	}

}

bool CInterfaceCharacterCreator::OnLoad()
{
    if(CInterface::OnLoad() == false)
        return false;

    LoadStep();

    return true;
}

void CInterfaceCharacterCreator::OnLoop()
{
	CInterface::OnLoop();
	CleanupStepSurface();
	LoadStepSurface();
}

void CInterfaceCharacterCreator::OnRender(SDL_Surface* Surf_Display)
{
	CInterface::OnRender(Surf_Display);

	if(Surf_StepTitle)
		CSurface::OnDraw(Surf_Display, Surf_StepTitle, nPosX + 600, nPosY + 50);

	//Abilitys Step
	for(int i=0; i<ABILITY_MAX; ++i)
	{
		if(SurfAbility[i])
			CSurface::OnDraw(Surf_Display, SurfAbility[i], 350, 200 + i*35);
	}

	if(SurfAbilityPoints)
		CSurface::OnDraw(Surf_Display, SurfAbilityPoints, 350, 200 + 7*35);
}

void CInterfaceCharacterCreator::OnCleanup()
{
    CInterface::OnCleanup();
	CleanupStep();
}

void CInterfaceCharacterCreator::OnButtonActivate(ButtonType Type)
{
    switch(Type)
    {
        case BUTTON_CREATECHAR_NEXT:
        {
			CleanupStepSurface();
            ++nActualStep;
            LoadStep();
            break;
        }
        case BUTTON_CREATECHAR_BACK:
        {
			CleanupStepSurface();
            --nActualStep;
            LoadStep();
            break;
        }
        case BUTTON_CREATECHAR_END:
        {
            //SaveChar();
            CInterfaceMenager::InterfaceMenager.CleanUpInterface(INTERFACE_CHARACTERCREATOR);
            CInterfaceMenager::InterfaceMenager.LoadInterface(INTERFACE_MAINMENU);
            break;
        }

		//Choose Race Buttons
		case BUTTON_CREATECHAR_DRAGONBORN: Race = RACE_DRAGONBORN; break;
		case BUTTON_CREATECHAR_DWARF: Race = RACE_DWARF; break;
		case BUTTON_CREATECHAR_ELADRIN: Race = RACE_ELADRIN; break;
		case BUTTON_CREATECHAR_ELF:Race = RACE_ELF; break;
		case BUTTON_CREATECHAR_HALFELF: Race = RACE_HALFELF; break;
		case BUTTON_CREATECHAR_HALFLING:Race = RACE_HALFLING; break;
		case BUTTON_CREATECHAR_HUMAN:Race = RACE_HUMAN; break;
		case BUTTON_CREATECHAR_TIEFLING: Race = RACE_TIEFLING; break;

		case BUTTON_CREATECHAR_CLERIC: Class = CLASS_CLERIC; break;
		case BUTTON_CREATECHAR_FIGHTER: Class = CLASS_FIGHTER; break;
		case BUTTON_CREATECHAR_PALADIN: Class = CLASS_PALADIN; break;
		case BUTTON_CREATECHAR_RANGER: Class = CLASS_RANGER; break;
		case BUTTON_CREATECHAR_ROGUE: Class = CLASS_ROGUE; break;
		case BUTTON_CREATECHAR_WARLOCK: Class = CLASS_WARLOCK; break;
		case BUTTON_CREATECHAR_WARLORD: Class = CLASS_WARLORD; break;
		case BUTTON_CREATECHAR_WIZARD: Class = CLASS_WIZARD; break;

		case BUTTON_CREATECHAR_STR: SelectedAbi = ABILITY_STRENGHT; break;
		case BUTTON_CREATECHAR_CON: SelectedAbi = ABILITY_CONSTITUTION; break;
		case BUTTON_CREATECHAR_DEX: SelectedAbi = ABILITY_DEXTERITY; break;
		case BUTTON_CREATECHAR_INT: SelectedAbi = ABILITY_INTELLIGENCE; break;
		case BUTTON_CREATECHAR_WIS: SelectedAbi = ABILITY_WISDOM; break;
		case BUTTON_CREATECHAR_CHA: SelectedAbi = ABILITY_CHARISMA; break;
		case BUTTON_CREATECHAR_INCREASE: IncreaseAbility(); break;
		case BUTTON_CREATECHAR_DECREASE: DecreaseAbility(); break;

        default: break;
    }
}

void CInterfaceCharacterCreator::LoadStep()
{
    CleanupStep(); //Cleanup previous step

   //Button Param
    ButtonType eType;
    int x;
    int y;

	std::string strTitle = "Error: No Title Found";

    //cleanup Step
    switch(nActualStep)
    {
        case STEP_RACE:
        {
			strTitle = "CHOOSE YOUR RACE";

			for(int i=0; i<MAX_RACE; ++i)
			{
				switch(i)
				{
					case 0: eType = BUTTON_CREATECHAR_DRAGONBORN; break;
					case 1: eType = BUTTON_CREATECHAR_DWARF; break;
					case 2: eType = BUTTON_CREATECHAR_ELADRIN; break;
					case 3: eType = BUTTON_CREATECHAR_ELF; break;
					case 4: eType = BUTTON_CREATECHAR_HALFELF; break;
					case 5: eType = BUTTON_CREATECHAR_HALFLING; break;
					case 6: eType = BUTTON_CREATECHAR_HUMAN; break;
					case 7: eType = BUTTON_CREATECHAR_TIEFLING; break;
				}

				x = 300;
				y = 200 + i*35;

				CButton *pButton = new CButton(x, y, eType);

				if(pButton->OnLoad() == false)
					continue;
 
				ButtonsList.push_back(pButton);
			}
			break;
        }

        case STEP_CLASS: 
		{
			strTitle = "CHOOSE YOUR CLASS";

			for(int i=0; i<MAX_CLASS; ++i)
			{
				switch(i)
				{
					case 0: eType = BUTTON_CREATECHAR_CLERIC; break;
					case 1: eType = BUTTON_CREATECHAR_FIGHTER; break;
					case 2: eType = BUTTON_CREATECHAR_PALADIN; break;
					case 3: eType = BUTTON_CREATECHAR_RANGER; break;
					case 4: eType = BUTTON_CREATECHAR_ROGUE; break;
					case 5: eType = BUTTON_CREATECHAR_WARLOCK; break;
					case 6: eType = BUTTON_CREATECHAR_WARLORD; break;
					case 7: eType = BUTTON_CREATECHAR_WIZARD; break;
				}

				x = 300;
				y = 200 + i*35;

				CButton *pButton = new CButton(x, y, eType);

				if(pButton->OnLoad() == false)
					continue;
 
				ButtonsList.push_back(pButton);
			}

			break;
		}
		
        case STEP_ABILITY: 
		{
			strTitle = "CHOOSE YOUR ABILITYS";

			//AbilityPoints = 22;

			for(int i=0; i<MAX_ABI; ++i)
			{
				switch(i)
				{
					case 0: eType = BUTTON_CREATECHAR_STR; break;
					case 1: eType = BUTTON_CREATECHAR_CON; break;
					case 2: eType = BUTTON_CREATECHAR_DEX; break;
					case 3: eType = BUTTON_CREATECHAR_INT; break;
					case 4: eType = BUTTON_CREATECHAR_WIS; break;
					case 5: eType = BUTTON_CREATECHAR_CHA; break;
					case 6: eType = BUTTON_CREATECHAR_INCREASE; break;
					case 7: eType = BUTTON_CREATECHAR_DECREASE; break;
				}

				x = 300;
				y = 200 + i*35;

				CButton *pButton = new CButton(x, y, eType);

				if(pButton->OnLoad() == false)
					continue;
 
				ButtonsList.push_back(pButton);
			}

			//load modified abilitys via  race and class

			break;
		}

        case STEP_SKILLS: 
		{
			strTitle = "CHOOSE YOUR SKILLS";
			break;
		}

        case STEP_FEATS: 
		{
			strTitle = "CHOOSE YOUR FEATS";
			break;
		}


        case STEP_POWERS: 
		{
			strTitle = "CHOOSE YOUR POWERS";
			break;
		}

        case STEP_EQUIP: 
		{
			strTitle = "CHOOSE YOUR EQUIP";
			break;
		}

        case STEP_CALCULATE: 
		{
			strTitle = "CALCULATING STATS";
			break;
		}

        case STEP_DETAILS: 
		{
			strTitle = "CHOOSE YOUR DETAILS";
			break;
		}

        case STEP_NAME: 
		{
			strTitle = "CHOOSE YOUR NAME";
			break;
		}

        default: break;
    }

    //Load Standard Buttons
    for(int i=0; i<3; ++i)
    {
        switch(i)
        {
            case 0: { if(nActualStep > 10) eType = BUTTON_CREATECHAR_END; eType = BUTTON_CREATECHAR_NEXT; break; }
            case 1: eType = BUTTON_CREATECHAR_BACK; break;
            case 2: eType = BUTTON_CREATECHAR_END; break;
        }

        x = INTERFACE_CHARACTERCREATOR_W * 0.5 + i*35;
        y = INTERFACE_CHARACTERCREATOR_H - 30;

		CButton *pButton = new CButton(x, y, eType);

        if(pButton->OnLoad() == false)
            break;
 
        ButtonsList.push_back(pButton);
    }

	//Load Surfaces(steptyp)

	Surf_StepTitle = CSurface::RenderText(strTitle);
}

void CInterfaceCharacterCreator::CleanupStep()
{
    for(int i = 0;i < ButtonsList.size();i++) 
    {   
        if(!ButtonsList[i]) continue;

        ButtonsList[i]->OnCleanup();
    }

    ButtonsList.clear();

	if(Surf_StepTitle) 
		SDL_FreeSurface(Surf_StepTitle);

	Surf_StepTitle = NULL;
}

void CInterfaceCharacterCreator::IncreaseAbility()
{
	if(Ability[SelectedAbi] > 17 || AbilityPoints == 0) return;

	int Koszt = 20;
	switch(Ability[SelectedAbi])
	{
		default:
		case 8: 
		case 9: 
		case 10:
		case 11: 
		case 12: Koszt = 1; break;
		case 13: 
		case 14: 
		case 15: Koszt = 2; break;
		case 16: Koszt = 3; break;
		case 17: Koszt = 4; break;
	}

	if(AbilityPoints >= Koszt)
	{
		AbilityPoints -= Koszt;
		++Ability[SelectedAbi];
	}
}

void CInterfaceCharacterCreator::DecreaseAbility()
{
	if(Ability[SelectedAbi] < 9 ) return;

	int Koszt = 0;
	switch(Ability[SelectedAbi])
	{
		default:
		case 9:  
		case 10: 
		case 11: 
		case 12: 
		case 13: Koszt = 1; break;
		case 14: 
		case 15: 
		case 16: Koszt = 2; break;
		case 17: Koszt = 3; break;
		case 18: Koszt = 4; break;
	}

	AbilityPoints += Koszt;
	--Ability[SelectedAbi];
}

void CInterfaceCharacterCreator::LoadStepSurface()
{
	switch(nActualStep)
	{
		case STEP_ABILITY:
		{
			for(int i=0; i<ABILITY_MAX; ++i)
			{
				SurfAbility[i] = CSurface::RenderText(Ability[i]);
			}

		    SurfAbilityPoints = CSurface::RenderText(AbilityPoints);

			break;
		}
		default: break;
	}

}

void CInterfaceCharacterCreator::CleanupStepSurface()
{
	switch(nActualStep)
	{
		case STEP_ABILITY:
		{
			for(int i=0; i<ABILITY_MAX; ++i)
			{
				if(SurfAbility[i]) 
					SDL_FreeSurface(SurfAbility[i]);

				SurfAbility[i] = NULL;
			}

			if(SurfAbilityPoints) 
				SDL_FreeSurface(SurfAbilityPoints);

			SurfAbilityPoints = NULL;

			break;
		}
		default: break;
	}
}

void CInterfaceCharacterCreator::GetTrainedSkills()
{
	switch(Class)
	{
		case CLASS_CLERIC:
		{
			Skill[SKILL_RELIGION] = true;
			break;
		}
		case CLASS_FIGHTER:
		case CLASS_PALADIN:
		case CLASS_RANGER:
		case CLASS_ROGUE:
		case CLASS_WARLOCK:
		case CLASS_WARLORD:
		case CLASS_WIZARD:
		default: break;
	}
}

int CInterfaceCharacterCreator::GetClassSkillPoints()
{
}
void CInterfaceCharacterCreator::GetAvailableSkills()
{
}
int CInterfaceCharacterCreator::GetRaceSkillPoints()
{
}