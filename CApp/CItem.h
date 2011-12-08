#ifndef _CITEM_H_
    #define _CITEM_H_

#include "CSurface.h"
#include "CApp.h"
#include "CButton.h"

class CItem : public CButton
{
    public:
        CItem()
		{
			eButtonClass = BUTTONCLASS_ITEM;

		}
        CItem(InterfaceType eType);
        ~CItem() {}

    public:
        //bool OnLoad();
        //void OnRender(SDL_Surface* Surf_Display);
        //void OnCleanup();


	private:
		int nItemID;
		int nItemGUID;
		int nItemCount;
};

#endif