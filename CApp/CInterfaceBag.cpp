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

bool CInterfaceBag::OnLoad()
{
    if(CInterface::OnLoad() == false)
        return false;

    LoadBag(ActualBag);

    return true;
}

void CInterfaceBag::OnRender(SDL_Surface* Surf_Display)
{
    CInterfaceA::OnRender(Surf_Display);

    for(int x = 0; x < BAG_MAX_X; ++x) 
    {   
        for(int y = 0; y < BAG_MAX_Y; ++y) 
        {   
            if(!ItemList[ActualBag][x][y]) continue;

            ItemList[ActualBag][x][y]->OnRender(Surf_Display);
        }
    }
}

void CInterfaceBag::OnCleanup()
{
    SaveBag(ActualBag);
    CleanUpBag(ActualBag);

    CInterfaceA::OnCleanup();
}

void CInterfaceBag::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    CInterfaceA::OnMouseMove(mX, mY, relX, relY, Left, Right, Middle);

    for(int x = 0; x < BAG_MAX_X; ++x) 
    {   
        for(int y = 0; y < BAG_MAX_Y; ++y) 
        {   
            if(!ItemList[ActualBag][x][y]) continue;

            ItemList[ActualBag][x][y]->OnMouseMove(mX, mY, relX, relY, Left, Right, Middle);
        }
    }
}

void CInterfaceBag::UpdateButtonsPosition()
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

void CInterfaceBag::LoadButtons()
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
			}

			break;
		}

        default: break;
    }
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

            ItemList[ActualBag][x][y] = pButton;
        }
    }



  //  Open a file for reading 
  //  std::ifstream load( "./save/bag1_save" );

  //  If the file loaded 
  //  if( load != NULL ) 
  //  { 
  //      The offset 
  //      int offset; 

  //      load >> offset; 

  //      ButtonType eType = static_cast<ButtonType>(offset);

  //      CButton *pButton = new CButton(nPosX + 50, nPosY + 100, eType);

		//if(pButton->OnLoad() == false)
  //          return;

  //      ButtonsList.push_back(pButton);
		//CButton::ButtonList.push_back(pButton);

  //      Close the file 
  //      load.close(); 
  //  }

}



