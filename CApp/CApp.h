#ifndef _CAPP_H_
    #define _CAPP_H_

#include "CMySQL.h"

#include <SDL.h>
#include "math.h"
#include <vector>

//#include <stdlib.h>
//#include <iostream>
//#include <sstream>
//#include <stdexcept>

#include "Define.h"

#include "CArea.h"
#include "CCamera.h"
#include "CEvent.h"
#include "CSurface.h"
#include "CMovementGenerator.h"


#include "CInterfaceMenager.h"
//#include "CButton.h"
#include "CItem.h"
#include "CObjectMenager.h"
#include "CUnitMenager.h"

#include "CPlayer.h"
#include "CMouse.h"

class CInterface;
class CButton;
class CUnit;

class CApp : public CEvent 
{
    public:
        static CApp GameControl;

        static GameState eGameState;

        static CInterface* pSelectedInterface;
        static CButton* pSelectedButton;

		static CInterface* pOldButtonInterface;
		static CButton* pSelectedMovedButton;

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

			void OnRButtonDown(int mX,int mY);
            void OnRButtonUp(int mX, int mY);
			void OnLButtonDown(int x,int y);
            void OnLButtonUp(int x,int y);

            void OnExit();

        void OnLoop();

        void OnRender();

        void OnCleanup();

};

#endif
