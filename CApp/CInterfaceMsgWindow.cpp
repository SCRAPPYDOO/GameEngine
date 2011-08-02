#include "CInterfaceMsgWindow.h"

CInterfaceMsgWindow::CInterfaceMsgWindow()
{
    eInterfaceType = INTERFACE_MASAGEWINDOW;

    TextColor.b = 255;
    TextColor.g = 255;
    TextColor.r = 255;

    Surf_Interface = NULL;
    Font = NULL;

    OldX = 0;
    OldY = 0;

    for(int i = 0;i < INTERFACE_MSGWINDOW_MAX_TEXT_LINES;i++) 
    {   
        Masage[i] = "asd";
    }
}

bool CInterfaceMsgWindow::OnLoad()
{
    if(CInterface::OnLoad() == false)
        return false;

    Font = TTF_OpenFont( "./font/lazy.ttf", 15 );
    if(Font == NULL)
        return false;

    return true;
}

void CInterfaceMsgWindow::OnRender(SDL_Surface* Surf_Display)
{
    if(Surf_Interface == NULL || Surf_Display == NULL) return;

    CSurface::OnDraw(Surf_Display, Surf_Interface, nPosX, nPosY);

    for(int i = 0;i < INTERFACE_MSGWINDOW_MAX_TEXT_LINES;i++) 
    {  
        SDL_Surface* Msg = TTF_RenderText_Solid(Font, Masage[i], TextColor);

        if(Msg == NULL) break;

        CSurface::OnDraw(Surf_Display, Msg, nPosX, nPosY + i * 10); 

        SDL_FreeSurface( Msg );
    }  
}    

void CInterfaceMsgWindow::OnCleanup()
{
    TTF_CloseFont( Font );
    CInterface::OnCleanup();
}

void CInterfaceMsgWindow::AddMsg(char* msg)
{
    for(int i = 0;i < INTERFACE_MSGWINDOW_MAX_TEXT_LINES;i++) 
    {  
        Masage[i] = Masage[i+1]; 
    } 

    Masage[5] = msg;
}