#include "CInterfaceCharSheet.h"

int TxtPosition[INTERFACE_CHARSHEET_MAX][2] =
{
    {8, 44}, //Character Name 
    {429, 169}, //Actual Health
    {66, 5},
    {22, 5},
    {77, 5},
    {33, 5},
    {88, 5},
    {44, 5},
    {99, 5},
    {55, 5},
};

CInterfaceCharSheet::CInterfaceCharSheet()
{
    eInterfaceType = INTERFACE_CHARACTERSHEET;
    //pChar = NULL;

    for(int i = 0;i < INTERFACE_CHARSHEET_MAX;i++) 
    {
        TextSurface[i] = NULL; 
    }
}

bool CInterfaceCharSheet::OnLoad()
{
    if(CInterface::OnLoad() == false)
        return false;

    //Set Up a  Character
    UpdateInterface();

    return true;
}

void CInterfaceCharSheet::OnLoop()
{
    CInterface::OnLoop();
    
    UpdateInterface();
}

void CInterfaceCharSheet::OnRender(SDL_Surface* Surf_Display)
{
    CInterface::OnRender(Surf_Display);

    for(int i = 0;i < INTERFACE_CHARSHEET_MAX;i++) 
    {
        if(!TextSurface[i]) continue;

        CSurface::OnDraw(Surf_Display, TextSurface[i], nPosX + TxtPosition[i][0], nPosY + TxtPosition[i][1]);
    }

	for(int n = 0; n < MAX_EQUIPED_ITEMS; ++n) 
	{   
		if(!CPlayer::Player.pPlayerCharacter->ItemEquipedList[n]) continue;
		
		CPlayer::Player.pPlayerCharacter->ItemEquipedList[n]->OnRender(Surf_Display);
	}
}    

void CInterfaceCharSheet::OnCleanup()
{
    CInterface::OnCleanup();
    CleanUpSurface();
}

void CInterfaceCharSheet::CleanUpSurface()
{
    for(int i=0; i<INTERFACE_CHARSHEET_MAX; ++i)
    {
        if(TextSurface[i]) 
		    SDL_FreeSurface(TextSurface[i]);

	    TextSurface[i] = NULL;
    }  
}


void CInterfaceCharSheet::UpdateInterface()
{
	CleanUpSurface();

	if(CPlayer::Player.pPlayerCharacter == NULL)
		return;

    for(int i=0; i<INTERFACE_CHARSHEET_MAX; ++i)
    { 
        std::string strText = "";
        int nValue = 0;

		int Type = 0;

        switch(i)
        {
			//string types
            case 0: strText = CPlayer::Player.pPlayerCharacter->GetName(); Type = 1; break;

			//int types
            case 1: nValue = CPlayer::Player.pPlayerCharacter->GetActualHealth(); Type = 2; break;
            default: break;
        }

		switch(Type)
		{
            case 1: TextSurface[i] = CSurface::RenderText(strText); break;
            case 2: TextSurface[i] = CSurface::RenderText(nValue); break;
			default: break;
		}   
    }  
}

int EquipSlots[16][2] =
{
	{ 438, 36},
	{ 438, 76},
	{ 438,116},
	{ 438,156},
	{ 438,196},
	{ 438,236},
	{ 438,276},
	{ 438,316},
	{ 622, 36},
	{ 622, 76},
	{ 622,116},
	{ 622,156},
	{ 622,196},
	{ 622,236},
	{ 622,276},
	{ 622,316},
};

int ItemSlot[8][2] =
{
	{ItemTypeHead,		ItemTypeEyes,},
	{ItemTypeChest,		ItemTypeTrincket,},
	{ItemTypeBoots,		ItemTypeQuiver,},
	{ItemTypeWrists,	ItemTypeAmmo,},
	{ItemTypeCloak,		ItemTypeShield,},
	{ItemTypeBelt,		ItemTypeWeapon,},
	{ItemTypeRing,		ItemTypeNecklace,},
	{ItemTypeRing,		ItemTypeHands,},
};

bool CInterfaceCharSheet::AddButtonToSlot(CButton* pButton, int mX, int mY)
{
	if(CPlayer::Player.pPlayerCharacter == NULL) return false;
	//Restriction with add ability button and other
	//Only Items Can Be Added To Equpment
    if(pButton->GetButtonClass() != BUTTONCLASS_ITEM)
	{
		if(CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW])
			CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Mozes Dodac Do Equip Tylko Item");

        return false;
	}

    //For bag slots
	int x = 0;
	int SecondRowX = 440;
	int number = 0;

    for(int y = 0; y < MAX_EQUIPED_ITEMS; ++y) 
    {   

		if( y > 7)
		{
			if( x == 1)
				return false;
			y = 0;
			x = 1;
			SecondRowX = 485;


		}

        if( ( mX > nPosX + SecondRowX + x*(SLOT_W_H + 5)) && ( mX < nPosX + SecondRowX + x*(SLOT_W_H + 5) + SLOT_W_H) && ( mY > nPosY + 10 +  y*(SLOT_W_H + 5) ) && ( mY < nPosY + 10 +  y*(SLOT_W_H + 5) + SLOT_W_H) )
        {      
			if(CPlayer::Player.pPlayerCharacter->ItemEquipedList[number] != NULL)
				return false;

			//if(ItemSlot[y][x] != ItemTable[pButton->GetID()].ItemType) 
			//{
			//	CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("DEBUG: Invalid Slot Item");
			//	return false;
			//}

			for(int n = 0; n < MAX_EQUIPED_ITEMS; ++n) 
			{   
				if(!CPlayer::Player.pPlayerCharacter->ItemEquipedList[n]) continue;

				if(CPlayer::Player.pPlayerCharacter->ItemEquipedList[n] == pButton)
					CPlayer::Player.pPlayerCharacter->ItemEquipedList[n] = NULL;
			}

			int nX = nPosX + SecondRowX + x*(SLOT_W_H + 5);
			int nY = nPosY + 10 + y*(SLOT_W_H + 5);
            pButton->SetPositionX(nX);
            pButton->SetPositionY(nY);

			CPlayer::Player.pPlayerCharacter->ItemEquipedList[number] = pButton;

			return true;
        }


		++number;
    }

	return false;
}

void CInterfaceCharSheet::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
	CInterface::OnMouseMove( mX, mY, relX, relY, Left, Right, Middle);

	if(CPlayer::Player.pPlayerCharacter == NULL) return;

	for(int n = 0; n < MAX_EQUIPED_ITEMS; ++n) 
	{   
		if(!CPlayer::Player.pPlayerCharacter->ItemEquipedList[n]) continue;
		
		CPlayer::Player.pPlayerCharacter->ItemEquipedList[n]->OnMouseMove( mX, mY, relX, relY, Left, Right, Middle);
	}
}

CButton* CInterfaceCharSheet::GetButton(int nPosX, int nPosY) const
{
	if(CButton* Button = CInterface::GetButton( nPosX, nPosY))
		return Button;

	for(int n = 0; n < MAX_EQUIPED_ITEMS; ++n) 
	{   
		if(!CPlayer::Player.pPlayerCharacter->ItemEquipedList[n]) continue;
		
		if(CPlayer::Player.pPlayerCharacter->ItemEquipedList[n]->IsButtonOnPos(nPosX, nPosY))
			return CPlayer::Player.pPlayerCharacter->ItemEquipedList[n]; 
	}

    return NULL;
}

void CInterfaceCharSheet::DeleteButtonFromSlot(CButton* pButton) 
{ 
	for(int n = 0; n < MAX_EQUIPED_ITEMS; ++n) 
	{   
		if(!CPlayer::Player.pPlayerCharacter->ItemEquipedList[n]) continue;
		
		if(CPlayer::Player.pPlayerCharacter->ItemEquipedList[n] == pButton)
			CPlayer::Player.pPlayerCharacter->ItemEquipedList[n] = NULL; 
	}
}
