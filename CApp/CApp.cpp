#include "CApp.h"

CApp::CApp() 
{
    Surf_Display = NULL;			//Main Window

	eGameState   = MAIN_MENU;		//Interface Mod

    pSelectedUnit = NULL;
    pSelectedTarget = NULL;

    Running = true;					//Main Loop
}

int CApp::OnExecute() 
{
    if(OnInit() == false) 
	{
        return -1;
    }

    SDL_Event Event;

    while(Running) 
	{
        while(SDL_PollEvent(&Event)) 
		{
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}

int main(int argc, char* argv[])
{
    CApp theApp;

    return theApp.OnExecute();
}

