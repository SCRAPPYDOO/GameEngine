#ifndef _CINTERFACE_H_
    #define _CINTERFACE_H_

#include "CButton.h"
#include "CPlayer.h"

#define MAX_MENU_BUTTONS 2
#define MAX_BUTTONPANEL_BUTTONS 10
#define MAX_CHARPANEL_BUTTONS 5
#define MAX_GAMEMENU_BUTTONS 2

#define INTERFACE_MAINMENU_W 1280
#define INTERFACE_MAINMENU_H 720
#define INTERFACE_PLAYERINFO_W 89
#define INTERFACE_PLAYERINFO_H 89
#define INTERFACE_BUTTON_PANEL_W 1280
#define INTERFACE_BUTTON_PANEL_H 48
#define INTERFACE_GAMEMENU_W 414
#define INTERFACE_GAMEMENU_H 477
#define INTERFACE_CHARACTERPANEL_W 412
#define INTERFACE_CHARACTERPANEL_H 32

#define INTERFACE_EQUIPMENT_W 577
#define INTERFACE_EQUIPMENT_H 598
#define INTERFACE_EQUIPMENT_SLOT_H_W 59

#define INTERFACE_CHARACTERSHEET_W 639
#define INTERFACE_CHARACTERSHEET_H 319
#define INTERFACE_AREAMAP_W
#define INTERFACE_AREAMAP_H
#define INTERFACE_LOOT_W
#define INTERFACE_LOOT_H
#define INTERFACE_LOOT_W_H 200
#define INTERFACE_SPELLBOOK_W 300
#define INTERFACE_SPELLBOOK_H 500

//Number of Slots for items spells buttons
#define INTERFACE_BUTTON_PANEL_MAXSLOTS 10
#define INTERFACE_BAG_MAXSLOT_X 8
#define INTERFACE_BAG_MAXSLOT_Y 8



enum InterfaceType
{
    INTERFACE_MAINMENU          = 0,
    INTERFACE_PLAYERINFO        = 1,
    INTERFACE_BUTTON_PANEL      = 2,
    INTERFACE_GAMEMENU          = 3,
    INTERFACE_CHARACTERPANEL    = 4,
    INTERFACE_EQUIP             = 6,
    INTERFACE_CHARACTERSHEET    = 7,
    INTERFACE_AREAMAP           = 8,
    INTERFACE_LOOT              = 9,
    INTERFACE_SPELLBOOK         = 10,
    INTERFACE_MASAGEWINDOW      = 11,
    INTERFACE_TARGET            = 12,
    //If U ADD new Interface Update Value Below
};

#define MAX_INTERFACEOBJECTS 13

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

    public:
        
        InterfaceType GetInterfaceType() { return eInterfaceType; }

        int GetPosX() const { return nPosX;}
        int GetPosY() const { return nPosY;}
        int GetWidht() const { return nWidht;}
        int GetHeight() const { return nHeight;}

        bool HasFlag(InterfaceFlag Flag) { if(nInterfaceFlag && Flag) return true; return false; }

        bool IsInterfaceOnPos(int nX, int nY);

        virtual CButton* GetButton(int nPosX, int nPosY) const;
        virtual void AddButtonToSlot(CButton* pButton) { ButtonsList.push_back(pButton); }
        virtual bool AddButtonToSlot(CButton* pButton, int mX, int mY);
        virtual void DeleteButtonFromSlot(CButton* pButton);

        virtual void AddMsg(char* msg) {}

        SDL_Surface* RenderText(char* txt);
};

#endif

