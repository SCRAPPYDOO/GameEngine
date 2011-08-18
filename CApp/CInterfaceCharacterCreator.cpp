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


}

void CInterfaceCharacterCreator::OnRender(SDL_Surface* Surf_Display)
{
	CInterface::OnRender(Surf_Display);

	if(Surf_StepTitle)
		CSurface::OnDraw(Surf_Display, Surf_StepTitle, nPosX + 600, nPosY + 50);
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
            ++nActualStep;
            LoadStep();
            break;
        }
        case BUTTON_CREATECHAR_BACK:
        {
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

		case BUTTON_CREATECHAR_STR_PLUS: IncreaseAbility(ABILITY_STRENGHT); break;
		case BUTTON_CREATECHAR_STR_MINUS:DecreaseAbility(ABILITY_STRENGHT); break;
		case BUTTON_CREATECHAR_CON_PLUS: IncreaseAbility(ABILITY_CONSTITUTION); break;
		case BUTTON_CREATECHAR_CON_MINUS:DecreaseAbility(ABILITY_CONSTITUTION); break;
		case BUTTON_CREATECHAR_DEX_PLUS: IncreaseAbility(ABILITY_DEXTERITY); break;
		case BUTTON_CREATECHAR_DEX_MINUS:DecreaseAbility(ABILITY_DEXTERITY); break;
		case BUTTON_CREATECHAR_INT_PLUS: IncreaseAbility(ABILITY_INTELLIGENCE); break;
		case BUTTON_CREATECHAR_INT_MINUS:DecreaseAbility(ABILITY_INTELLIGENCE); break;
		case BUTTON_CREATECHAR_WIS_PLUS: IncreaseAbility(ABILITY_WISDOM); break;
		case BUTTON_CREATECHAR_WIS_MINUS:DecreaseAbility(ABILITY_WISDOM); break;
		case BUTTON_CREATECHAR_CHA_PLUS: IncreaseAbility(ABILITY_CHARISMA); break;
		case BUTTON_CREATECHAR_CHA_MINUS:DecreaseAbility(ABILITY_CHARISMA); break;

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

			AbilityPoints = 22;
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

void CInterfaceCharacterCreator::IncreaseAbility(AbilityType Abi)
{
	if(Ability[Abi] > 17 || AbilityPoints == 0) return;

	int Koszt = 20;
	switch(Ability[Abi])
	{
		default:
		case 8: 
		case 9:  Koszt = 1; break;
		case 10: Koszt = 1; break;
		case 11: Koszt = 2; break;
		case 12: Koszt = 3; break;
		case 13: Koszt = 5; break;
		case 14: Koszt = 7; break;
		case 15: Koszt = 9; break;
		case 16: Koszt = 12; break;
		case 17: Koszt = 16; break;
	}

	if(AbilityPoints >= Koszt)
	{
		AbilityPoints -= Koszt;
		++Ability[Abi];
	}
}

void CInterfaceCharacterCreator::DecreaseAbility(AbilityType Abi)
{
	if(Ability[Abi] < 9 ) return;

	int Koszt = 0;
	switch(Ability[Abi])
	{
		default:
		case 9:  
		case 10: 
		case 11: Koszt = 1; break;
		case 12: Koszt = 2; break;
		case 13: Koszt = 3; break;
		case 14: Koszt = 5; break;
		case 15: Koszt = 7; break;
		case 16: Koszt = 9; break;
		case 17: Koszt = 12; break;
		case 18: Koszt = 16; break;
	}

	AbilityPoints += Koszt;
	--Ability[Abi];
}

void CInterfaceCharacterCreator::LoadStepSurface()
{
	switch(nActualStep)
	{
		case STEP_ABILITY:
		{
			break;
		}
		default: break;
	}



}

void CInterfaceCharacterCreator::CleanupStepSurface()
{



}