#include "CItem.h"

CItem::CItem()
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

CItem::CItem(int ItemID, int ItemCount, int X, int Y )
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
}

bool CItem::OnLoad()
{
    char* Surf_Name = "./buttons/item_name.png";

	switch(nItemID)
	{

		default: break;
	}

    if((pButtonSurface = CSurface::OnLoad(Surf_Name)) == false)
        return false;

    return true;
}