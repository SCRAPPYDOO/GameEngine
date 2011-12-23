#include "CInterfaceSkillbook.h"

CInterfaceSkill::CInterfaceSkill()
{
    nPosX = 10;
    nPosY = 10;

    nWidht = 200;
    nHeight = 200;

	ShowSkillFrom = 0;
	ShowSkillTo = 10;

    eInterfaceType = INTERFACE_SKILL;

    for(int i = 0;i < 10; i++) 
    {   
        AbilityName[i] = NULL;
    }
}

bool CInterfaceSkill::OnLoad()
{
    if(CInterface::OnLoad() == false)
        return false;

    for(int i=0; i<3; ++i)
    {
		ButtonType eType;
		int x = 0;
		int y = 0;

        switch(i)
        {
            case 0: eType = BUTTON_SKILL_QUIT; x = nPosX + nWidht - 30  ; y = nPosY; break;
            case 1: eType = BUTTON_SKILL_UP; x = nPosX + nWidht - 30    ; y = nPosY + 40; break;
			case 2: eType = BUTTON_SKILL_DOWN; x = nPosX + nWidht - 30  ; y = nPosY + nHeight - 30; break;	
            default: break;
        }

        CButton *pButton = new CButton(x, y, eType);

        if(pButton->OnLoad() == false)
            break;

        ButtonsList.push_back(pButton);
    }

    return true;
}

void CInterfaceSkill::OnLoop()
{
	CInterface::OnLoop();

	//Set Up Buttons Showed Position
	if(CPlayer::Player.pPlayerCharacter == NULL) return;

	int p = 0;

	for(int n = ShowSkillFrom; n < ShowSkillTo; ++n) 
	{   
		if( n >= CPlayer::Player.pPlayerCharacter->AbilityList.size())
			return;

		int x = nPosX + 10;
		int y = nPosY + p*33;
		//show player skills
		if(!CPlayer::Player.pPlayerCharacter->AbilityList[n]) continue;

		CPlayer::Player.pPlayerCharacter->AbilityList[n]->SetPositionX(x);
		CPlayer::Player.pPlayerCharacter->AbilityList[n]->SetPositionY(y);
		//Show Ability Name on Rightside
		++p;
	}

	CleanUpAbilityName();
	RenderAbilityName();
}

void CInterfaceSkill::OnRender(SDL_Surface* Surf_Display)
{
	CInterface::OnRender(Surf_Display);

	if(CPlayer::Player.pPlayerCharacter == NULL) return;

	for(int n = ShowSkillFrom; n < ShowSkillTo; ++n) 
	{   
		if( n >= CPlayer::Player.pPlayerCharacter->AbilityList.size())
			return;

		//show player skills
		if(!CPlayer::Player.pPlayerCharacter->AbilityList[n]) continue;

		CPlayer::Player.pPlayerCharacter->AbilityList[n]->OnRender(Surf_Display);
		//Show Ability Name on Rightside
	}

    for(int i = 0;i < 10;i++) 
    {  
        if(!AbilityName[i]) continue;

        CSurface::OnDraw(Surf_Display, AbilityName[i], nPosX + 50, nPosY + i * 33); 
    }   

}

void CInterfaceSkill::OnCleanup()
{
    CInterface::OnCleanup();

	CleanUpAbilityName();
}

void CInterfaceSkill::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
	CInterface::OnMouseMove( mX, mY, relX, relY, Left, Right, Middle);

	if(CPlayer::Player.pPlayerCharacter == NULL) return;

	for(int n = ShowSkillFrom; n < ShowSkillTo; ++n) 
	{  
		if( n >= CPlayer::Player.pPlayerCharacter->AbilityList.size())
			return;

		if(!CPlayer::Player.pPlayerCharacter->AbilityList[n]) continue;
		
		CPlayer::Player.pPlayerCharacter->AbilityList[n]->OnMouseMove( mX, mY, relX, relY, Left, Right, Middle);
	}
}

CButton* CInterfaceSkill::GetButton(int nPosX, int nPosY) const
{
	if(CButton* Button = CInterface::GetButton( nPosX, nPosY))
		return Button;

	if(CPlayer::Player.pPlayerCharacter == NULL) return NULL;

	for(int n = ShowSkillFrom; n < ShowSkillTo; ++n) 
	{   
		if( n >= CPlayer::Player.pPlayerCharacter->AbilityList.size())
			return NULL;

		if(!CPlayer::Player.pPlayerCharacter->AbilityList[n]) continue;
		
		if(CPlayer::Player.pPlayerCharacter->AbilityList[n]->IsButtonOnPos(nPosX, nPosY))
			return CPlayer::Player.pPlayerCharacter->AbilityList[n]; 
	}

    return NULL;
}

void CInterfaceSkill::OnButtonActivate(ButtonType Type)
{
    switch(Type)
    {
		//Button Quit
        case 70:
		{
			if(CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_SKILL])
			{
				CInterfaceMenager::InterfaceMenager.CleanUpInterface(INTERFACE_SKILL);
			}
			break;
		}

		//Button Up
		case 71:
		{
			++ShowSkillFrom;
			++ShowSkillTo;
			break;
		}

		//Button Down
		case 72: 
		{
			if(ShowSkillFrom == 0) break;

			--ShowSkillFrom;
			--ShowSkillTo;
			break;
		}

        default: break;
    }
}

void CInterfaceSkill::CleanUpAbilityName()
{
    for(int i=0; i<10; ++i)
    {
        if(AbilityName[i]) 
		    SDL_FreeSurface(AbilityName[i]);

	    AbilityName[i] = NULL;
    } 
}

void CInterfaceSkill::RenderAbilityName()
{
	int i = 0;
	for(int n = ShowSkillFrom; n < ShowSkillTo; ++n) 
	{   
		if( n >= CPlayer::Player.pPlayerCharacter->AbilityList.size())
			return;

		//show player skills
		if(!CPlayer::Player.pPlayerCharacter->AbilityList[n]) continue;

		std::string name = /*"name";*/CPlayer::Player.pPlayerCharacter->AbilityList[n]->GetName();
		AbilityName[i] = CSurface::RenderText(name);  

		++i;
	}
}