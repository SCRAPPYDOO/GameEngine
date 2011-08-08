#ifndef _CINTERFACECHARSHEET_H_
    #define _CINTERFACECHARSHEET_H_

#include "CInterface.h"
#include <string>

#define INTERFACE_CHARSHEET_MAX 10
 
class CInterfaceCharSheet : public CInterface
{
    public:
        CInterfaceCharSheet();
        ~CInterfaceCharSheet() {}

    private:
        //CEntity* pChar; //character with we show on character sheet
        SDL_Surface* TextSurface[INTERFACE_CHARSHEET_MAX];

    public:
        bool OnLoad();
        void OnLoop();
        void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();

        void UpdateInterface();
};

#endif