#include "CApp.h"

void CApp::OnLoop() 
{
    switch(eGameState)
    {
        case MAIN_MENU:
        {

            break;
        }

        case TEST:
        {
	        OnKeyState();												//Handle Key States -> camera movement

            // Entities
            for(int i = 0;i < CEntity::EntityList.size();i++) 
	        {
                if(!CEntity::EntityList[i]) continue;

                CEntity::EntityList[i]->OnLoop();
            }

	        CMovementGenerator::MoveGenerator.OnLoop();

            break;
        }

        default: break;
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