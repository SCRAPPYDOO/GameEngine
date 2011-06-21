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
    if(pSelectedUnit == NULL)
        return;

    pSelectedUnit->goX = x + CCamera::CameraControl.GetX();
    pSelectedUnit->goY = y + CCamera::CameraControl.GetY();

}

void CApp::OnLButtonDown(int x,int y)
{
    for(int i = 0;i < CEntity::EntityList.size();i++) 
	{   
        if(!CEntity::EntityList[i]) continue;

        //If the mouse is over the Entity
        if( ( x > CEntity::EntityList[i]->X ) && ( x < CEntity::EntityList[i]->X + CEntity::EntityList[i]->Width) && ( y > CEntity::EntityList[i]->Y ) && ( y < CEntity::EntityList[i]->Y + CEntity::EntityList[i]->Height ) )
        {
            pSelectedUnit = CEntity::EntityList[i];
        }
    }
}

void CApp::OnExit() 
{
	Running = false;
}

