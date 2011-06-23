#include "CApp.h"

CApp::CApp() 
{
    Surf_Display = NULL;

    pSelectedUnit = NULL;
    pSelectedTarget = NULL;

    Running = true;
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

        OnKeyState(); //Handle Key States -> camera movement 
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

