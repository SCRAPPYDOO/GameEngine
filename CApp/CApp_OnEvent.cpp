#include "CApp.h"

void CApp::OnEvent(SDL_Event* Event) 
{
    CEvent::OnEvent(Event);
}

void CApp::OnKeyState()
{
    //Get the keystates
    Uint8 *keystates = SDL_GetKeyState( NULL );

    if( keystates[ SDLK_UP ] )
    {
        CCamera::CameraControl.OnMove( 0,  -5);
    }

    if( keystates[ SDLK_DOWN ] )
    {
        CCamera::CameraControl.OnMove( 0, 5);
    }

    if( keystates[ SDLK_LEFT ] )
    {
        CCamera::CameraControl.OnMove( -5,  0);
    }

    if( keystates[ SDLK_RIGHT ] )
    {
        CCamera::CameraControl.OnMove(5,  0);
    }
}

void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) 
{
}

void CApp::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) 
{
}

void CApp::OnRButtonDown(int x,int y)
{
    if(pSelectedUnit != NULL) 
    {
        CEntity *temp = NULL;
        temp = CEntityContainer::GetEntity(x, y);

        if(temp == NULL)                                                    //we check what we can do due to targetet entity
        {
            x += CCamera::CameraControl.GetX();
            y += CCamera::CameraControl.GetY();

            //if we have a clear point we go there
            pSelectedUnit->OnMoveToPoint(x, y);
            return;
        }

        if(temp->Type == ENTITY_TYPE_PLAYER)                            //if its our unit do nothing
            return;

        if(pSelectedUnit == temp)                                       // if its selected unit do nothing
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
    if(CInterface::InterfaceControl.OnEvent(x,y))
        return;

    CEntity *temp = NULL;
    temp = CEntityContainer::GetEntity(x, y);

            //If its a player unit
    if(temp->Type == ENTITY_TYPE_PLAYER)
    {
        if(pSelectedUnit == temp)
            return;

        pSelectedUnit = temp;
    }
}

void CApp::OnExit() 
{
	Running = false;
}

