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
        static CInterface					InterfaceControl;
        static std::vector<CInterface*>     InterfaceObjectList;

        SDL_Surface*						Surf_BackGround;

        SDL_Surface*                        Surf_MenuButton;
        static SDL_Surface*                 Surf_GameMenuButton;
        SDL_Surface*                        Surf_GameMenuBackGround;

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

class CButtonPanel : public CInterface
{
    public:
        CButtonPanel()
        {
            nPosX = 100;
            nPoxY = 100;
            nWeight = 600;
            nHight = 30;

            Surf_ButtonPanel = NULL;
        }

        ~CButtonPanel() {}

        SDL_Surface* Surf_ButtonPanel;

    public:
        int nPosX;
        int nPoxY;
        int nWeight;
        int nHight;

    public:
        bool OnLoad()
        {


        }
};

#endif

