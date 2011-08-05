#include "CCharacter.h"

bool CCharacter::OnLoad(char* File, int Width, int Height, int MaxFrames) 
{
    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) 
    {
        return false;
    }

    return true;
}

void CCharacter::OnLoop() 
{
    CEntity::OnLoop();
}

void CCharacter::OnRender(SDL_Surface* Surf_Display) 
{
    CEntity::OnRender(Surf_Display);
}

void CCharacter::OnCleanup() 
{
    CEntity::OnCleanup();
}
