#ifndef _CBUTTON_H_
    #define _CBUTTON_H_

#include <vector>

#include "CSurface.h"
#include "CInterface.h"

#define GAME_BUTTON_SIZE_W 30
#define GAME_BUTTON_SIZE_H 30

#define GAME_OPTION_BUTTON_SIEZ_W 140
#define GAME_OPTION_BUTTON_SIZE_H 30

enum ButtonType
{
	BUTTON_DEFAULT	= 99,
	BUTTON_PLAY		= 0,
	BUTTON_QUIT		= 1,
    BUTTON_MENU     = 2,

    //Game Menu Button
    BUTTON_GAMEMENU_QUIT = 10,
    BUTTON_GAMEMENU_RETURN = 11,

    BUTTON_CHARPANEL_CHARSHEET = 20,
    BUTTON_CHARPANEL_EQUPMENT = 21,
    BUTTON_CHARPANEL_SPELLBOOK = 22,
    BUTTON_CHARPANEL_QUESTDIARY = 23,
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

class CButton
{
	public:
		CButton();
        CButton(int nPosX, int nPosY, ButtonType Type);
        CButton(int nPosX, int nPosY, ButtonType Type, SDL_Surface* pButtonSurface);

        ~CButton() {}

        static CButton ButtonControl;

		static std::vector<CButton*>    ButtonList;

    protected:
        SDL_Surface*     pButtonSurface;

		ButtonType       eType;
        ButtonState      eButtonState;
        ButtonAnimeState eAnimationState;

		int x, y, w, h; 
        int nDistX, nDistY;

    public:
        virtual bool OnLoad();
		virtual bool OnLoad(ButtonType eType);
		virtual void OnRender(SDL_Surface* Surf_Display);
        virtual void OnCleanup();

    public: //Methods for variables
        CButton* GetButton(int nX, int nY);
        ButtonType GetButtonType() { return eType; }
        ButtonState GetButtonState() { return eButtonState; }

        int GetPosX() { return x; }
        int GetPosY() { return y; }
        int GetWidht() { return w; }
        int GetHeight() { return h; }

        void SetPositionX(int nValue) { x = nValue;}
        void SetPositionY(int nValue) { y = nValue;}
        void SetButtonState(ButtonState eState) { eButtonState = eState; }
        void SetAnimationState(ButtonAnimeState eState) { eAnimationState = eState; }

    public:
        virtual void Activate();
        virtual void OnMove(int nNextX, int nNextY)     { x = nNextX - nDistX; y = nNextY - nDistY; eButtonState = BUTTONSTATE_MOVED; }
        virtual void SetDistance(int nX, int nY)        { nDistX = nX - x; nDistY = nY - y; }                      //Used for proper update movement for interface panels
        virtual bool IsButtonOnPos(int mX, int mY);
        virtual void OnDrop(int mX, int mY);  //if left button up with button pointed
        
    public: //Button Control Methods
        void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
        void DeleteButton(CButton* pButton);

       
};

#endif