#include "CItem.h"

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