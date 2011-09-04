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

	//Race = RACE_NORACE;
	//Class = CLASS_NOCLASS;

	//Abilitys Step
	for(int i=0; i<ABILITY_MAX; ++i)
	{
		if(i > 4)
			Ability[i] = 8;
		else
			Ability[i] = 10;
	}

	SkillPoints = 0;
	AbilityPoints = 22;  //points to spend
	SelectedAbi = ABILITY_STRENGHT;
	SurfAbilityPoints = NULL;

	for(int i=0; i<ABILITY_MAX; ++i)
	{
		SurfAbility[i] = NULL;
	}

	//Step: Feats
	FeatPoints = 1; 

	//Step Power
	AtWillPower = 2;


	pos = 2;
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
	UpdateSurface();
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

	for(int i=0; i<10; ++i)
	{
		if(!Stat[i]) continue;

		CSurface::OnDraw(Surf_Display, Stat[i], 950, 100 + i*35);
	}
	
	//Show Choosen Powers
	for(int i=0; i<PowerTextSurf.size(); ++i)
	{
		if(!PowerTextSurf[i]) continue;

		CSurface::OnDraw(Surf_Display, PowerTextSurf[i], 1050, 100 + i*35);
	}
}

void CInterfaceCharacterCreator::OnCleanup()
{
    CInterface::OnCleanup();
	CleanupStep();

	for(int i=0; i<10; ++i)
	{
		if(Stat[i]) 
			SDL_FreeSurface(Stat[i]);

		Stat[i] = NULL;
	}

	//Show Choosen Powers
	for(int i=0; i<PowerTextSurf.size(); ++i)
	{
		if(PowerTextSurf[i]);
			SDL_FreeSurface(PowerTextSurf[i]);

		PowerTextSurf[i] = NULL;
	}

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
		case BUTTON_CREATECHAR_DRAGONBORN:	Char.SetRace(RACE_DRAGONBORN);	break;
		case BUTTON_CREATECHAR_DWARF:		Char.SetRace(RACE_DWARF);		break;
		case BUTTON_CREATECHAR_ELADRIN:		Char.SetRace(RACE_ELADRIN);		break;
		case BUTTON_CREATECHAR_ELF:			Char.SetRace(RACE_ELF);			break;
		case BUTTON_CREATECHAR_HALFELF:		Char.SetRace(RACE_HALFELF);		break;
		case BUTTON_CREATECHAR_HALFLING:	Char.SetRace(RACE_HALFLING);	break;
		case BUTTON_CREATECHAR_HUMAN:		Char.SetRace(RACE_HUMAN);		break;
		case BUTTON_CREATECHAR_TIEFLING:	Char.SetRace(RACE_TIEFLING);	break;

		case BUTTON_CREATECHAR_CLERIC:		Char.SetClass(CLASS_CLERIC); break;
		case BUTTON_CREATECHAR_FIGHTER:		Char.SetClass(CLASS_FIGHTER); break;
		case BUTTON_CREATECHAR_PALADIN:		Char.SetClass(CLASS_PALADIN); break;
		case BUTTON_CREATECHAR_RANGER:		Char.SetClass(CLASS_RANGER); break;
		case BUTTON_CREATECHAR_ROGUE:		Char.SetClass(CLASS_ROGUE); break;
		case BUTTON_CREATECHAR_WARLOCK:		Char.SetClass(CLASS_WARLOCK); break;
		case BUTTON_CREATECHAR_WARLORD:		Char.SetClass(CLASS_WARLORD); break;
		case BUTTON_CREATECHAR_WIZARD:		Char.SetClass(CLASS_WIZARD); break;

		case BUTTON_CREATECHAR_STR: SelectedAbi = ABILITY_STRENGHT; break;
		case BUTTON_CREATECHAR_CON: SelectedAbi = ABILITY_CONSTITUTION; break;
		case BUTTON_CREATECHAR_DEX: SelectedAbi = ABILITY_DEXTERITY; break;
		case BUTTON_CREATECHAR_INT: SelectedAbi = ABILITY_INTELLIGENCE; break;
		case BUTTON_CREATECHAR_WIS: SelectedAbi = ABILITY_WISDOM; break;
		case BUTTON_CREATECHAR_CHA: SelectedAbi = ABILITY_CHARISMA; break;
		case BUTTON_CREATECHAR_INCREASE: IncreaseAbility(); break;
		case BUTTON_CREATECHAR_DECREASE: DecreaseAbility(); break;

		case BUTTON_CREATECHAR_SKILL_ACROBATICS:
		case BUTTON_CREATECHAR_SKILL_ARCANA:
		case BUTTON_CREATECHAR_SKILL_ATHLETICS:
		case BUTTON_CREATECHAR_SKILL_BLUFF:
		case BUTTON_CREATECHAR_SKILL_DIPLOMACY:
		case BUTTON_CREATECHAR_SKILL_DUNGEONEERING: 
		case BUTTON_CREATECHAR_SKILL_ENDURANCE:
		case BUTTON_CREATECHAR_SKILL_HEAL:
		case BUTTON_CREATECHAR_SKILL_HISTORY:
		case BUTTON_CREATECHAR_SKILL_INSIGHT:
		case BUTTON_CREATECHAR_SKILL_INTIMIDATE:
		case BUTTON_CREATECHAR_SKILL_NATURE:
		case BUTTON_CREATECHAR_SKILL_PERCEPTION:
		case BUTTON_CREATECHAR_SKILL_RELIGION:
		case BUTTON_CREATECHAR_SKILL_STEALTH:
		case BUTTON_CREATECHAR_SKILL_STREETWISE: { SelectSkill(Type); break; }

        default: break;
    }
}

void CInterfaceCharacterCreator::OnButtonActivate(int Type)
{
	//Step: Feats
	if(Type >= HeroicFeatsBegin && Type < HeroicFeatsEnd) 
    {
        SelectFeat(Type); 
    }

	if(Type >= 10000 && Type < PowerIndexMax) 
    {
        SelectPower(Type); 
    }
}

void CInterfaceCharacterCreator::LoadStep()
{
    CleanupStep(); //Cleanup previous step

   //Button Param
	int ButtonIndex = 0;
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

			SkillList.clear();

			GetTrainedSkills();
			GetClassSkillPoints();
			GetAvailableSkills();

			for(int i=0; i<SkillList.size(); ++i)
			{
				if(!SkillList[i]) continue;

				eType = static_cast<ButtonType>(SkillList[i]);
				
				x = 300;
				y = 200 + i*35;

				CButton *pButton = new CButton(x, y, eType);

				if(pButton->OnLoad() == false)
					continue;
 
				ButtonsList.push_back(pButton);
			}

			break;
		}

        case STEP_FEATS: 
		{
			strTitle = "CHOOSE YOUR FEATS";

			FeatList.clear();

			if(Char.GetRace() == RACE_HUMAN)
				FeatPoints = 2; //Humans Gain 2

			GetClassFeatures(); // get all automatic learned feats
			GenerateAvailableFeatsList();

			//show feats without learned feats
			for(int i=0; i<FeatList.size(); ++i)
			{
				if(!FeatList[i]) continue;

				ButtonIndex = FeatList[i];
				
				x = 300;
				y = 200 + i*35;

				CButton *pButton = new CButton(x, y, ButtonIndex);

				if(pButton->OnLoad() == false)
					continue;
 
				ButtonsList.push_back(pButton);
			}

			break;
		}

        case STEP_POWERS: 
		{
			strTitle = "CHOOSE YOUR POWERS";

			AvailablePowerList.clear();
			GetClassPower();
			GenerateAvailablePowerList();

			for(int i=0; i<AvailablePowerList.size(); ++i)
			{
				if(!AvailablePowerList[i]) continue;

				ButtonIndex = AvailablePowerList[i];
				
				x = 300;
				y = 200 + i*35;

				CButton *pButton = new CButton(x, y, ButtonIndex);

				if(pButton->OnLoad() == false)
					continue;
 
				ButtonsList.push_back(pButton);
			}

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

#define MAXSHOW 15
void CInterfaceCharacterCreator::UpdateSurface()
{
	for(int i=0; i<MAXSHOW; ++i)
	{
		if(Stat[i]) 
			SDL_FreeSurface(Stat[i]);

		Stat[i] = NULL;
	}

	/*Render In Right Table all Choosen Atributes*/
	std::string string = GetRaceName(Char.GetRace());
	Stat[0] = CSurface::RenderText("Race: " + string);
	string = GetClassName(Char.GetClass());
	Stat[1] = CSurface::RenderText("Class: " + string);

	pos = 2;
	for(int i=0; i<Char.SkillList.size(); ++i)
	{
		if(!Char.SkillList[i]) continue;

		string = GetSkillName(Char.GetSkill(i));
		Stat[pos] = CSurface::RenderText(string);
		++pos;
	}

	for(int i=0; i<Char.FeatList.size(); ++i)
	{
		if(!Char.FeatList[i]) continue;

		string = GetFeatName(Char.GetFeat(i));
		Stat[pos] = CSurface::RenderText(string);
		++pos;
	}

	//Show Choosen Powers
	for(int i=0; i<PowerTextSurf.size(); ++i)
	{
		if(PowerTextSurf[i]);
			SDL_FreeSurface(PowerTextSurf[i]);

		PowerTextSurf[i] = NULL;
	}

	PowerTextSurf.clear();

	for(int i=0; i<Char.PowerList.size(); ++i)
	{
		if(!Char.PowerList[i]) continue;

		string = GetPowerName(Char.GetPower(i));
		
		PowerTextSurf.push_back(CSurface::RenderText(string));
	}
}

void CInterfaceCharacterCreator::SelectSkill(ButtonType Type)
{
	//If We Already Trained On This Skill
	for(int i=0; i<Char.SkillList.size(); ++i)
	{
		if(!Char.SkillList[i]) continue;

		if(Char.IsSkillTrained(static_cast<int>(Type)))
		{
			Char.UnTrainSkill(static_cast<int>(Type));
			++SkillPoints;
			return;
		}
	}

	if(SkillPoints > 0)
	{
		Char.TrainSkill(static_cast<int>(Type));
		--SkillPoints;
	}
}

//Completed
void CInterfaceCharacterCreator::GetTrainedSkills()
{
	switch(Char.GetClass())
	{
		case CLASS_CLERIC: 
		case CLASS_PALADIN: Char.TrainSkill(113); break;
		case CLASS_RANGER:	Char.TrainSkill(105); Char.TrainSkill(111); break;
		case CLASS_ROGUE:	Char.TrainSkill(114); Char.TrainSkill(116); break;
		case CLASS_WIZARD:	Char.TrainSkill(101); break;
		case CLASS_WARLOCK: 
		case CLASS_WARLORD:
		case CLASS_FIGHTER: break;
		default: break;
	}
}

//Completed
void CInterfaceCharacterCreator::GetClassSkillPoints()
{
	switch(Char.GetClass())
	{
		case CLASS_CLERIC: 
		case CLASS_FIGHTER:
		case CLASS_WIZARD:
		case CLASS_PALADIN: SkillPoints = 3; break;
		case CLASS_RANGER:
		case CLASS_ROGUE: 
		case CLASS_WARLOCK:
		case CLASS_WARLORD: SkillPoints = 4; break;
		default: break;
	}
}

int AvailableSkill[7][8] =
{
	{ 101, 104, 107, 108, 109 }, // Cleric
};

//Completed
void CInterfaceCharacterCreator::GetAvailableSkills()
{
	int index = 0;
	for(int i=0; i<8; ++i)
	{
		switch(Char.GetClass())
		{
			case CLASS_CLERIC:
			{
				switch(i)
				{
					case 0: index = 101; break;
					case 1: index = 104; break;
					case 2: index = 107; break;
					case 3: index = 108; break;
					case 4: index = 109; break;
					default: return;
				}
				break;
			}
			case CLASS_FIGHTER: 
			{
				switch(i)
				{
					case 0: index = 102; break;
					case 1: index = 106; break;
					case 2: index = 107; break;
					case 3: index = 110; break;
					case 4: index = 115; break;
					default: return;
				}
				break;
			}
			case CLASS_PALADIN:
			{
				switch(i)
				{
					case 0: index = 104; break;
					case 1: index = 106; break;
					case 2: index = 107; break;
					case 3: index = 108; break;
					case 4: index = 109; break;
					case 5: index = 110; break;
					default: return;
				}
				break;
			}
			case CLASS_RANGER:
			{
				switch(i)
				{
					case 0: index = 100; break;
					case 1: index = 102; break;
					case 2: index = 106; break;
					case 3: index = 107; break;
					case 4: index = 112; break;
					case 5: index = 114; break;
					default: return;
				}
				break;
			}
			case CLASS_ROGUE:
			{
				switch(i)
				{
					case 0: index = 100; break;
					case 1: index = 102; break;
					case 2: index = 103; break;
					case 3: index = 105; break;
					case 4: index = 109; break;
					case 5: index = 110; break;
					case 6: index = 112; break;
					case 7: index = 115; break;
					default: return;
				}
				break;
			}
			case CLASS_WARLOCK:
			{
				switch(i)
				{
					case 0: index = 101; break;
					case 1: index = 103; break;
					case 2: index = 108; break;
					case 3: index = 109; break;
					case 4: index = 110; break;
					case 5: index = 113; break;
					case 6: index = 115; break;
					case 7: index = 116; break;
					default: return;
				}
				break;
			}
			case CLASS_WARLORD:
			{
				switch(i)
				{
					case 0: index = 102; break;
					case 1: index = 104; break;
					case 2: index = 106; break;
					case 3: index = 107; break;
					case 4: index = 108; break;
					case 5: index = 110; break;
					default: return;
				}
				break;
			}
			case CLASS_WIZARD:
			{
				switch(i)
				{
					case 0: index = 104; break;
					case 1: index = 105; break;
					case 2: index = 108; break;
					case 3: index = 109; break;
					case 4: index = 111; break;
					case 5: index = 113; break;
					default: return;
				}
				break;
			}
			default: break;
		}
		SkillList.push_back(index);
	}
}

void CInterfaceCharacterCreator::GetRaceSkillPoints()
{
}

//### Step:: Feats ###//
void CInterfaceCharacterCreator::SelectFeat(int Type)
{
	//If We Already Trained On This Feat
	for(int i=0; i<Char.FeatList.size(); ++i)
	{
		if(!Char.FeatList[i]) continue;

		if(Char.IsFeatTrained(Type))
		{
			Char.UnTrainFeat(Type);
			++FeatPoints;
			return;
		}
	}

	if(FeatPoints > 0)
	{
		Char.TrainFeat(Type);
		--FeatPoints;
	}
}

int ClassFeatures[6][6] =
{
	{ 1086, 1087, 1088, 1089 }, //cleric
	{  },
};

void CInterfaceCharacterCreator::GetClassFeatures()
{
	for(int i = 0; i<6; ++i)
	{
		Char.TrainFeat(ClassFeatures[Char.GetClass()][i]);
	}
}

void CInterfaceCharacterCreator::GenerateAvailableFeatsList()
{
	//If We Already Trained On This Feat
	for(int FeatIndex = HeroicFeatsBegin; FeatIndex < 1010/*HeroicFeatsEnd*/; ++FeatIndex) //Dopuki nie  posortujemy wyswietlania
	{
		if(!Char.IsFeatTrained(FeatIndex))
		{
			FeatList.push_back(FeatIndex);
		}
	}
}

//### Step:: Powers ###//
void CInterfaceCharacterCreator::SelectPower(int PowerIndex)
{
	//If We Already Trained On This Power
	for(int i=0; i<Char.PowerList.size(); ++i)
	{
		if(!Char.PowerList[i]) continue;

		if(Char.IsPowerTrained(PowerIndex))
		{
			Char.UnTrainPower(PowerIndex);
			++AtWillPower;
			return;
		}
	}

	if(AtWillPower > 0)
	{
		Char.TrainPower(PowerIndex);
		--AtWillPower;
	}
}

void CInterfaceCharacterCreator::GetClassPower()
{
	for(int i = 0; i<6; ++i)
	{
		Char.TrainPower(ClassFeaturePowers[static_cast<int>(Char.GetClass())][i]);
	}
}

void CInterfaceCharacterCreator::GenerateAvailablePowerList()
{
	//int PowerIndexMax = 

	//If We Already Trained On This Feat
	for(int PowerIndex = ClassPowersBeginEnd[Char.GetClass()][0]; PowerIndex < ClassPowersBeginEnd[Char.GetClass()][1]; ++PowerIndex)
	{
		if(!Char.IsPowerTrained(PowerIndex))
		{
			AvailablePowerList.push_back(PowerIndex);
		}
	}
}





//Methods For Text
std::string CInterfaceCharacterCreator::GetRaceName(RaceType Type)
{
	std::string Race = "not choosen yet";
	switch(Type)
	{
		case RACE_DRAGONBORN:	Race = "Dragon Born";	break;
		case RACE_DWARF:		Race = "Dwarf";			break;
		case RACE_ELADRIN:		Race = "Eladrin";		break;
		case RACE_ELF:			Race = "Elf";			break;
		case RACE_HALFELF:		Race = "Half Elf";		break;
		case RACE_HALFLING:		Race = "Halfling";		break;
		case RACE_HUMAN:		Race = "Human";			break;
		case RACE_TIEFLING:		Race = "Tiefling";		break;
		default: break; 
	}
	return Race;
}

std::string CInterfaceCharacterCreator::GetClassName(ClassType Type)
{
	std::string Class = "not choosen yet";
	switch(Type)
	{
		case CLASS_CLERIC:	Class = "Cleric";	break;
		case CLASS_FIGHTER:	Class = "Fighter";	break;
		case CLASS_PALADIN:	Class = "Paladin";	break;
		case CLASS_RANGER:	Class = "Ranger";	break;
		case CLASS_ROGUE:	Class = "Rogue";	break;
		case CLASS_WARLOCK:	Class = "Warlock";	break;
		case CLASS_WARLORD:	Class = "Warlord";	break;
		case CLASS_WIZARD:	Class = "Wizard";	break;
		default: break; 
	}
	return Class;
}

std::string CInterfaceCharacterCreator::GetSkillName(int Index)
{
	std::string string = "error";

	switch(Index)
	{
		case SKILL_ACROBATICS: string = "Acrobatics"; break;
		case SKILL_ARCANA: string = "Arcana"; break;
		case SKILL_ATHLETICS: string = "Athletics"; break;
		case SKILL_BLUFF: string = "Bluff"; break;
		case SKILL_DIPLOMACY: string = "Diplomacy"; break; 
		case SKILL_DUNGEONEERING: string = "Dungeoneering"; break;
		case SKILL_ENDURANCE: string = "Endurance"; break;
		case SKILL_HEAL: string = "Heal"; break;
		case SKILL_HISTORY: string = "History"; break;
		case SKILL_INSIGHT: string = "Insight"; break;
		case SKILL_INTIMIDATE: string = "Intimidate"; break;
		case SKILL_NATURE: string = "Nature"; break;
		case SKILL_PERCEPTION: string = "Perception"; break;
		case SKILL_RELIGION: string = "Religion"; break;
		case SKILL_STEALTH: string = "Stealth"; break;
		case SKILL_STREETWISE: string = "Streetwise"; break;
		case SKILL_THIEVERY: string = "Thievery"; break;
		default: break; 
	}
	return string;
}

std::string CInterfaceCharacterCreator::GetFeatName(int Index)
{
	return FeatName[Index - 1000]; //Table In FeatDefines.h
}