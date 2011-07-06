#include "CInterfaceB.h"

CInterfaceB::CInterfaceB()
{
    nPosX = 400;
    nPosY = 200;
    nWidht = 414;  
    nHeight = 477;

    OldX = 0;
    OldY = 0;

    Surf_Interface = NULL;
    eInterfaceType = INTERFACE_GAMEMENU;
}

CInterfaceB::CInterfaceB(InterfaceType eType)
{
    nPosX = 50;
    nPosY = 50;


    nWidht = 50;  
    nHeight = 50;

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
    if(CInterface::OnLoad() == false)
        return false;

    return true;
}

void CInterfaceB::OnCleanup()
{
    CInterfaceA::OnCleanup();

    for(int BagSlot = 0; BagSlot < BAG_MAX_SLOTS; ++BagSlot) 
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

    for(int BagSlot = 0; BagSlot < BAG_MAX_SLOTS; ++BagSlot) 
    {   
        for(int x = 0; x < BAG_MAX_X; ++x) 
        {   
            for(int y = 0; y < BAG_MAX_Y; ++y) 
            {   
                if(!ItemList[BagSlot][x][y]) continue;

                ItemList[BagSlot][x][y]->OnMoveWithInterface(nPosX-OldX,nPosY-OldY);
            }
        }
    }

    OldX = 0;
    OldY = 0;
}

void CInterfaceB::LoadButtons()
{
    ButtonType eType = BUTTON_DEFAULT;

    int x, y = 0;

    switch(eInterfaceType)
    {
        case INTERFACE_BAG:
		{
			for(int i=0; i<2; ++i)
			{
				switch(i)
				{
                    /*
                    load X
                    bagh swicher
                    */
					case 0: eType = BUTTON_BAG_QUIT; x = nPosX + nWidht - 30; y = nPosY; break;

                    default: break;
				}
					
                CButton *pButton = new CButton(x, y, eType);

				if(pButton->OnLoad(eType) == false)
                    break;

                ButtonsList.push_back(pButton);
				CButton::ButtonList.push_back(pButton);
			}

			break;
		}

        default: break;
    }
}