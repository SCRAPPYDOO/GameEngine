#ifndef _CINTERFACE_H_
    #define _CINTERFACE_H_

#include <SDL.h>
#include <vector>

#include "Define.h"
#include "CSurface.h"
#include "CButton.h"
#include "CApp.h"

#define MAX_MENU_BUTTONS 2
#define MAX_PANEL_BUTTONS 10

enum SurfaceType
{
    Surf_MenuBackGround = 0,
    Surf_MenuButton     = 1,
    Surf_GameMenu       = 2,
    Surf_GameMenuButton = 3,
};

enum InterfaceType
{
    InterfaceType_PlayerIcon  = 10,
    InterfaceType_ButtonPanel = 11,
};

class CInterface 
{
	public:
        static CInterface					InterfaceControl;
        static std::vector<CInterface*>     InterfaceObjectList;

        SDL_Surface*						Surf_BackGround;

        SDL_Surface*                        Surf_MenuButton;
        static SDL_Surface*                 Surf_GameMenuButton;

        bool ShowGameMenu;

    protected:
        int nPosX, nPosY, nWidht, nHeight, nDistX, nDistY;

	public:
        CInterface();
        virtual ~CInterface() {}

	public:
        virtual bool OnLoad();
			
        virtual void OnRender(SDL_Surface* Surf_Display);

        virtual void OnCleanup();

    public:
        bool OnLButtonUp(int x, int y);

	public:
        CInterface* GetInterface(int nPosX, int nPosY);

        virtual int GetPosX() { return nPosX;}
        virtual int GetPosY() { return nPosY;}
        virtual int GetWidht() { return nWidht;}
        virtual int GetHeight() { return nHeight;}

        virtual void OnMove(int nNextX, int nNextY) 
        { 
            nPosX = nNextX - nDistX;
            nPosY = nNextY - nDistY;
        }

        virtual void SetDistance(int nX, int nY) //Used for proper update movement for interface panels
        {
            nDistX = nX - nPosX; 
            nDistY = nY - nPosY;
        }

		bool LoadInterface();
		bool LoadSurface();
		bool LoadButtons();
        void CleanUpInterface();
};

#endif

