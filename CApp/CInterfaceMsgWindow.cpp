#include "CInterfaceMsgWindow.h"

CInterfaceMsgWindow::CInterfaceMsgWindow()
{
    eInterfaceType = INTERFACE_MASAGEWINDOW;

    for(int i = 0;i < INTERFACE_MSGWINDOW_MAX_TEXT_LINES;i++) 
    {   
        Masage[i] = NULL;
    }
}

bool CInterfaceMsgWindow::OnLoad()
{
    if(CInterface::OnLoad() == false)
        return false;

    return true;
}

void CInterfaceMsgWindow::OnLoop()
{
    CInterface::OnLoop();
    CleanUpMassageSurf();
    RenderMassage();
}

void CInterfaceMsgWindow::OnRender(SDL_Surface* Surf_Display)
{
    CInterface::OnRender(Surf_Display);

    for(int i = 0;i < INTERFACE_MSGWINDOW_MAX_TEXT_LINES;i++) 
    {  
        if(!Masage[i]) continue;

        CSurface::OnDraw(Surf_Display, Masage[i], nPosX, nPosY + i * 10 + 40); 
    }   
}    

void CInterfaceMsgWindow::OnCleanup()
{
    CInterface::OnCleanup();
    CleanUpMassageSurf();
}

void CInterfaceMsgWindow::CleanUpMassageSurf()
{
    for(int i=0; i<INTERFACE_MSGWINDOW_MAX_TEXT_LINES; ++i)
    {
        if(Masage[i]) 
		    SDL_FreeSurface(Masage[i]);

	    Masage[i] = NULL;
    } 
}

void CInterfaceMsgWindow::AddMsg(char* msg)
{
    for(int i = 0;i < INTERFACE_MSGWINDOW_MAX_TEXT_LINES;++i) 
    {  
        if(i == (INTERFACE_MSGWINDOW_MAX_TEXT_LINES - 1))
        {
            std::stringstream s;
            s << msg;

            MasageList[i] = s.str();
            return;
        }

        MasageList[i] = MasageList[i+1]; 
    } 
}

void CInterfaceMsgWindow::RenderMassage()
{
    for(int i = 0;i < INTERFACE_MSGWINDOW_MAX_TEXT_LINES;++i) 
    {  
        Masage[i] = CSurface::RenderText(MasageList[i]);
    } 
}