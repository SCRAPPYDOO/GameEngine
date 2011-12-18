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
			x = 0;
			y = 0;
			w = 45;
			h = 45;
			nButtonFlag = 0;
			nPreviousX = x;
			nPreviousY = y;

			pButtonSurface = NULL;
			eButtonState = BUTTONSTATE_UNSELECTED;
			eAnimationState = BUTTON_ANIME_NORMAL;
			eButtonClass = BUTTONCLASS_ITEM;
		}

        CItem(int ItemID, int ItemCount, int X, int Y )
		{
			nItemID = ItemID;
			nItemCount = ItemCount;
			x = X;
			y = Y;
			w = 45;
			h = 45;
			nButtonFlag = 0;
			nPreviousX = x;
			nPreviousY = y;

			pButtonSurface = NULL;
			eButtonState = BUTTONSTATE_UNSELECTED;
			eAnimationState = BUTTON_ANIME_NORMAL;
			eButtonClass = BUTTONCLASS_ITEM;
			eButtonType = BUTTON_CHARPANEL_CHARSHEET;
		}

        ~CItem() {}

    public:
        bool OnLoad();
        //void OnRender(SDL_Surface* Surf_Display);
        //void OnCleanup();


	private:
		int nItemID;
		int nItemGUID;
		int nItemCount;

	public:



		void GenerateGUID();


		//GetBonusType()
		//GetBonus
};

#endif