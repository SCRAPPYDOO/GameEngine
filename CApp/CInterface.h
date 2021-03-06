#ifndef _CINTERFACE_H_
    #define _CINTERFACE_H_

#include "CButton.h"

#include "CPlayer.h"
#include <string>
#include <sstream>

#define MAX_MENU_BUTTONS 2
#define MAX_BUTTONPANEL_BUTTONS 10
#define MAX_CHARPANEL_BUTTONS 5
#define MAX_GAMEMENU_BUTTONS 2

#define INTERFACE_MAINMENU_W 1280
#define INTERFACE_MAINMENU_H 720
//Main Panel
#define INTERFACE_PLAYERINFO_W 786
#define INTERFACE_PLAYERINFO_H 107
#define INTERFACE_BUTTON_PANEL_W 1280
#define INTERFACE_BUTTON_PANEL_H 48
#define INTERFACE_GAMEMENU_W 414
#define INTERFACE_GAMEMENU_H 477
#define INTERFACE_CHARACTERPANEL_W 412
#define INTERFACE_CHARACTERPANEL_H 32

#define INTERFACE_EQUIPMENT_W 500
#define INTERFACE_EQUIPMENT_H 300
#define INTERFACE_EQUIPMENT_SLOT_H_W 59

#define INTERFACE_CHARACTERSHEET_W 702
#define INTERFACE_CHARACTERSHEET_H 521
#define INTERFACE_AREAMAP_W
#define INTERFACE_AREAMAP_H
#define INTERFACE_LOOT_W
#define INTERFACE_LOOT_H
#define INTERFACE_LOOT_W_H 200
#define INTERFACE_SPELLBOOK_W 300
#define INTERFACE_SPELLBOOK_H 500

#define INTERFACE_CHARACTERCREATOR_W 1280
#define INTERFACE_CHARACTERCREATOR_H 720

//Number of Slots for items spells buttons
#define INTERFACE_BUTTON_PANEL_MAXSLOTS 10
#define INTERFACE_BAG_MAXSLOT_X 8
#define INTERFACE_BAG_MAXSLOT_Y 8


enum InterfaceType
{
    INTERFACE_MAINMENU          = 0,
    INTERFACE_PLAYERINFO        = 1,
    INTERFACE_GAMEMENU          = 3,
    INTERFACE_CHARACTERPANEL    = 4,
    INTERFACE_EQUIP             = 6,
    INTERFACE_CHARACTERSHEET    = 7,
    INTERFACE_AREAMAP           = 8,
    INTERFACE_LOOT              = 9,
    INTERFACE_SPELLBOOK         = 10,
    INTERFACE_MASAGEWINDOW      = 11,
	INTERFACE_CHARACTERCREATOR  = 13,
	INTERFACE_INFOWINDOW,
	INTERFACE_SKILL,
    //If U ADD new Interface Update Value Below
};

#define MAX_INTERFACEOBJECTS 16

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
        CInterface();
        CInterface(InterfaceType eType);
        virtual ~CInterface() {}

    protected:
        std::vector<CButton*>     ButtonsList;
        SDL_Surface* Surf_Interface;
        InterfaceType eInterfaceType;

        int nInterfaceFlag;
        int nPosX, nPosY, nWidht, nHeight, nDistX, nDistY;
        int OldX, OldY;

    public:
        int GetPosX() const { return nPosX;}
        int GetPosY() const { return nPosY;}
        int GetWidht() const { return nWidht;}
        int GetHeight() const { return nHeight;}

        bool HasFlag(InterfaceFlag Flag) { if(nInterfaceFlag && Flag) return true; return false; }
        bool IsInterfaceOnPos(int nX, int nY);

        virtual CButton* GetButton(int nPosX, int nPosY) const;
		virtual CItem* GetItem(int nPosX, int nPosY) const { return NULL; }
        virtual void AddButtonToSlot(CButton* pButton) { }
		virtual bool AddButtonToSlot(CButton* pButton, int mX, int mY) { return false; }
		virtual void DeleteButtonFromSlot(CButton* pButton) { }

        virtual void AddMsg(char* msg) {}
		virtual void AddUnitPointer(CUnit* Unit = NULL, CButton* Button = NULL) {}

	public:
        virtual bool OnLoad();	
            virtual void LoadButtons();

      //virtual void OnEvent();
            virtual void OnMove(int nNextX, int nNextY); //when we  move interface object
            virtual void SetDistance(int nX, int nY) { nDistX = nX - nPosX; nDistY = nY - nPosY; }              //Used for proper update movement
            virtual void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);

        virtual void OnLoop();
            virtual void UpdateButtonsPosition();                                                             //When we move we update our buttons positions as well                                                               //If we move  our button we need delete his old position

        virtual void OnRender(SDL_Surface* Surf_Display);
        virtual void OnCleanup();

        virtual void OnButtonActivate(ButtonType Type) {} // called when button activate
		virtual void OnButtonActivate(int Type) {}

		virtual void LoadLoot(int ID) {}
};

#endif

