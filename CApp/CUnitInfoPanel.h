#ifndef _CUNITINFOPANEL_H_
    #define _CUNITINFOPANEL_H_

#include <SDL.h>
#include <vector>

#include "CSurface.h"
#include "CApp.h"
#include "CInterface.h"

class CUnitInfoPanel : public CInterface
{
    public:
        CUnitInfoPanel();

        ~CUnitInfoPanel() {}

        SDL_Surface* Surf_UnitInfoPanel;
        SDL_Surface* Surf_UnitStatus;

    public:
        bool OnLoad();
        void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();
};

#endif

