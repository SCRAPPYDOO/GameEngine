#include "CApp.h"

void CApp::OnEvent(SDL_Event* Event) 
{
    CEvent::OnEvent(Event);
}

void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) 
{
    switch(sym)
    {
        case SDLK_ESCAPE: 
        {
            switch(CApp::eGameState)
            {
                case TEST:
                {
			        if(!CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_GAMEMENU])
			        {
				        CInterfaceMenager::InterfaceMenager.LoadInterface(INTERFACE_GAMEMENU);
			        }
			        else
				        CInterfaceMenager::InterfaceMenager.CleanUpInterface(INTERFACE_GAMEMENU);

                    break;
                }

                default: break;
            }
            
            
        }

        default: break;
    }
}

void CApp::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) 
{
}

void CApp::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{ 
	//Send Masage That Mouse is Over Target and Need to Show Short Info
	if(CApp::eGameState == TEST)
	{
		if(CUnit* pUnit = CUnitMenager::GetUnit(mX, mY))
		{
			CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_INFOWINDOW]->AddUnitPointer(pUnit);
		}
		else
		{
			CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_INFOWINDOW]->AddUnitPointer(NULL);
		}
	}

	//UpdateInterface()
	//{

    //ToDo: Change cursor image when move on different objects
    if(!Left)
	{
        if(CInterface* pInterface = CInterfaceMenager::InterfaceMenager.GetInterface(mX, mY))
             if(pInterface)
                 pInterface->OnMouseMove(mX, mY, relX, relY, Left, Right, Middle);

        //Interface
        //Entitys
        //StaticObjects

        if(CUnit* pUnit = CUnitMenager::GetUnit(mX, mY))
        {
 
        }
    }
    else
    {
        if(pSelectedButton != NULL && (pSelectedButton->GetButtonState() == BUTTONSTATE_SELECTED || pSelectedButton->GetButtonState() == BUTTONSTATE_MOVED) && !pSelectedButton->HasFlag(BUTTONFLAG_NOTMOVED) )
        {
            if(pSelectedButton->GetButtonState() != BUTTONSTATE_MOVED)
            {
				pSelectedButton->SetButtonState(BUTTONSTATE_MOVED);
                //Save our current positions -> used in Button->OnDrop()
                //pSelectedButton->SaveCurrentPosition();

                //if(CInterface* pInterface = CInterfaceMenager::InterfaceMenager.GetInterface(mX, mY))
                //{
                //    pInterface->DeleteButtonFromSlot(pSelectedButton);
                //}
            }

            //pSelectedButton->OnMove(mX, mY);

            return;                
        }

		//Interface Move Part
        //if(pSelectedInterface != NULL)
        //{
        //    pSelectedInterface->OnMove(mX, mY);
        //    return;
        //}
    }
}

void CApp::OnRButtonDown(int mX, int mY)
{
    //if(CApp::eGameState == MAIN_MENU) //We Dont Use RButton In Menu                                       
    //    return;

	//Unit Targeting
    if(CUnit* pUnit = CUnitMenager::GetUnit(mX, mY))
    {
		if(CPlayer::Player.pPlayerCharacter != pUnit)
		{
			CPlayer::Player.pTargetedUnit = pUnit;
			CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("DEBUG: Target Unit");
		}
		else
			CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("DEBUG: Targetet Unit is Player Unit");
	}
	else 
	{
		if(CPlayer::Player.pTargetedUnit != NULL)
		{
			CPlayer::Player.pTargetedUnit = NULL;
			CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("DEBUG: Targetet Unit Removed");
		}
		else
			CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("DEBUG: No Any Units To Target");
	}
}

void CApp::OnRButtonUp(int mX, int mY)
{
	//if is loot asand klik nie byl na  loot delete  okno lootu
    if(CUnit* pUnit = CUnitMenager::GetUnit(mX, mY))
    {
        if(pUnit)
        {
			if(CPlayer::Player.nSelectedSpell != 0)
			////	SelectedPlayer->CastSpel->SelectedSApell
            //if(pUnit->IsEnemy())
            //{
                 /* CanAttack();*/  
            //    return;
            //}

            if(/*!pUnit->IsAlive() &&*/ pUnit->HasFlag(UNIT_FLAG_LOOTABLE))
            {
				//Open okno Lootu o ID mobka a jezlei nie  istnieje stworz
				//Prevent przed podwojnym stworzeniem lootu
				if(CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_LOOT] != NULL) return;

				CInterfaceMenager::InterfaceMenager.LoadInterface(INTERFACE_LOOT);
				CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_LOOT]->LoadLoot(pUnit->GetID());
                CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Looting Corps");
                return;
            }

            //If Chat Available
            if(pUnit->HasFlag(UNIT_FLAG_GOSSIP))
            {
                //ToDo: Create Chat Window Load Gossip by Unit ID
                CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Wlaczam Gossip");
                return;
            }
        }
    }
}

void CApp::OnLButtonDown(int x,int y)
{
    CInterface* pInterface = NULL;
    if(pInterface = CInterfaceMenager::InterfaceMenager.GetInterface(x, y))
    {
        if(pInterface)
        {
			//Move Interface to 1st position on the list for proper showing it on main screen
			//CInterfaceMenager::InterfaceMenager.MoveInterface(pInterface);

            if(pSelectedButton = pInterface->GetButton(x, y))
            {
				pOldButtonInterface = pInterface;
				pSelectedMovedButton = pSelectedButton;
				if(CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW])
					CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Zapisano Uchwyt Do Interfacu i Buttona");

                if(pSelectedButton != NULL)
                {
                    pSelectedButton->SetButtonState(BUTTONSTATE_SELECTED);
                    pSelectedButton->SetAnimationState(BUTTON_ANIME_ONCLICK);
                    pSelectedButton->SetDistance(x,y);
                    return;
                }
            }
        }
    }
                    
    if(pSelectedInterface = CInterfaceMenager::InterfaceMenager.GetInterface(x,y))
    {
        if(pSelectedInterface != NULL)
        {

            pSelectedInterface->SetDistance(x,y);
            return;
        }
    }

	if(CPlayer::Player.pPlayerCharacter)
		CPlayer::Player.pPlayerCharacter->OnMoveToPoint(x,y);

	//CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Ide Do Pktu");

    //if(CUnit* pUnit = CUnitMenager::GetUnit(x, y))
    //    if(pUnit)
    //        ////if(pUnit == CPlayer::Player.pSelectedUnit)
    //        ////{
    //        ////    return;
    //        ////}
    //        ////else
    //        ////{
    //            CPlayer::Player.pTargetedUnit = pUnit;
    //        //}
}

void CApp::OnLButtonUp(int x,int y)
{
	if(pOldButtonInterface)
	{
		if(pSelectedMovedButton)
		{
			if(pSelectedInterface = CInterfaceMenager::InterfaceMenager.GetInterface(x,y))
			{
				if(pSelectedInterface->AddButtonToSlot(pSelectedMovedButton, x, y))
				{
					if(pOldButtonInterface != pSelectedInterface)
					{
						pOldButtonInterface->DeleteButtonFromSlot(pSelectedMovedButton);
						if(CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW])
							CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Dodano Button Do Nowego Interfacu");
					}
					else
					{
						if(CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW])
							CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Tem Sam Interface");
					}
					//pOldButtonInterface->DeleteButtonFromSlot(pSelectedMovedButton);			
				}
				else
				{
					if(CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW])
						CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Nie Dodano Button Do Nowego Interfacu");
				}
			}
			//If We Drop Button Not On Any Interface
			else
			{
				if(CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW])
					CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Brak Interfacu ! Usunieto Button");
			}
		}
	}

	if(pOldButtonInterface || pSelectedMovedButton)
	{
		pOldButtonInterface = NULL;
		pSelectedMovedButton = NULL;

		if(CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW])
			CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Usunieto Uchwyt Do Interfacu i Buttona");
	}

    if(pSelectedButton != NULL)
    {
        if(pSelectedButton->IsButtonOnPos(x, y))
        {
            if(pSelectedButton->GetButtonState() == BUTTONSTATE_SELECTED)
            {
                pSelectedButton->Activate();
            }
            else
                if(pSelectedButton->GetButtonState() == BUTTONSTATE_MOVED)
                {
                    //pSelectedButton->OnDrop(x,y);
                }
        }

        pSelectedButton->SetButtonState(BUTTONSTATE_UNSELECTED);
        pSelectedButton->SetAnimationState(BUTTON_ANIME_NORMAL);
        pSelectedButton = NULL;
    }

    pSelectedInterface = NULL;
}

void CApp::OnExit() 
{
	Running = false;
}
