#ifndef _CITEM_H_
    #define _CITEM_H_

#include "CSurface.h"
#include "CApp.h"
#include "CButton.h"

/*
    INTERFACE_BAG
    INTERFACE_EQUIPMENT
*/
#define MAX_BAG_SLOTS   4

class CItem : public CButton
{
    public:
        CItem();
        CItem(InterfaceType eType);
        ~CItem() {}

    public:
        bool OnLoad();
        void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();
};

#endif