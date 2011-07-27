#include "CInterfaceLoot.h"
#include <string>
#include <fstream>

CInterfaceLoot::CInterfaceLoot()
{
    nPosX = 400;
    nPosY = 200;
    nWidht = INTERFACE_LOOT_W_H;
    nHeight = INTERFACE_LOOT_W_H;

    OldX = 0;
    OldY = 0;

    Surf_Interface = NULL;

    eInterfaceType = INTERFACE_LOOT;

    for(int x = 0; x < 4; ++x)
    {
        for(int y = 0; y < 4; ++y)
        {
            ItemList[x][y] = NULL;
        }
    }
}

bool CInterfaceLoot::OnLoad()
{
    if(CInterface::OnLoad() == false)
        return false;

    //load loot from cfg

    return true;
}

void CInterfaceLoot::OnCleanup()
{
    CInterfaceA::OnCleanup();

    for(int x = 0; x <4; ++x)
    {
        for(int y = 0; y < 4; ++y)
        {
            if(!ItemList[x][y]) continue;

            ItemList[x][y]->OnCleanup();
            ItemList[x][y] = NULL;
        }
    }
}

void CInterfaceLoot::UpdateButtonsPosition()
{
    if(OldX == 0 && OldY == 0)
        return;

    for(int i = 0;i < ButtonsList.size();i++)
    {
        if(!ButtonsList[i]) continue;
                
        ButtonsList[i]->OnMoveWithInterface(nPosX-OldX,nPosY-OldY);
    }

    for(int x = 0; x < 4; ++x)
    {
        for(int y = 0; y < 4; ++y)
        {
            if(!ItemList[x][y]) continue;

            ItemList[x][y]->OnMoveWithInterface(nPosX-OldX,nPosY-OldY);
        }
    }

    OldX = 0;
    OldY = 0;
}

void CInterfaceLoot::LoadButtons()
{
    ButtonType eType = BUTTON_DEFAULT;

    int x = 0;
int y = 0;

    for(int i=0; i<2; ++i)
    {
        switch(i)
        {
            case 0: eType = BUTTON_LOOT_QUIT; x = nPosX + INTERFACE_LOOT_W_H - 30; y = nPosY; break;
            case 1: eType = BUTTON_LOOT_LOOTALL; x = nPosX; y = nPosY + INTERFACE_LOOT_W_H - 30; break;

            default: break;
        }

        CButton *pButton = new CButton(x, y, eType);

        if(pButton->OnLoad() == false)
            break;

        ButtonsList.push_back(pButton);
    }
}