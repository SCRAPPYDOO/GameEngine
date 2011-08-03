#include "CInterfaceEquip.h"
#include <string> 
#include <fstream>

CInterfaceEquip::CInterfaceEquip()
{
    nPosX = 400;
    nPosY = 200;

    ActualBag = BAG_ONE;
    eInterfaceType = INTERFACE_EQUIP;
}

bool CInterfaceEquip::OnLoad()
{
    if(CInterface::OnLoad() == false)
        return false;

    LoadBag(ActualBag);

    return true;
}

void CInterfaceEquip::OnCleanup()
{
    SaveBag();
    CleanUpBag();

    CInterface::OnCleanup();
}

void CInterfaceEquip::SwitchBag(BAGSLOT NewBag)
{
    if(ActualBag == NewBag)
        return;

    SaveBag();
    CleanUpBag();
    LoadBag(NewBag);
}

void CInterfaceEquip::SaveBag()
{
    //Open a file for writing 
    switch(ActualBag)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        default: break;
    }

    std::ofstream save( "./save/bag1_save" ); 

    //ToDo: Need to save all buttons with class ITEM and their coorinates

    //Write offsets to the file 
    save << "51"; 
    save << " "; 

    //Close the file 
    save.close();
}

void CInterfaceEquip::CleanUpBag()
{
    for(int i = 0;i < ButtonsList.size();i++) 
    {   
        if(!ButtonsList[i] || ButtonsList[i]->GetButtonClass() != BUTTONCLASS_ITEM) continue;
                
        ButtonsList[i]->OnCleanup();
        ButtonsList[i] = NULL;
    }
}

void CInterfaceEquip::LoadBag(BAGSLOT BagSlot)
{
    //int upleftX = nPosX + 10;
    //int upLeftY = nPosY + 100;

    //for(int x = 0; x < BAG_MAX_X; ++x) 
    //{   
    //    for(int y = 0; y < BAG_MAX_Y; ++y) 
    //    {   
    //        CButton *pButton = new CButton(upleftX + x*33, upLeftY + y*33, BUTTON_CHARPANEL_GAMEMENU);

    //        if(pButton->OnLoad() == false)
    //            break;

    //        ButtonsList.push_back(pButton);
    //    }
    //}

    std::ifstream load( "./save/bag1_save" );

    if( load != NULL ) 
    { 
        int offset; 
        load >> offset; 
        load.close(); 
    }
}

bool CInterfaceEquip::AddButtonToSlot(CButton* pButton, int mX, int mY)
{
    if(pButton->GetButtonClass() != BUTTONCLASS_ITEM)
        return false;

    //For bag slots
    for(int x = 0; x < INTERFACE_BAG_MAXSLOT_X; ++x) 
    {   
        for(int y = 0; y < INTERFACE_BAG_MAXSLOT_Y; ++y) 
        {   
            if( ( mX > nPosX + 10 + x*100 + 29 ) && ( mX < nPosX + 10 + x*33 + 29 + INTERFACE_EQUIPMENT_SLOT_H_W) && ( mY > nPosY + 100 + y*33 ) && ( mY < nPosY + 100 + y*33 + INTERFACE_EQUIPMENT_SLOT_H_W) )
            {      
                //ToDo: Need to check if on slot  is any aother button then return false
                if(CButton *Button = GetButton(mX, mY))
                    if(Button != NULL)
                        return false;

                pButton->SetPositionX(nPosX + 10 + x*33);
                pButton->SetPositionY(nPosY + 100 + y*33);
                ButtonsList.push_back(pButton);
                return true;
            }
        }
    }

    //for equip slots
    for(int x = 0; x < 2; ++x) 
    {   
        for(int y = 0; y < 6; ++y) 
        {   
            if( ( mX > nPosX + 10 + x*33 ) && ( mX < nPosX + 10 + x*33 + 30) && ( mY > nPosY + 100 + y*33 ) && ( mY < nPosY + 100 + y*33 + 30 ) )
            {
                switch(y)
                {
                    case 0: 
                    {
                        //if(x == 0 || ItemType_Ammo != pButton->GetItemType())
                        //    return false;
                        //break;
                    }
                    case 1:
                    {
                        //if(x == 0 && ItemType_Weapon == pButton->GetItemType() || x == 1 && ( ItemType_Weapon == pButton->GetItemType() || ItemType_Shield == pButton->GetItemType() /* || or offhand) */ ))
                        //    break;
  

                    }
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    default: return false;
                }
                //Add Button if no return false;
                return true;
            }
        }
    }
    return false;
}




