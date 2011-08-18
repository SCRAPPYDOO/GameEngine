#include "CUnit.h"
#include "CUnitMenager.h"
#include "CInterface.h"
#include "CInterfaceMenager.h"

CUnit::CUnit()
{
    Surf_Unit = NULL;

    fPosX = 50;
    fPosY = 50;
    nWidth = 50;
    nHeight = 50;

    fRadius = 0;  //radius of colision box
    fGoX = 0;   // destination point
    fGoY = 0;   
    fNewX = 0;  //position where we are going to
    fNewY = 0;  
    fSpeed = 0; 

    nUnitFlag = 0;
    nUnitMovementFlag = 0;

    CurrentFrameCol = 0;
    CurrentFrameRow = 0;
}

bool CUnit::OnLoad() 
{
    CObjectUnit::OnLoad();

    if((Surf_Unit = CSurface::OnLoad("./anim/1.png")) == NULL) 
    {
        //CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Unit Image Not Loaded");
        return false;
    }

    nUnitFlag = nUnitFlag | UNIT_FLAG_GOSSIP | UNIT_FLAG_LOOTABLE;

    //CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Unit Image Loaded");

    return true;
}

void CUnit::OnLoop() 
{
    CObjectUnit::OnLoop();
}

void CUnit::OnRender(SDL_Surface* Surf_Display) 
{
    CObjectUnit::OnRender(Surf_Display);
}

void CUnit::OnCleanup() 
{
    CObjectUnit::OnCleanup();
}

