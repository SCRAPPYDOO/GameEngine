#include "CInterfaceCharSheet.h"

int TxtPosition[INTERFACE_CHARSHEET_MAX][2] =
{
    {8, 44}, //Character Name 
    {429, 169}, //Actual Health
    {66, 5},
    {22, 5},
    {77, 5},
    {33, 5},
    {88, 5},
    {44, 5},
    {99, 5},
    {55, 5},
};

CInterfaceCharSheet::CInterfaceCharSheet()
{
    eInterfaceType = INTERFACE_CHARACTERSHEET;
    //pChar = NULL;

    for(int i = 0;i < INTERFACE_CHARSHEET_MAX;i++) 
    {
        TextSurface[i] = NULL; 
    }
}

bool CInterfaceCharSheet::OnLoad()
{
    if(CInterface::OnLoad() == false)
        return false;

    //Set Up a  Character
    UpdateInterface();

    return true;
}

void CInterfaceCharSheet::OnLoop()
{
    CInterface::OnLoop();
    
    UpdateInterface();
}

void CInterfaceCharSheet::OnRender(SDL_Surface* Surf_Display)
{
    CInterface::OnRender(Surf_Display);

    for(int i = 0;i < INTERFACE_CHARSHEET_MAX;i++) 
    {
        if(!TextSurface[i]) continue;

        CSurface::OnDraw(Surf_Display, TextSurface[i], nPosX + TxtPosition[i][0], nPosY + TxtPosition[i][1]);
    }
}    

void CInterfaceCharSheet::OnCleanup()
{
    CInterface::OnCleanup();
    CleanUpSurface();
}

void CInterfaceCharSheet::CleanUpSurface()
{
    for(int i=0; i<INTERFACE_CHARSHEET_MAX; ++i)
    {
        if(TextSurface[i]) 
		    SDL_FreeSurface(TextSurface[i]);

	    TextSurface[i] = NULL;
    }  
}


void CInterfaceCharSheet::UpdateInterface()
{
	CleanUpSurface();

	if(CPlayer::Player.pPlayerCharacter == NULL)
		return;

    for(int i=0; i<INTERFACE_CHARSHEET_MAX; ++i)
    { 
        std::string strText = "";
        int nValue = 0;

		int Type = 0;

        switch(i)
        {
			//string types
            case 0: strText = CPlayer::Player.pPlayerCharacter->GetName(); Type = 1; break;

			//int types
            case 1: nValue = CPlayer::Player.pPlayerCharacter->GetActualHealth(); Type = 2; break;
            default: break;
        }

		switch(Type)
		{
            case 1: TextSurface[i] = CSurface::RenderText(strText); break;
            case 2: TextSurface[i] = CSurface::RenderText(nValue); break;
			default: break;
		}   
    }  
}

