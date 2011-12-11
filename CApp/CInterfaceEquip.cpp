#include "CInterfaceEquip.h"
#include <string> 
#include <fstream>

CInterfaceEquip::CInterfaceEquip()
{
    nPosX = 300;
    nPosY = 200;

    eInterfaceType = INTERFACE_EQUIP;
}

bool CInterfaceEquip::OnLoad()
{
    if(CInterface::OnLoad() == false)
        return false;

    return true;
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
    //SaveBag();
    //CleanUpBag();

    CInterface::OnCleanup();
}

//
//void CInterfaceEquip::SaveBag()
//{
//    //Open a file for writing 
//
//    std::ofstream save( "./save/bag1_save" ); 
//
//    //ToDo: Need to save all buttons with class ITEM and their coorinates
//
//    //Write offsets to the file 
//    save << "51"; 
//    save << " "; 
//
//    //Close the file 
//    save.close();
//}
//
//void CInterfaceEquip::CleanUpBag()
//{
//    for(int i = 0;i < ButtonsList.size();i++) 
//    {   
//        if(!ButtonsList[i] || ButtonsList[i]->GetButtonClass() != BUTTONCLASS_ITEM) continue;
//                
//        ButtonsList[i]->OnCleanup();
//        ButtonsList[i] = NULL;
//    }
//}
//
//void CInterfaceEquip::LoadBag()
//{
//    //int upleftX = nPosX + 10;
//    //int upLeftY = nPosY + 100;
//
//    //for(int x = 0; x < BAG_MAX_X; ++x) 
//    //{   
//    //    for(int y = 0; y < BAG_MAX_Y; ++y) 
//    //    {   
//    //        CButton *pButton = new CButton(upleftX + x*33, upLeftY + y*33, BUTTON_CHARPANEL_GAMEMENU);
//
//    //        if(pButton->OnLoad() == false)
//    //            break;
//
//    //        ButtonsList.push_back(pButton);
//    //    }
//    //}
//
//    std::ifstream load( "./save/bag1_save" );
//
//    if( load != NULL ) 
//    { 
//        int offset; 
//        load >> offset; 
//        load.close(); 
//    }
//}

bool CInterfaceEquip::AddButtonToSlot(CButton* pButton, int mX, int mY)
{
	if(CPlayer::Player.pPlayerCharacter == NULL) return false;
	//Restriction with add ability button and other
	//Only Items Can Be Added To Equpment
 //   if(pButton->GetButtonClass() != BUTTONCLASS_ITEM)
	//{
	//	if(CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW])
	//		CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Mozes Dodac Do Equip Tylko Item");

 //       return false;
	//}


    //For bag slots

    for(int x = 0; x < BAG_MAX_X; ++x) 
    {   
        for(int y = 0; y < BAG_MAX_Y; ++y) 
        {   
            if( ( mX > nPosX + 10 + x*30) && ( mX < nPosX + 10 + x*30 + SLOT_W_H) && ( mY > nPosY + 10 + y*30 ) && ( mY < nPosY + 10 + y*30 + SLOT_W_H) )
            {      
                //ToDo: Need to check if on slot  is any aother button then return false
                //if(CButton *Button = GetButton(mX, mY))
                //    if(Button != NULL)
                //        return false;
	
				if(CPlayer::Player.pPlayerCharacter->ItemListTable[x][y] != NULL)
					return false;

				//int nX = nPosX + 10 + x*30;
				//int nY = nPosY + 10 + y*30;
				////If Slot Is Empty We SetUp Porper Coordinates To Button
    //            pButton->SetPositionX(nX);
    //            pButton->SetPositionY(nY);

				//Check If Button Is Already In Same Interface Just Change Place
				//Prevent Double Add 1 Button to Button List
				//for(int i = 0;i < ButtonsList.size();i++) 
				//{   
				//	if(!ButtonsList[i]) continue;
				//	if(ButtonsList[i] == pButton)
				//		return true;
				//}

				for(int n = 0; n < BAG_MAX_X; ++n) 
				{   
					for(int m = 0; m < BAG_MAX_Y; ++m) 
					{   
						if(!CPlayer::Player.pPlayerCharacter->ItemListTable[n][m]) continue;

						if(CPlayer::Player.pPlayerCharacter->ItemListTable[n][m] == pButton)
							CPlayer::Player.pPlayerCharacter->ItemListTable[n][m] = NULL;
					}
				}

				int nX = nPosX + 10 + x*30;
				int nY = nPosY + 10 + y*30;
                pButton->SetPositionX(nX);
                pButton->SetPositionY(nY);

				CPlayer::Player.pPlayerCharacter->ItemListTable[x][y] = pButton;

                //ButtonsList.push_back(pButton);
		
                return true;
            }
        }
    }

	//return false;
    //for equip slots
    //for(int x = 0; x < 2; ++x) 
    //{   
    //    for(int y = 0; y < 6; ++y) 
    //    {   
    //        if( ( mX > nPosX + 10 + x*33 ) && ( mX < nPosX + 10 + x*33 + 30) && ( mY > nPosY + 100 + y*33 ) && ( mY < nPosY + 100 + y*33 + 30 ) )
    //        {
    //            switch(y)
    //            {
    //                case 0: 
    //                {
    //                    //if(x == 0 || ItemType_Ammo != pButton->GetItemType())
    //                    //    return false;
    //                    //break;
    //                }
    //                case 1:
    //                {
    //                    //if(x == 0 && ItemType_Weapon == pButton->GetItemType() || x == 1 && ( ItemType_Weapon == pButton->GetItemType() || ItemType_Shield == pButton->GetItemType() /* || or offhand) */ ))
    //                    //    break;
  

    //                }
    //                case 2:
    //                case 3:
    //                case 4:
    //                case 5:
    //                default: return false;
    //            }
    //            //Add Button if no return false;
    //            return true;
    //        }
    //    }
    //}
	return false;
}
//
//CButton* CInterfaceEquip::AddItemToSlot(CButton* pButton, int mX, int mY)
//{
//	//if(pButton->GetButtonClass() != BUTTONCLASS_ITEM)
//	//	return pButton;
//
// //   //For bag slots
// //   for(int x = 0; x < BAG_MAX_X; ++x) 
// //   {   
// //       for(int y = 0; y < BAG_MAX_Y; ++y) 
// //       {   
// //           if( ( mX > nPosX + 10 + x*33 + 29 ) && ( mX < nPosX + 10 + x*33 + 29 + INTERFACE_EQUIPMENT_SLOT_H_W) && ( mY > nPosY + 100 + y*33 ) && ( mY < nPosY + 100 + y*33 + INTERFACE_EQUIPMENT_SLOT_H_W) )
// //           {      
// //               //Need to check if on slot  is any aother button then return this button to handle mouse
//	//			if(ItemSlot[x][y])
//	//				return ItemSlot[x][y];
//
//	//			ItemSlot[x][y] = pButton;
// //           }
// //       }
// //   }
//	//return NULL;
//}
//
//jestem nad  interface
//	Additem to slot
//	if return null

//button na  pozycji x y
//	bierzmy go myszka i prznosimy do interfacu
//	gdy sie dodaje zmeinia pozycje
//
//
//	loot all
//	lista buttonow -> add do lista buttonow
//	i u
//	suniecie
//
//
//	transfer z interfacu do interfacu po spelnieniu warunkow
//
//	czyli klikamy na buttonz interfacu a zapisajumey interface
//
//
//	klik prawym
//	if
//	CInterface = get interface x y
//	if
//		CButton = get nbutton x y

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
	CInterface::GetButton( nPosX, nPosY);

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
