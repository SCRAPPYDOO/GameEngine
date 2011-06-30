#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h>
#include "math.h"

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
#include "CButton.h"

class CEntity;
class CInterface;
class CButton;

class CApp : public CEvent 
{
    public:
        static GameState eGameState;

        static CInterface* pSelectedInterface;
        static CButton* pSelectedButton;

        static CEntity* pSelectedUnit;
        CEntity* pSelectedTarget;

    private:
        bool            Running;

        SDL_Surface*    Surf_Display;
    public:
        CApp();

        int OnExecute();

    public:
        bool OnInit();

        void OnEvent(SDL_Event* Event);

            void OnKeyState();

        	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
            void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

            void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);

			void OnRButtonDown(int x,int y);
			void OnLButtonDown(int x,int y);
            void OnLButtonUp(int x,int y);

            void OnExit();

        void OnLoop();

        void OnRender();

        void OnCleanup();

        CEntity* CApp::GetEntity(int x, int y);

};

#endif
