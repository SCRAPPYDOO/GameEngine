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

#define MAX_INTERFACEOBJECTS 10

#define INTERFACE_MAINMENU_W 1280
#define INTERFACE_MAINMENU_H 720
#define    INTERFACE_PLAYERINFO_W
#define    INTERFACE_PLAYERINFO_H
#define    INTERFACE_BUTTON_PANEL_W
#define    INTERFACE_BUTTON_PANEL_H
#define    INTERFACE_GAMEMENU_W 414
#define    INTERFACE_GAMEMENU_H 477
#define    INTERFACE_CHARACTERPANEL_W 224
#define    INTERFACE_CHARACTERPANEL_H 52
#define INTERFACE_BAG_W 577
#define INTERFACE_BAG_H 598
#define    INTERFACE_EQUIP_W
#define    INTERFACE_EQUIP_H
#define    INTERFACE_CHARACTERSHEET_W
#define    INTERFACE_CHARACTERSHEET_H
#define    INTERFACE_AREAMAP_W
#define    INTERFACE_AREAMAP_H
#define    INTERFACE_LOOT_W
#define    INTERFACE_LOOT_H

enum InterfaceType
{
    INTERFACE_MAINMENU          = 0,
    INTERFACE_PLAYERINFO        = 1,
    INTERFACE_BUTTON_PANEL      = 2,
    INTERFACE_GAMEMENU          = 3,
    INTERFACE_CHARACTERPANEL    = 4,
    INTERFACE_BAG               = 5,
    INTERFACE_EQUIP             = 6,
    INTERFACE_CHARACTERSHEET    = 7,
    INTERFACE_AREAMAP           = 8,
    INTERFACE_LOOT              = 9,

};

enum InterfaceFlag
{
    INTERFACE_FLAG_NOTMOVEABLE              = 0x01,
    INTERFACE_FLAG_ITEMSLOTS                = 0x02,
    INTERFACE_FLAG_BUTTONSLOTS              = 0x04,
    INTERFACE_FLAG_SPELLSLOTS               = 0x08,
};

class CInterface 
{
	public:
        static CInterface					InterfaceControl;
        CInterface*                         Interface[MAX_INTERFACEOBJECTS];

    public:
		bool LoadInterface();
        bool LoadInterface(InterfaceType eType);
        void CleanUpInterface();
        void CleanUpInterface(InterfaceType eType);

        bool IsInterfaceOnPos(int nX, int nY);

	public:
        virtual bool OnLoad();	
            virtual void LoadButtons() {}

      //virtual void OnEvent();
            virtual void OnMove(int nNextX, int nNextY); //when we  move interface object
            virtual void SetDistance(int nX, int nY) { nDistX = nX - nPosX; nDistY = nY - nPosY; }              //Used for proper update movement
            virtual bool AddButtonToInterface(CButton* pButton, int mX, int mY) { return false; }               //Used when we add button to interface

            virtual void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) {}

        virtual void OnLoop();
            virtual void UpdateButtonsPosition() {}                                                             //When we move we update our buttons positions as well
            virtual void DeleteMovedButtons() {}                                                                //If we move  our button we need delete his old position

        virtual void OnRender(SDL_Surface* Surf_Display);
        virtual void OnCleanup();

	public:
        CInterface();
        virtual ~CInterface() {}

    protected:
        SDL_Surface* Surf_Interface;
        
        InterfaceType eInterfaceType;

        int nInterfaceFlag;

        int nPosX, nPosY, nWidht, nHeight, nDistX, nDistY;

        int OldX, OldY;

	public:
        CInterface* GetInterface(int nPosX, int nPosY);
        InterfaceType GetInterfaceType() const { return eInterfaceType; }

        int GetPosX() const { return nPosX;}
        int GetPosY() const { return nPosY;}
        int GetWidht() const { return nWidht;}
        int GetHeight() const { return nHeight;}

        bool HasFlag(InterfaceFlag Flag) { if(nInterfaceFlag && Flag) return true; return false; }

        virtual CButton* GetButton(int nPosX, int nPosY) const { return NULL; }
};

#endif

