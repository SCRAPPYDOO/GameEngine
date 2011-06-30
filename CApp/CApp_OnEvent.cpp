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
            if(!CInterface::InterfaceControl.ShowGameMenu)
                CInterface::InterfaceControl.ShowGameMenu = true;
            else
                CInterface::InterfaceControl.ShowGameMenu = false;

            break;
        }
    }
}

void CApp::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) 
{
}

void CApp::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{ 
    if(Left && pSelectedInterface != NULL)
    {
        pSelectedInterface->OnMove(mX + CCamera::CameraControl.GetX(), mY + CCamera::CameraControl.GetY());
    }
}

void CApp::OnRButtonDown(int x,int y)
{
    if(CApp::eGameState == MAIN_MENU) //We Dont Use RButton In Menu                                       
        return;

    if(pSelectedUnit != NULL) 
    {
        CEntity* pEntity = GetEntity(x,y);

        if(pEntity == NULL)                                                    //we check what we can do due to targetet entity
        { 
            x += CCamera::CameraControl.GetX();
            y += CCamera::CameraControl.GetY();

            //if we have a clear point we go there
            pSelectedUnit->OnMoveToPoint(x, y);
            return;
        }

        if(pEntity->Type == ENTITY_TYPE_PLAYER)                            //if its our unit do nothing
            return;

        if(pSelectedUnit == pEntity)                                       // if its selected unit do nothing
            return;

            /*if(temp->FactionType != pSelectedUnit->FactionType)           // If Its Enemy We Start Basic Attack
            {
                pSelectedUnit->StartAttack(temp);
                return;
            } */
        

        //Interact with doors

        //Interact with portals

        //Interact with Objects

        //Interact with massage box
    }
}

void CApp::OnLButtonDown(int x,int y)
{
    switch(CApp::eGameState)
    {
        case MAIN_MENU:
        {
            break;
        }

        case TEST:
        {
            /*
            if(pSelectedButton = CInterface::InterfaceControl.GetInterface(x,y));
                break;
                */

            if(pSelectedInterface = CInterface::InterfaceControl.GetInterface(x,y));
                if(pSelectedInterface != NULL)
                {
                    pSelectedInterface->SetDistance(x,y);
                    break;
                }

            CEntity* pEntity = GetEntity(x,y);

            if(pEntity && pEntity->Type == ENTITY_TYPE_PLAYER)
            {
                if(pSelectedUnit == pEntity)
                    return;
                
                pSelectedUnit = pEntity;
                    return;
            }
            else
            {
                if(pSelectedTarget == pEntity)
                    return;

                pSelectedTarget = pEntity;
            }

            break;
        }

        default: break;
    }
    return;
}

void CApp::OnLButtonUp(int x,int y)
{
    pSelectedInterface = NULL;

    if(CInterface::InterfaceControl.OnLButtonUp(x,y))
        return;
}

void CApp::OnExit() 
{
	Running = false;
}

CEntity* CApp::GetEntity(int x, int y)
{
    CEntity* temp = NULL;

    for(int i = 0;i < CEntity::EntityList.size();i++) 
    {   
        if(!CEntity::EntityList[i]) continue;

        //If the mouse is over the Entity
        if( ( x > CEntity::EntityList[i]->GetAnimPosX() ) && ( x < CEntity::EntityList[i]->GetAnimPosX() + CEntity::EntityList[i]->Width) && ( y > CEntity::EntityList[i]->GetAnimPosY() ) && ( y < CEntity::EntityList[i]->GetAnimPosY() + CEntity::EntityList[i]->Height ) )
        {  
            temp = CEntity::EntityList[i];
            return temp;
        }
    }

    return temp;
}
