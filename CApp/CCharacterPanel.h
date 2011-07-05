/*
Include 
    Character Sheet
    Character Equipment
    Character SpellBook
    Quest Diary



*/

#ifndef _CCHARPANEL_H_
    #define _CCHARPANEL_H_

#include <SDL.h>
#include <vector>

#include "CSurface.h"
#include "CApp.h"
#include "CInterface.h"

#define MAX_BUTTON_LIST 10

class CCharacterPanel : public CInterface
{
    public:
        CCharacterPanel();
        ~CCharacterPanel() {}

    private:
        CButton*        ButtonList[MAX_BUTTON_LIST];
        
    public:
        bool OnLoad();
        void OnCleanup();
        void OnRender(SDL_Surface* Surf_Display);
        void UpdateButtonsPosition();
};

#endif