#include "CApp.h"
//

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
			if(!CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_GAMEMENU])
			{
				CInterfaceMenager::InterfaceMenager.LoadInterface(INTERFACE_GAMEMENU);
			}
			else
				CInterfaceMenager::InterfaceMenager.CleanUpInterface(INTERFACE_GAMEMENU);

            break;
        }
    }
}

void CApp::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) 
{
}

void CApp::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{ 
    if(CInterface* pInterface = CInterfaceMenager::InterfaceMenager.GetInterface(mX, mY))
         if(pInterface)
             pInterface->OnMouseMove(mX, mY, relX, relY, Left, Right, Middle);

    //Interface
    //Entitys
    //StaticObjects
    if(CUnit* pUnit = CUnitMenager::GetUnit(mX, mY))
        if(pUnit && !pUnit->HasFlag(UNIT_FLAG_GOSSIP))
            CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Mam Flage");
       


    if(Left)
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
