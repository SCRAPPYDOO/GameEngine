#include "CFrameControler.h"

CFrameControler  CFrameControler::FrameControler;

CFrameControler::CFrameControler () 
{
    OldTime     = 0;
    LastTime    = 0;

    SpeedFactor = 0;

    Frames      = 0;
    NumFrames   = 0;
}

void CFrameControler::OnLoop() 
{
    if(OldTime + 1000 < SDL_GetTicks())
	{
        OldTime = SDL_GetTicks();

        NumFrames = Frames;

        Frames = 0;
    }

	int Ticks = SDL_GetTicks() - LastTime;
    SpeedFactor = (Ticks / 1000.0f) * 32.0f;

    LastTime = SDL_GetTicks();

    Frames++;
}

int CFrameControler::GetFPS() 
{
    return NumFrames;
}

float CFrameControler::GetSpeedFactor()
{
    return SpeedFactor;
}