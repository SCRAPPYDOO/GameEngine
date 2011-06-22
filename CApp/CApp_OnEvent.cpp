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
        for(int i = 0;i < CEntity::EntityList.size();i++) 
	    {   
            if(!CEntity::EntityList[i]) continue;

            //If the mouse is over the Entity
            if( ( x > CEntity::EntityList[i]->X ) && ( x < CEntity::EntityList[i]->X + CEntity::EntityList[i]->Width) && ( y > CEntity::EntityList[i]->Y ) && ( y < CEntity::EntityList[i]->Y + CEntity::EntityList[i]->Height ) )
            {
                if(CEntity::EntityList[i]->Type == ENTITY_TYPE_PLAYER)
                    return;
            }
        }


        x += CCamera::CameraControl.GetX();
        y += CCamera::CameraControl.GetY();

        //if we have a clear point we go there
        pSelectedUnit->OnMoveToPoint(x, y);
    }

}

void CApp::OnLButtonDown(int x,int y)
{
    if(CInterface::InterfaceControl.OnEvent(x,y))
        return;

    for(int i = 0;i < CEntity::EntityList.size();i++) 
	{   
        if(!CEntity::EntityList[i]) continue;

        //If the mouse is over the Entity
        if( ( x > CEntity::EntityList[i]->X ) && ( x < CEntity::EntityList[i]->X + CEntity::EntityList[i]->Width) && ( y > CEntity::EntityList[i]->Y ) && ( y < CEntity::EntityList[i]->Y + CEntity::EntityList[i]->Height ) )
        {
            //If its a player unit
            if(CEntity::EntityList[i]->Type == ENTITY_TYPE_PLAYER)
                pSelectedUnit = CEntity::EntityList[i];
        }
    }
}

void CApp::OnExit() 
{
	Running = false;
}

