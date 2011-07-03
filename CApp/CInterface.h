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
#define MAX_INTERFACEOBJECTS 20

enum SurfaceType
{
    Surf_MenuBackGround = 0,
    Surf_MenuButton     = 1,
    Surf_GameMenu       = 2,
    Surf_GameMenuButton = 3,
};

enum InterfaceType
{
    INTERFACE_PLAYERINFO        = 1,
    INTERFACE_BUTTON_PANEL      = 2,
    INTERFACE_GAMEMENU          = 3,
};

class CInterface 
{
	public:
        static CInterface					InterfaceControl;
        static std::vector<CInterface*>     InterfaceObjectList;

        SDL_Surface*						Surf_BackGround;

        SDL_Surface*                        Surf_MenuButton;
        static SDL_Surface*                 Surf_GameMenuButton;

        static bool IsGameMenu;

    protected:
        int nPosX, nPosY, nWidht, nHeight, nDistX, nDistY;

        InterfaceType eInterfaceType;

	public:
        CInterface();
        virtual ~CInterface() {}

	public:
        virtual bool OnLoad();	
        virtual void OnLoop();
        virtual void OnRender(SDL_Surface* Surf_Display);
        virtual void OnCleanup();

	public:
        CInterface* GetInterface(int nPosX, int nPosY);
        InterfaceType GetInterfaceType() const { return eInterfaceType; }

        virtual int GetPosX() const { return nPosX;}
        virtual int GetPosY() const { return nPosY;}
        virtual int GetWidht() const { return nWidht;}
        virtual int GetHeight() const { return nHeight;}

        virtual void OnMove(int nNextX, int nNextY) { nPosX = nNextX - nDistX; nPosY = nNextY - nDistY; }
        virtual void SetDistance(int nX, int nY) { nDistX = nX - nPosX; nDistY = nY - nPosY; } //Used for proper update movement for interface panels

        virtual bool AddButtonToInterface(CButton* pButton, int mX, int mY) { return false; }

    public:
        bool OnLButtonUp(int x, int y);

		bool LoadInterface();
        void LoadInterface(InterfaceType eType);
        void UnloadInterface(InterfaceType eType);

		bool LoadSurface();
		bool LoadButtons();
        void CleanUpInterface();

        bool IfInterfaceOnPos(int nX, int nY);
};

#endif

