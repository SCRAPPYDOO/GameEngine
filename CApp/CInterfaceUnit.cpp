#include "CInterfaceUnit.h"


CInterfaceUnit::CInterfaceUnit()
{
    pUnit               = NULL; 
    nHealth             = 0;
    nMaxHealth          = 0;
    nHealthBarRange     = 0;
    Surf_UnitStatus     = NULL;
    Surf_UnitImage      = NULL;
    Surf_UnitName       = NULL;
    Surf_Percentage     = NULL; 
    eInterfaceType      = INTERFACE_PLAYERINFO;

	pTarget = NULL;
    nTargetHealth= 0;
    nTargetMaxHealth= 0;
    nTargetHealthBarRange= 0;

    Surf_TargetUnitName = NULL;
    Surf_TargetUnitImage = NULL;
}

CInterfaceUnit::CInterfaceUnit(InterfaceType eType)
{
    pUnit               = NULL;      
    nHealth             = 0;
    nMaxHealth          = 0;
    nHealthBarRange     = 0;
    Surf_UnitStatus     = NULL;
    Surf_UnitImage      = NULL;
    Surf_UnitName       = NULL;
    Surf_Percentage     = NULL; 
    eInterfaceType = eType;

	pTarget = NULL;
    nTargetHealth= 0;
    nTargetMaxHealth= 0;
    nTargetHealthBarRange= 0;

    Surf_TargetUnitName = NULL;
    Surf_TargetUnitImage = NULL;

}

bool CInterfaceUnit::OnLoad()
{
    if(CInterface::OnLoad() == false) 
        return false;

    if((Surf_UnitStatus = CSurface::OnLoad("./interface/interface_unitinfo_status.png")) == NULL) 
        return false;

    UpdateUnit();

    if(pUnit)
    {
        std::string name = pUnit->GetName();

        Surf_UnitName = CSurface::RenderText(name);

        /*Surf_UnitImage = CPlayer::Player.pPlayerCharacter->GetImage();*/
    }

    return true;
}

void CInterfaceUnit::OnLoop()
{
    CInterface::OnLoop();

	CleanUpTargetSurf();
    CleanUpHealthBar();

    UpdateUnit();

	UpdateTarget();

    UpdateHealth();
}

void CInterfaceUnit::OnRender(SDL_Surface* Surf_Display)
{
    if(Surf_Display == NULL) return;

    CInterface::OnRender(Surf_Display);

    if(Surf_UnitImage)
        CSurface::OnDraw(Surf_Display, NULL /*CApp::pSelectedUnit->GetPortraitSurf()*/, nPosX + 26, nPosY + 39); // selected unit image

    if(Surf_UnitStatus)
        CSurface::OnDraw(Surf_Display, Surf_UnitStatus, nPosX, nPosY + INTERFACE_PLAYERINFO_H - HEALTHBARHEIGHT, 0, 0, nHealthBarRange, HEALTHBARHEIGHT); //hp

    if(Surf_Percentage)
        CSurface::OnDraw(Surf_Display, Surf_Percentage, nPosX + 0.5 * INTERFACE_PLAYERINFO_H, nPosY + INTERFACE_PLAYERINFO_H); //hp

    if(Surf_UnitName)
        CSurface::OnDraw(Surf_Display, Surf_UnitName, nPosX, nPosY + 60); 

	if(pTarget)
	{
		if(Surf_TargetUnitImage)
			CSurface::OnDraw(Surf_Display, NULL /*CApp::pSelectedUnit->GetPortraitSurf()*/, nPosX + 26, nPosY + 39); // selected unit image

		if(Surf_UnitStatus)
			CSurface::OnDraw(Surf_Display, Surf_UnitStatus, nPosX + 600, nPosY + INTERFACE_PLAYERINFO_H - HEALTHBARHEIGHT, 0, 0, nTargetHealthBarRange, HEALTHBARHEIGHT); //hp

		if(Surf_TargetHealthPercText)
			CSurface::OnDraw(Surf_Display, Surf_TargetHealthPercText, nPosX + 600 + 0.5 * INTERFACE_PLAYERINFO_H, nPosY + INTERFACE_PLAYERINFO_H); //hp

		if(Surf_TargetUnitName)
			CSurface::OnDraw(Surf_Display, Surf_TargetUnitName, nPosX + 700, nPosY + 60); 
	}
}

void CInterfaceUnit::OnCleanup()
{
	CInterface::OnCleanup();

	CleanUpPlayerSurf();
	CleanUpTargetSurf();

    if(Surf_UnitStatus)
        SDL_FreeSurface(Surf_UnitStatus);

    Surf_UnitStatus = NULL;

    CleanUpHealthBar();
}

void CInterfaceUnit::CleanUpPlayerSurf()
{
    if(Surf_UnitImage)
        SDL_FreeSurface(Surf_UnitImage);

    if(Surf_UnitName)
        SDL_FreeSurface(Surf_UnitName);

    Surf_UnitName = NULL;
    Surf_UnitImage = NULL;
}

void CInterfaceUnit::CleanUpTargetSurf()
{
    if(Surf_TargetUnitImage)
        SDL_FreeSurface(Surf_TargetUnitImage);

    if(Surf_TargetUnitName)
        SDL_FreeSurface(Surf_TargetUnitName);

	if(Surf_TargetHealthPercText)
        SDL_FreeSurface(Surf_TargetHealthPercText);

    Surf_TargetHealthPercText = NULL;
    Surf_TargetUnitName = NULL;
    Surf_TargetUnitImage = NULL;
}

void CInterfaceUnit::CleanUpHealthBar()
{
    if(Surf_Percentage)
        SDL_FreeSurface(Surf_Percentage);

    Surf_Percentage = NULL;
}

void CInterfaceUnit::UpdateHealth()
{
    if(!pUnit) return;

    nHealth = pUnit->GetActualHealth();
    nMaxHealth = pUnit->GetMaxHealth();
    nHealthBarRange = nHealth / (nMaxHealth / HEALTHBARRANGE);  

    Surf_Percentage = CSurface::RenderText(nHealthBarRange);
}

void CInterfaceUnit::UpdateUnit()
{
    if(CPlayer::Player.pPlayerCharacter != NULL)
        pUnit = CPlayer::Player.pPlayerCharacter;
    else pUnit = NULL;
}

void CInterfaceUnit::UpdateTarget()
{
	if(CPlayer::Player.pTargetedUnit != NULL)
        pTarget = CPlayer::Player.pTargetedUnit;
    else 
	{
		pTarget = NULL;
		CleanUpTargetSurf();
		return;
	}

    std::string name = pTarget->GetName();

    Surf_TargetUnitName = CSurface::RenderText(name);

    /*Surf_TargetUnitImage = pTarget->GetImageID();*/

    nTargetHealth = pTarget->GetActualHealth();
    nTargetMaxHealth = pTarget->GetMaxHealth();
    nTargetHealthBarRange = nTargetHealth / (nTargetMaxHealth / HEALTHBARRANGE);  

    Surf_TargetHealthPercText = CSurface::RenderText(nTargetHealthBarRange);
}

bool CInterfaceUnit::AddButtonToSlot(CButton* pButton, int mX, int mY)
{
	//Only Items Can Be Added To Equpment
 //   if(pButton->GetButtonClass() != BUTTONCLASS_ITEM)
	//{
	//	if(CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW])
	//		CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Mozes Dodac Do Equip Tylko Item");

 //       return false;
	//}

    //For bag slots
    for(int x = 0; x < SLOT_MAX_X; ++x) 
    {   
        for(int y = 0; y < SLOT_MAX_Y; ++y) 
        {   
            if( ( mX > nPosX + 170 + x*30) && ( mX < nPosX + 170 + x*30 + SLOT_W_H) && ( mY > nPosY + 40 + y*30 ) && ( mY < nPosY + 40 + y*30 + SLOT_W_H) )
            {      
                //ToDo: Need to check if on slot is any other button delete this button and add new button
                if(CButton *Button = GetButton(mX, mY))
                    if(Button != NULL)
                        CInterface::DeleteButtonFromSlot(Button);
				
				int nX = nPosX + 170 + x*30;
				int nY = nPosY + 40 + y*30;

				//Check If Button Is Already In Same Interface Just Change Place
				//Prevent Double Add 1 Button to Button List
				for(int i = 0;i < ButtonsList.size();i++) 
				{   
					if(!ButtonsList[i]) continue;
					if(ButtonsList[i] == pButton)
					{
						pButton->SetPositionX(nX);
						pButton->SetPositionY(nY);
						return true;
					}
				}

				//If Slot Is Empty We SetUp Porper Coordinates To Button
				CButton* pButtonShortcut = new CButtonShortcut(pButton);

				if(CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW])
					CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("DEBUG: Stworzono Shortcut Do Buttona");

                pButtonShortcut->SetPositionX(nX);
                pButtonShortcut->SetPositionY(nY);

                if(pButtonShortcut->OnLoad() == false)
					return false;

                ButtonsList.push_back(pButtonShortcut);
				if(CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW])
					CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("DEBUG: Dodano Shortcut do Listy butonow Interfacu");
                return false;
            }
        }
    }

	return false;
}