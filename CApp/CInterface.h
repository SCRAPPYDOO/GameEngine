#ifndef _CINTERFACE_H_
    #define _CINTERFACE_H_

#include <SDL.h>
#include <vector>

#include "Define.h"
#include "CSurface.h"
#include "CButton.h"

#define MAX_MENU_BUTTONS 2

class CInterface 
{
	public:
		GameState							eGameState;

        SDL_Surface*						Surf_BackGround;

        static CInterface					InterfaceControl;

	public:
        CInterface();
        virtual ~CInterface() {}

	public:
        virtual bool OnLoad(GameState eGameState);
			
        bool OnEvent(int x, int y);

        virtual void OnRender(SDL_Surface* Surf_Display);

        virtual void OnCleanup();

	public:
		bool LoadInterface(GameState eGameState);
		bool LoadSurface();
		bool LoadButtons();
};

#endif

