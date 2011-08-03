#include "CInterfaceCharSheet.h"

CInterfaceCharSheet::CInterfaceCharSheet()
{
    eInterfaceType = INTERFACE_CHARACTERSHEET;
}

bool CInterfaceCharSheet::OnLoad()
{
    if(CInterface::OnLoad() == false)
        return false;

    return true;
}

void CInterfaceCharSheet::OnRender(SDL_Surface* Surf_Display)
{
    if(Surf_Interface == NULL || Surf_Display == NULL) return;

    CSurface::OnDraw(Surf_Display, Surf_Interface, nPosX, nPosY);
}    

void CInterfaceCharSheet::OnCleanup()
{
    CInterface::OnCleanup();
}