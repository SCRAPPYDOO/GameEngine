#include "CButtonPanel.h"

CButtonPanel::CButtonPanel()
{
    nPosX               = 300;
    nPosY               = 600;
    nWidht              = 600;
    nHeight             = 60;

    Surf_Interface      = NULL;
    eInterfaceType      = INTERFACE_BUTTON_PANEL;
}

bool CButtonPanel::OnLoad()
{
    if(CInterface::OnLoad() == false)
        return false;

    return true;
}

void CButtonPanel::OnCleanup()
{
    CInterfaceA::OnCleanup();
}


