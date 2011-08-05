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

    for(int i=0; i<INTERFACE_MSGWINDOW_MAX_TEXT_LINES; ++i)
    {
        if(Masage[i]) 
		    SDL_FreeSurface(Masage[i]);

	    Masage[i] = NULL;
    } 
}

void CInterfaceMsgWindow::AddMsg(char* msg)
{
    for(int i = 0;i < INTERFACE_MSGWINDOW_MAX_TEXT_LINES;i++) 
    {  
        if(i == (INTERFACE_MSGWINDOW_MAX_TEXT_LINES - 1))
        {
            Masage[i] = RenderText(msg);
            return;
        }

        Masage[i] = Masage[i+1]; 
    } 
}