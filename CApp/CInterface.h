#ifndef _CINTERFACE_H_
    #define _CINTERFACE_H_

#include <SDL.h>
#include <vector>

#include "Define.h"
#include "CSurface.h"
#include "CButton.h"
#include "CApp.h"

#define MAX_MENU_BUTTONS 2

class CInterface 
{
	public:
        SDL_Surface*						Surf_BackGround;

        static SDL_Surface*                 Surf_MenuButton;
        static SDL_Surface*                 Surf_GameMenuButton;
        SDL_Surface*                        Surf_GameMenuBackGround;

        static CInterface					InterfaceControl;

        bool ShowGameMenu;

	public:
        CInterface();
        virtual ~CInterface() {}

	public:
        virtual bool OnLoad();
			
        bool OnEvent(int x, int y);

        virtual void OnRender(SDL_Surface* Surf_Display);

        virtual void OnCleanup();

	public:
		bool LoadInterface();
		bool LoadSurface();
		bool LoadButtons();
};

#endif

