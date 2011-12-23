#include "CInterfaceEquip.h"

CInterfaceEquip::CInterfaceEquip()
{
    nPosX = 300;
    nPosY = 200;

    eInterfaceType = INTERFACE_EQUIP;
}

bool CInterfaceEquip::OnLoad()
{
    nPosX = WWIDTH - INTERFACE_EQUIPMENT_W - 30;
    nPosY = 0.5 * WHEIGHT - 0.5 * INTERFACE_EQUIPMENT_H;
    nWidht = INTERFACE_EQUIPMENT_W;
    nHeight = INTERFACE_EQUIPMENT_H;

    char* SurfName = "./interface/interface_equpment_surf.png";

    if((Surf_Interface = CSurface::OnLoad(SurfName)) == NULL) 
        return false;

	for(int n = 0; n < BAG_MAX_X; ++n) 
	{   
		for(int m = 0; m < BAG_MAX_Y; ++m) 
		{   
			if(!CPlayer::Player.pPlayerCharacter->ItemListTable[n][m]) continue;

			int nX = nPosX + 10 + n*(SLOT_W_H + 5);
			int nY = nPosY + 10 + m*(SLOT_W_H + 5);

			CPlayer::Player.pPlayerCharacter->ItemListTable[n][m]->SetPositionX(nX);
			CPlayer::Player.pPlayerCharacter->ItemListTable[n][m]->SetPositionY(nY);
		}
	}

    return true;
}

void CInterfaceEquip::OnLoop()
{
	CInterface::OnLoop();

	for(int n = 0; n < BAG_MAX_X; ++n) 
	{   
		for(int m = 0; m < BAG_MAX_Y; ++m) 
		{   
			if(!CPlayer::Player.pPlayerCharacter->ItemListTable[n][m]) continue;

			CPlayer::Player.pPlayerCharacter->ItemListTable[n][m]->OnLoop();
		}
	}
}

void CInterfaceEquip::OnRender(SDL_Surface* Surf_Display)
{
	CInterface::OnRender(Surf_Display);

	if(CPlayer::Player.pPlayerCharacter == NULL) return;

	for(int n = 0; n < BAG_MAX_X; ++n) 
	{   
		for(int m = 0; m < BAG_MAX_Y; ++m) 
		{   
			if(!CPlayer::Player.pPlayerCharacter->ItemListTable[n][m]) continue;
		
			CPlayer::Player.pPlayerCharacter->ItemListTable[n][m]->OnRender(Surf_Display);
		}
	}
}

void CInterfaceEquip::OnCleanup()
{
    CInterface::OnCleanup();
}

bool CInterfaceEquip::AddButtonToSlot(CButton* pButton, int mX, int mY)
{
	if(CPlayer::Player.pPlayerCharacter == NULL) return false;

	//Only Items Can Be Added To Equpment
	if(pButton->GetButtonClass() != BUTTONCLASS_ITEM)
	{
		if(CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW])
			CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Mozes Dodac Do Equip Tylko Item");

        return false;
	}

    //For bag slots
    for(int x = 0; x < BAG_MAX_X; ++x) 
    {   
        for(int y = 0; y < BAG_MAX_Y; ++y) 
        {   
            if( ( mX > nPosX + 10 + x*(SLOT_W_H + 5)) && ( mX < nPosX + 10 + x*(SLOT_W_H + 5) + SLOT_W_H) && ( mY > nPosY + 10 + y*(SLOT_W_H + 5) ) && ( mY < nPosY + 10 + y*(SLOT_W_H + 5) + SLOT_W_H) )
            {     
				if(CPlayer::Player.pPlayerCharacter->ItemListTable[x][y] != NULL)
					return false;

				for(int n = 0; n < BAG_MAX_X; ++n) 
				{   
					for(int m = 0; m < BAG_MAX_Y; ++m) 
					{   
						if(!CPlayer::Player.pPlayerCharacter->ItemListTable[n][m]) continue;

						//we clear equip for dprevent double add item
						if(CPlayer::Player.pPlayerCharacter->ItemListTable[n][m] == pButton)
							CPlayer::Player.pPlayerCharacter->ItemListTable[n][m] = NULL;
					}
				}

				int nX = nPosX + 10 + x*(SLOT_W_H + 5);
				int nY = nPosY + 10 + y*(SLOT_W_H + 5);
                pButton->SetPositionX(nX);
                pButton->SetPositionY(nY);

				CPlayer::Player.pPlayerCharacter->ItemListTable[x][y] = pButton;

                return true;
            }
        }
    }

	return false;
}

void CInterfaceEquip::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
	CInterface::OnMouseMove( mX, mY, relX, relY, Left, Right, Middle);

	if(CPlayer::Player.pPlayerCharacter == NULL) return;

	for(int n = 0; n < BAG_MAX_X; ++n) 
	{   
		for(int m = 0; m < BAG_MAX_Y; ++m) 
		{   
			if(!CPlayer::Player.pPlayerCharacter->ItemListTable[n][m]) continue;
		
			CPlayer::Player.pPlayerCharacter->ItemListTable[n][m]->OnMouseMove( mX, mY, relX, relY, Left, Right, Middle);
		}
	}
}

CButton* CInterfaceEquip::GetButton(int nPosX, int nPosY) const
{
	if(CButton* Button = CInterface::GetButton( nPosX, nPosY))
		return Button;

	for(int n = 0; n < BAG_MAX_X; ++n) 
	{   
		for(int m = 0; m < BAG_MAX_Y; ++m) 
		{   
			if(!CPlayer::Player.pPlayerCharacter->ItemListTable[n][m]) continue;
		
			if(CPlayer::Player.pPlayerCharacter->ItemListTable[n][m]->IsButtonOnPos(nPosX, nPosY))
				return CPlayer::Player.pPlayerCharacter->ItemListTable[n][m]; 
		}
	}

    return NULL;
}

void CInterfaceEquip::DeleteButtonFromSlot(CButton* pButton) 
{ 
	for(int n = 0; n < BAG_MAX_X; ++n) 
	{   
		for(int m = 0; m < BAG_MAX_Y; ++m) 
		{   
			if(!CPlayer::Player.pPlayerCharacter->ItemListTable[n][m]) continue;

			//we clear equip for dprevent double add item
			if(CPlayer::Player.pPlayerCharacter->ItemListTable[n][m] == pButton)
				CPlayer::Player.pPlayerCharacter->ItemListTable[n][m] = NULL;
		}
	}
}