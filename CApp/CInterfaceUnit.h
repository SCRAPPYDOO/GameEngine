#ifndef _CUNITINFOPANEL_H_
    #define _CUNITINFOPANEL_H_

#include "CInterface.h"

class CInterfaceUnit : public CInterface
{
    public:
        CInterfaceUnit();
        ~CInterfaceUnit() {}

        SDL_Surface* Surf_Interface;

        SDL_Surface* Surf_UnitStatus;

    public:
        bool OnLoad();
        void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();
};

#endif

