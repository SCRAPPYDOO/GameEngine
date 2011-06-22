#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h>

#include "Define.h"

#include "CArea.h"
#include "CCamera.h"
#include "CEvent.h"
#include "CEntity.h"
#include "CSurface.h"
#include "CMovementGenerator.h"
#include "CPlayer.h"
#include "CObject.h"
#include "CInterface.h"

class CEntity;

class CApp : public CEvent 
{
    private:
        bool            Running;

        SDL_Surface*    Surf_Display;

        CPlayer Player;
        CPlayer Player2;

        CEntity* pSelectedUnit;
    public:
        CApp();

        int OnExecute();

    public:
        bool OnInit();

        void OnEvent(SDL_Event* Event);

            void OnKeyState();

        	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
            void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

			void OnRButtonDown(int x,int y);
			void OnLButtonDown(int x,int y);

            void OnExit();

        void OnLoop();

        void OnRender();

        void OnCleanup();
};

#endif
