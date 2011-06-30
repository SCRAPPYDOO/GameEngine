#ifndef _CGAMEMENU_H_
    #define _CGAMEMENU_H_

#include <SDL.h>
#include <vector>

#include "CSurface.h"
#include "CApp.h"
#include "CInterface.h"

class CGameMenu : public CInterface
{
    public:
        CGameMenu();
        ~CGameMenu() {}

        SDL_Surface* Surf_GameMenu;  
        SDL_Surface* Surf_GameMenuButtons;

    public:
        std::vector<CButton*>     GameMenuButtonsList;

    public:
        bool OnLoad();
        void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();

        void OnMove(int nNextX, int nNextY);
        void UpdateButtonsPosition();
};

#endif