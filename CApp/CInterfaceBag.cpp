#include "CInterfaceBag.h"
#include <string> 
#include <fstream>

CInterfaceBag::CInterfaceBag()
{
    nPosX = 400;
    nPosY = 200;
    nWidht = INTERFACE_BAG_W;
    nHeight = INTERFACE_BAG_H;

    OldX = 0;
    OldY = 0;

    ActualBag = BAG_ONE;

    Surf_Interface = NULL;

    eInterfaceType = INTERFACE_BAG;
}

bool CInterfaceBag::OnLoad()
{
    if(CInterface::OnLoad() == false)
        return false;

    LoadBag(ActualBag);

    return true;
}

void CInterfaceBag::OnCleanup()
{
    SaveBag(ActualBag);
    CleanUpBag(ActualBag);

    CInterfaceA::OnCleanup();
}

void CInterfaceBag::SwitchBag(BAGSLOT NewBag)
{
    //if(ActualBag == NewBag)
        //return;

    SaveBag(ActualBag);
    CleanUpBag(ActualBag);
    LoadBag(NewBag);
}

void CInterfaceBag::SaveBag(BAGSLOT BagSlot)
{
    //Open a file for writing 
    switch(BagSlot)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        default: break;
    }

    std::ofstream save( "./save/bag1_save" ); 
    //Write offsets to the file 


    save << "51"; 
    save << " "; 

    //Close the file 
    save.close();

}

void CInterfaceBag::CleanUpBag(BAGSLOT BagSlot)
{
    for(int i = 0;i < ButtonsList.size();i++) 
    {   
        if(!ButtonsList[i] || ButtonsList[i]->GetButtonClass() != BUTTONCLASS_ITEM) continue;
                
        ButtonsList[i]->OnCleanup();
        ButtonsList[i] = NULL;
    }
}

void CInterfaceBag::LoadBag(BAGSLOT BagSlot)
{
    int upleftX = nPosX + 10;
    int upLeftY = nPosY + 100;

    for(int x = 0; x < BAG_MAX_X; ++x) 
    {   
        for(int y = 0; y < BAG_MAX_Y; ++y) 
        {   
            CButton *pButton = new CButton(upleftX + x*33, upLeftY + y*33, BUTTON_CHARPANEL_GAMEMENU);

            if(pButton->OnLoad() == false)
                break;

            ButtonsList.push_back(pButton);
        }
    }

    std::ifstream load( "./save/bag1_save" );

    if( load != NULL ) 
    { 
        int offset; 
        load >> offset; 
        load.close(); 
    }
}




