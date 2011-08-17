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
                    CPlayer::Player.pPlayerCharacter->SetHealth(5);
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
            if(pUnit && pUnit->HasFlag(UNIT_FLAG_GOSSIP))
                CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Mam Flage");

            if(pUnit && pUnit->HasFlag(UNIT_FLAG_VENDOR))
                CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Mam Flage");
        }
    }
    else
    {
        if(pSelectedButton != NULL && (pSelectedButton->GetButtonState() == BUTTONSTATE_SELECTED || pSelectedButton->GetButtonState() == BUTTONSTATE_MOVED) && !pSelectedButton->HasFlag(BUTTONFLAG_NOTMOVED) )
        {
            if(pSelectedButton->GetButtonState() != BUTTONSTATE_MOVED)
            {
                //Save our current positions -> used in Button->OnDrop()
                pSelectedButton->SaveCurrentPosition();

                if(CInterface* pInterface = CInterfaceMenager::InterfaceMenager.GetInterface(mX, mY))
                {
                    pInterface->DeleteButtonFromSlot(pSelectedButton);
                }
            }

            pSelectedButton->OnMove(mX, mY);

            return;                
        }

        if(pSelectedInterface != NULL)
        {
            pSelectedInterface->OnMove(mX, mY);
            return;
        }
    }
}

void CApp::OnRButtonDown(int x,int y)
{
    if(CApp::eGameState == MAIN_MENU) //We Dont Use RButton In Menu                                       
        return;

    CPlayer::Player.pPlayerCharacter->SetHealth(55);
}

void CApp::OnRButtonUp(int mX, int mY)
{
    if(CUnit* pUnit = CUnitMenager::GetUnit(mX, mY))
    {
        if(pUnit)
        {
            //if(pUnit->IsEnemy())
            //{
                 /* CanAttack();*/  
            //    return;
            //}

            if(!pUnit->IsAlive() && pUnit->HasFlag(UNIT_FLAG_LOOTABLE))
            {
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
            if(pSelectedButton = pInterface->GetButton(x, y))
            {
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

    //if(CUnit* pUnit = CUnitMenager::GetUnit(x, y))
    //    if(pUnit)
    //        if(pUnit == CPlayer::Player.pSelectedUnit)
    //        {
    //            return;
    //        }
    //        else
    //        {
    //            CPlayer::Player.pTargetedUnit = pUnit;
    //        }
}

void CApp::OnLButtonUp(int x,int y)
{
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
                    pSelectedButton->OnDrop(x,y);
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
