#include "CInterfaceB.h"
#include <string> 
#include <fstream>

CInterfaceB::CInterfaceB()
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

CInterfaceB::CInterfaceB(InterfaceType eType)
{
    nPosX = 50;
    nPosY = 50;

    nWidht = INTERFACE_BAG_W;
    nHeight = INTERFACE_BAG_H;

    ActualBag = BAG_ONE;

    OldX = 0;
    OldY = 0;

    Surf_Interface = NULL;
    eInterfaceType = eType;

    for(int BagSlot = 0; BagSlot < BAG_MAX_SLOTS; ++BagSlot) 
    {   
        for(int x = 0; x < BAG_MAX_X; ++x) 
        {   
            for(int y = 0; y < BAG_MAX_Y; ++y) 
            {   
                ItemList[BagSlot][x][y] = NULL;
            }
        }
    }
}

bool CInterfaceB::OnLoad()
{
	//OnCleanup();

    if(CInterface::OnLoad() == false)
        return false;

	//InterfaceObjectList.push_back(this);

    LoadBag(ActualBag);

    return true;
}

void CInterfaceB::OnCleanup()
{
    SaveBag(ActualBag);
    CleanUpBag(ActualBag);

    CInterfaceA::OnCleanup();
}

void CInterfaceB::UpdateButtonsPosition()
{
    if(OldX == 0 && OldY == 0)
        return;

    for(int i = 0;i < ButtonsList.size();i++) 
    {   
        if(!ButtonsList[i]) continue;
                
        ButtonsList[i]->OnMoveWithInterface(nPosX-OldX,nPosY-OldY);
    }

    for(int x = 0; x < BAG_MAX_X; ++x) 
    {   
        for(int y = 0; y < BAG_MAX_Y; ++y) 
        {   
            if(!ItemList[ActualBag][x][y]) continue;

            ItemList[ActualBag][x][y]->OnMoveWithInterface(nPosX-OldX,nPosY-OldY);
        }
    }

    OldX = 0;
    OldY = 0;
}

void CInterfaceB::LoadButtons()
{
    ButtonType eType = BUTTON_DEFAULT;

    int x = 0;
	int y = 0;

    switch(eInterfaceType)
    {
        case INTERFACE_BAG:
		{
			for(int i=0; i<2; ++i)
			{
				switch(i)
				{
					case 0: eType = BUTTON_BAG_QUIT; x = nPosX + nWidht - 30; y = nPosY; break;
                    case 1: eType = BUTTON_BAG_SLOT_ONE; x = nPosX; y = nPosY; break;

                    default: break;
				}
					
                CButton *pButton = new CButton(x, y, eType);

				if(pButton->OnLoad() == false)
                    break;

                ButtonsList.push_back(pButton);
				CButton::ButtonList.push_back(pButton);
			}

			break;
		}

        default: break;
    }
}

void CInterfaceB::SwitchBag(BAGSLOT NewBag)
{
    //if(ActualBag == NewBag)
        //return;

    SaveBag(ActualBag);
    CleanUpBag(ActualBag);
    LoadBag(NewBag);
}

void CInterfaceB::SaveBag(BAGSLOT BagSlot)
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

void CInterfaceB::CleanUpBag(BAGSLOT BagSlot)
{
    for(int x = 0; x < BAG_MAX_X; ++x) 
    {   
        for(int y = 0; y < BAG_MAX_Y; ++y) 
        {   
            if(!ItemList[BagSlot][x][y]) continue;

            ItemList[BagSlot][x][y]->OnCleanup();
            ItemList[BagSlot][x][y] = NULL;
        }
    }
}

void CInterfaceB::LoadBag(BAGSLOT BagSlot)
{
    //Open a file for reading 
    std::ifstream load( "./save/bag1_save" );

    //If the file loaded 
    if( load != NULL ) 
    { 
        //The offset 
        int offset; 

        load >> offset; 

        ButtonType eType = static_cast<ButtonType>(offset);

        CButton *pButton = new CButton(nPosX + 50, nPosY + 100, eType);

		if(pButton->OnLoad() == false)
            return;

        ButtonsList.push_back(pButton);
		CButton::ButtonList.push_back(pButton);

        //Close the file 
        load.close(); 
    }

}



