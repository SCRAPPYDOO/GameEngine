#ifndef _CITEM_H_
    #define _CITEM_H_

#include "CSurface.h"
#include "CApp.h"
#include "CButton.h"
#include "ItemDefines.h"

#define SLOT_W_H  45

class CItem : public CButton
{
    public:
        CItem();
        CItem(int ItemID, int ItemCount, int X, int Y );
        ~CItem() {}

    public:
        bool OnLoad();
        //void OnRender(SDL_Surface* Surf_Display);
        //void OnCleanup();

		void Activate() {}

	private:
		int nItemID;
		int nItemGUID;
		int nItemCount;

	public:
		void GenerateGUID();

		int GetID() { return nItemID; }
		std::string GetItemName() { return ItemTable[nItemID].Name; }



		//GetBonusType()
		//GetBonus
};

#endif