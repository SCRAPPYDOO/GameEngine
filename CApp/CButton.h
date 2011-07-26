#ifndef _CBUTTON_H_
    #define _CBUTTON_H_

#include <vector>

#include "CSurface.h"
#include "CInterface.h"

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
	BUTTON_DEFAULT	= 99,
	BUTTON_PLAY		= 0,   //enter to world
	BUTTON_QUIT		= 1,   //quit from game

    BUTTON_CREATECHARACTER = 3,  // create character

    //Game Menu Button
    BUTTON_GAMEMENU_QUIT = 10,
    BUTTON_GAMEMENU_RETURN = 11,

    BUTTON_CHARPANEL_CHARSHEET = 20,
    BUTTON_CHARPANEL_EQUPMENT = 21,
    BUTTON_CHARPANEL_SPELLBOOK = 22,
    BUTTON_CHARPANEL_QUESTDIARY = 23,
    BUTTON_CHARPANEL_GAMEMENU   = 24,

    BUTTON_BAG_SWITCHBAG    = 50,
    BUTTON_BAG_QUIT         = 51,
    BUTTON_BAG_SLOT_ONE     = 52,  //up to 55  4 bag slots
    BUTTON_BAG_SLOT_TWO     = 53, 
    BUTTON_BAG_SLOT_THREE   = 54,
    BUTTON_BAG_SLOT_FOUR    = 55,

    BUTTON_LOOT_QUIT        = 56,
    BUTTON_LOOT_LOOTALL     = 57,
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
	BUTTONFLAG_NOTMOVED		= 0x01,
};

class CInterface;

class CButton
{
	public:
        CButton() {}
        CButton(int nPosX, int nPosY, ButtonType Type);
        ~CButton() {}

    protected:
        SDL_Surface*     pButtonSurface;

        ButtonClass      eButtonClass;
		ButtonType       eType;
        ButtonState      eButtonState;
        ButtonAnimeState eAnimationState;
		int				 nButtonFlag;

		int x, y, w, h;
        
        int nDistX, nDistY;

    public:
        virtual bool OnLoad();
		virtual bool OnLoad(ButtonType eType);
		virtual void OnRender(SDL_Surface* Surf_Display);
        virtual void OnCleanup();

        int nPreviousX, nPreviousY;

    public: //Methods for variables
        ButtonType GetButtonType() const { return eType; }
        ButtonState GetButtonState() const { return eButtonState; }

        int GetPosX() const { return x; }
        int GetPosY() const { return y; }
        int GetWidht() const { return w; }
        int GetHeight() const { return h; }

        void SetPositionX(int nValue) { x = nValue;}
        void SetPositionY(int nValue) { y = nValue;}
        void SetButtonState(ButtonState eState) { eButtonState = eState; }
        void SetAnimationState(ButtonAnimeState eState) { eAnimationState = eState; }

        void SetButtonClass(ButtonClass eClass) { eButtonClass = eClass; }

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