#include "CApp.h"

void CApp::OnLoop() 
{
	OnKeyState();												//Handle Key States -> camera movement

	CMovementGenerator::MoveGenerator.OnLoop();

    for(int i = 0;i < MAX_INTERFACEOBJECTS ;i++) //Update Interface Variables
	{
        if(!CInterface::InterfaceControl.Interface[i]) continue;

        CInterface::InterfaceControl.Interface[i]->OnLoop();
    }

    // Entities
    for(int i = 0;i < CEntity::EntityList.size();i++) 
	{
        if(!CEntity::EntityList[i]) continue;

        CEntity::EntityList[i]->OnLoop();
    }
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