#ifndef _CBUTTON_H_
    #define _CBUTTON_H_

#include <vector>
#include "CSurface.h"

#define GAME_BUTTON_SIZE_W 30
#define GAME_BUTTON_SIZE_H 30

#define GAME_OPTION_BUTTON_SIEZ_W 140
#define GAME_OPTION_BUTTON_SIZE_H 30

enum ButtonClass 
{
    BUTTONCLASS_BUTTON,
    BUTTONCLASS_ITEM,
    BUTTONCLASS_SPELL,
    BUTTONCLASS_SHORTCURT,
};

enum ButtonType
{
	BUTTON_PLAY		= 0,   //enter to world
	BUTTON_QUIT		= 1,   //quit from game

	BUTTON_MENU_CREATECHARACTER		= 3,
	BUTTON_MENU_DELETE_CHARACTER	= 4,
	BUTTON_MENU_ENTERTOWORLD		= 5,

	BUTTON_MENU_SLOT_ONE,
	BUTTON_MENU_SLOT_TWO,
	BUTTON_MENU_SLOT_THREE,
	BUTTON_MENU_SLOT_FOUR,
	BUTTON_MENU_SLOT_FIVE = 10004,
	BUTTON_MENU_SLOT_SIX = 10005,

    //Game Menu Button
    BUTTON_GAMEMENU_QUIT = 10,
    BUTTON_GAMEMENU_RETURN = 11,

    BUTTON_CHARPANEL_CHARSHEET = 20,
    BUTTON_CHARPANEL_EQUIPMENT = 21,
    BUTTON_CHARPANEL_SPELLBOOK = 22,
    BUTTON_CHARPANEL_QUESTDIARY = 23,
    BUTTON_CHARPANEL_GAMEMENU   = 24,

    BUTTON_EQUIPMENT_QUIT         = 51,

    BUTTON_LOOT_QUIT        = 56,
    BUTTON_LOOT_LOOTALL     = 57,

    BUTTON_SPELLBOOK_QUIT   = 40,

    BUTTON_PANEL_LOCK       = 60,

   //Create Character Buttons
    BUTTON_CREATECHAR_NEXT  = 130,
    BUTTON_CREATECHAR_BACK = 131,
    BUTTON_CREATECHAR_END = 132,

	BUTTON_CREATECHAR_DRAGONBORN = 133,
	BUTTON_CREATECHAR_DWARF,
	BUTTON_CREATECHAR_ELADRIN,
	BUTTON_CREATECHAR_ELF,
	BUTTON_CREATECHAR_HALFELF,
	BUTTON_CREATECHAR_HALFLING,
	BUTTON_CREATECHAR_HUMAN,
	BUTTON_CREATECHAR_TIEFLING,

	BUTTON_CREATECHAR_CLERIC,
	BUTTON_CREATECHAR_FIGHTER,
	BUTTON_CREATECHAR_PALADIN,
	BUTTON_CREATECHAR_RANGER,
	BUTTON_CREATECHAR_ROGUE,
	BUTTON_CREATECHAR_WARLOCK,
	BUTTON_CREATECHAR_WARLORD,
	BUTTON_CREATECHAR_WIZARD,

	BUTTON_CREATECHAR_STR,
	BUTTON_CREATECHAR_CON,
	BUTTON_CREATECHAR_DEX,
	BUTTON_CREATECHAR_INT,
	BUTTON_CREATECHAR_WIS,
	BUTTON_CREATECHAR_CHA,
	BUTTON_CREATECHAR_INCREASE,
	BUTTON_CREATECHAR_DECREASE,

	BUTTON_CREATECHAR_SKILL_ACROBATICS = 100,
	BUTTON_CREATECHAR_SKILL_ARCANA, 
	BUTTON_CREATECHAR_SKILL_ATHLETICS, 
	BUTTON_CREATECHAR_SKILL_BLUFF, 
	BUTTON_CREATECHAR_SKILL_DIPLOMACY, 
	BUTTON_CREATECHAR_SKILL_DUNGEONEERING, 
	BUTTON_CREATECHAR_SKILL_ENDURANCE, 
	BUTTON_CREATECHAR_SKILL_HEAL,
	BUTTON_CREATECHAR_SKILL_HISTORY,
	BUTTON_CREATECHAR_SKILL_INSIGHT,
	BUTTON_CREATECHAR_SKILL_INTIMIDATE, 
	BUTTON_CREATECHAR_SKILL_NATURE, 
	BUTTON_CREATECHAR_SKILL_PERCEPTION, 
	BUTTON_CREATECHAR_SKILL_RELIGION, 
	BUTTON_CREATECHAR_SKILL_STEALTH, 
	BUTTON_CREATECHAR_SKILL_STREETWISE,

    BUTTON_SWORD            = 10001,

    BUTTON_DEFAULT	                = 100000,
};

enum ItemType
{
    ItemType_Weapon,
    ItemType_Shield,
};

enum ButtonState
{
    BUTTONSTATE_UNSELECTED = 0,
    BUTTONSTATE_SELECTED   = 1,
    BUTTONSTATE_MOVED      = 2, 
};

enum ButtonAnimeState
{
    BUTTON_ANIME_NORMAL     = 0,
    BUTTON_ANIME_ONMOTION   = 1,
    BUTTON_ANIME_ONCLICK    = 2,
};

enum ButtonFlag
{
	BUTTONFLAG_NOTMOVED		= 0x02,
    BUTTONFLAG_LOOT         = 0x04,
};

class CInterface;

class CButton
{
	public:
        CButton() {}
        CButton(int nPosX, int nPosY, ButtonType Type);
        CButton(int nPosX, int nPosY, int Type);
		~CButton() {}

    protected:
        SDL_Surface*     pButtonSurface;

        ButtonClass      eButtonClass;
		ButtonType       eButtonType;
        ButtonState      eButtonState;
        ButtonAnimeState eAnimationState;

		int ButtonIndex;

		int				 nButtonFlag;
		int x, y, w, h;
        int nDistX, nDistY;
        int nPreviousX, nPreviousY;

    public:
        virtual bool OnLoad();
		virtual bool OnLoad(ButtonType eType);
		virtual void OnRender(SDL_Surface* Surf_Display);
        virtual void OnCleanup();

    public: //Methods for variables
        ButtonType GetButtonType() const { return eButtonType; }
        ButtonState GetButtonState() const { return eButtonState; }

        void SetButtonClass(ButtonClass eClass) { eButtonClass = eClass; }
        ButtonClass GetButtonClass() const { return eButtonClass; }

        int GetPosX() const { return x; }
        int GetPosY() const { return y; }
        int GetWidht() const { return w; }
        int GetHeight() const { return h; }
        int GetPreviousX() const { return nPreviousX; }
        int GetPreviousY() const { return nPreviousY; }

        void SetPositionX(int nValue) { x = nValue;}
        void SetPositionY(int nValue) { y = nValue;}
        void SetPreviousX(int nValue) { nPreviousX = nValue;}
        void SetPreviousY(int nValue) { nPreviousY = nValue;}
        void SetButtonState(ButtonState eState) { eButtonState = eState; }
        void SetAnimationState(ButtonAnimeState eState) { eAnimationState = eState; }

        void SaveCurrentPosition()
        {
            nPreviousX = x;
            nPreviousY = y;
        }

		bool HasFlag(ButtonFlag FlagType)
		{
			if(nButtonFlag && FlagType)
				return true;

			return false;
		}

    public:
        virtual void Activate();
        virtual void OnMove(int nNextX, int nNextY)     
		{ 
			x = nNextX - nDistX; 
            y = nNextY - nDistY; 
            eButtonState = BUTTONSTATE_MOVED; 
		}

        virtual void OnMoveWithInterface(int nX, int nY) { x += nX; y += nY; }
        virtual void SetDistance(int nX, int nY)        { nDistX = nX - x; nDistY = nY - y; }                      //Used for proper update movement for interface panels
        virtual bool IsButtonOnPos(int mX, int mY);
        virtual void OnDrop(int mX, int mY);  //if left button up with button pointed
        virtual void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle); 
};

#endif