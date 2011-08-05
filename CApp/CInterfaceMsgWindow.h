#ifndef _CINTERFACEMSG_H_
    #define _CINTERFACEMSG_H_

#include "CInterface.h"
#include <string>

#define INTERFACE_MSGWINDOW_MAX_TEXT_LINES 15

class CInterfaceMsgWindow : public CInterface
{
    public:
        CInterfaceMsgWindow();
        ~CInterfaceMsgWindow() {}

    private:
        SDL_Surface *Masage[INTERFACE_MSGWINDOW_MAX_TEXT_LINES];

    public:
        bool OnLoad();
        void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup(); 

        void AddMsg(char* msg);
};

#endif