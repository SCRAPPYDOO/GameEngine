#ifndef _CBUTTONPANEL_H_
    #define _CBUTTONPANEL_H_

#include <SDL.h>
#include <vector>

#include "CSurface.h"
#include "CApp.h"
#include "CInterface.h"

class CButtonPanel : public CInterface
{
    public:
        CButtonPanel();

        ~CButtonPanel() {}

        SDL_Surface* Surf_ButtonPanel;     

    public:
        std::vector<CButton*>     PanelButtonsPlace;

    public:
        bool OnLoad();
        void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();

        void OnMove(int nNextX, int nNextY);
        void AddButton();
        void UpdateButtonsPosition();
};

#endif