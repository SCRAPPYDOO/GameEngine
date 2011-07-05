#ifndef _CINTERFACE_H_
    #define _CINTERFACE_H_

#include <SDL.h>
#include <vector>

#include "Define.h"
#include "CSurface.h"
#include "CButton.h"
#include "CApp.h"

#define MAX_MENU_BUTTONS 2
#define MAX_BUTTONPANEL_BUTTONS 10
#define MAX_CHARPANEL_BUTTONS 5
#define MAX_GAMEMENU_BUTTONS 2
#define MAX_INTERFACEOBJECTS 3

enum InterfaceType
{
    INTERFACE_MAINMENU          = 0,
    INTERFACE_PLAYERINFO        = 1,
    INTERFACE_BUTTON_PANEL      = 2,
    INTERFACE_GAMEMENU          = 3,
    INTERFACE_CHARACTERPANEL    = 4,
};

enum InterfaceFlag
{
    FLAG_NOTMOVED               = 0x01,
};

class CInterface 
{
	public:
        static CInterface					InterfaceControl;
        static std::vector<CInterface*>     InterfaceObjectList;
        static bool IsGameMenu;

    public:
		bool LoadInterface();
        bool LoadInterface(InterfaceType eType);
        void CleanUpInterface();
        void CleanUpInterface(InterfaceType eType);

        bool IsInterfaceOnPos(int nX, int nY);

	public:
        virtual bool OnLoad();	
            virtual bool LoadButtons();

      //virtual void OnEvent();
            virtual void OnMove(int nNextX, int nNextY); //when we  move interface object
            virtual void SetDistance(int nX, int nY) { nDistX = nX - nPosX; nDistY = nY - nPosY; }              //Used for proper update movement
            virtual bool AddButtonToInterface(CButton* pButton, int mX, int mY) { return false; }               //Used when we add button to interface

        virtual void OnLoop();
            virtual void UpdateButtonsPosition() {}                                                             //When we move we update our buttons positions as well
            virtual void DeleteMovedButtons() {}                                                                //If we move  our button we need delete his old position

        virtual void OnRender(SDL_Surface* Surf_Display);
        virtual void OnCleanup();

	public:
        CInterface();
        CInterface(InterfaceType eType);
        virtual ~CInterface() {}

    protected:
        SDL_Surface* Surf_Interface;
        
        InterfaceType eInterfaceType;

        int nInterfaceflag;

        int nPosX, nPosY, nWidht, nHeight, nDistX, nDistY;

        int OldX, OldY;

	public:
        CInterface* GetInterface(int nPosX, int nPosY);
        InterfaceType GetInterfaceType() const { return eInterfaceType; }

        int GetPosX() const { return nPosX;}
        int GetPosY() const { return nPosY;}
        int GetWidht() const { return nWidht;}
        int GetHeight() const { return nHeight;}
};

#endif

