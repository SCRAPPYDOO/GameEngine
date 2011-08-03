#ifndef _CINTERFACECHARSHEET_H_
    #define _CINTERFACECHARSHEET_H_

#include "CInterface.h"
#include <string>

class CInterfaceCharSheet : public CInterface
{
    public:
        CInterfaceCharSheet();
        ~CInterfaceCharSheet() {}

    private:

    public:
        bool OnLoad();
        void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup(); 
};

#endif