#include "CUnit.h"
#include "CUnitMenager.h"
#include "CInterface.h"
#include "CInterfaceMenager.h"

enum Direction
{
    UpRight,
    UpLeft,
    DownRight,
    DownLeft,
};

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

    UnitIsAlive = true;
}

bool CUnit::OnLoad() 
{
    if((Surf_Unit = CSurface::OnLoad("./anim/1.png")) == NULL) 
    {
        //CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Unit Image Not Loaded");
        return false;
    }

    nUnitFlag = nUnitFlag | UNIT_FLAG_GOSSIP;

    //CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Unit Image Loaded");

    return true;
}

void CUnit::OnLoop() 
{
    OnAnimate();
}

void CUnit::OnRender(SDL_Surface* Surf_Display) 
{
    if(Surf_Unit == NULL || Surf_Display == NULL) return;

    int nCurrentFrameX = CurrentFrameCol * nWidth;
    int nCurrentFrameY = (CurrentFrameRow + Anim_Control.GetCurrentFrame()) * nHeight;

    CSurface::OnDraw(Surf_Display, Surf_Unit, GetAnimPosX(), GetAnimPosY(), nCurrentFrameX, nCurrentFrameY, nWidth, nHeight);
    //CSurface::OnDraw(Surf_Display, Surf_Unit, fPosX, fPosY);
}

void CUnit::OnCleanup() 
{
    if(Surf_Unit) 
    {
        SDL_FreeSurface(Surf_Unit);
    }

    Surf_Unit = NULL;
}

void CUnit::OnAnimate() 
{
    Anim_Control.OnAnimate();
}

void CUnit::OnMoveToPoint(int nGoPosX, int nGoPosY)
{
    //nUnitMovementFlag = UNIT_MOVEMENT_FLAG_WALK;
    fGoX = static_cast<float>(nGoPosX);
    fGoY = static_cast<float>(nGoPosY);
}

void CUnit::OnMoveToPoint()
{
    //if(nUnitMovementFlag ^ UNIT_MOVEMENT_FLAG_NOTMOVE)
    //    return;

    if(IsOnPoint(fGoX,fGoY))
    {
        StopMove(); 
        return;
    }

    float vectorX, vectorY;
    vectorX = vectorY = 0;

    Direction eDirect = UpRight;

    if(fPosX < fGoX && fPosY < fGoY)
        eDirect = DownRight;
    if(fPosX > fGoX && fPosY < fGoY)
        eDirect = DownLeft;
    if(fPosX < fGoX && fPosY > fGoY)
        eDirect = UpRight;
    if(fPosX > fGoX && fPosY > fGoY)
        eDirect = UpLeft;

    switch(eDirect)
    {
        case UpRight:   vectorX = 1.0f;     vectorY = -1.0f;    CurrentFrameCol = 1; break;
        case DownRight: vectorX = 1.0f;     vectorY = 1.0f;     CurrentFrameCol = 1; break;
        case DownLeft:  vectorX = -1.0f;    vectorY = 1.0f;     CurrentFrameCol = 0; break;
        case UpLeft:    vectorX = -1.0f;    vectorY = -1.0f;    CurrentFrameCol = 0; break;
    }

    fNewX = fPosX; 
    fNewY = fPosY;

    if(fPosX != fGoX)
        fNewX = fPosX + fSpeed*vectorX;

    if(fPosY != fGoY)
        fNewY = fPosY + fSpeed*vectorY; 


    if(!IsInColision())
    {
        fPosX = fNewX; 
        fPosY = fNewY;
    }
    else
    {
        StopMove(); 
        return;
    }
}

double CUnit::GetDistance(float x1, float y1, float x2, float y2 )
{ 
    return sqrt(pow( x2 - x1, 2) + pow( y2 - y1, 2));
}

bool CUnit::IsInRange(CUnit* pUnit)
{
    if(GetDistance(fPosX, fPosY, pUnit->fPosX,  pUnit->fPosY ) < fRadius + pUnit->fRadius)
        return true;

    return false;
}

bool CUnit::IsInColision()
{
    for(int i = 0;i < CUnitMenager::UnitList.size();i++) 
    {
        if(!CUnitMenager::UnitList[i]) continue;

        if(CUnitMenager::UnitList[i] == this) continue;

        if( GetDistance(fNewX, fNewY, CUnitMenager::UnitList[i]->fPosX, CUnitMenager::UnitList[i]->fPosY) <  fRadius + CUnitMenager::UnitList[i]->fRadius)
            return true;
    }

    //ToDo: With Other Objects

    return false;
}

bool CUnit::IsOnPoint(int goX, int goY)
{
    if(GetDistance(fPosX, fPosY, goX, goY) < 1)
        return true;

    return false;
}

void CUnit::StopMove() 
{
    //eMovementFlag = MOVEMENT_FLAG_NOTMOVE;
}

int CUnit::GetAnimPosX()
{
    int Return = fPosX - (static_cast<int>(0.5 * nWidth)) - CCamera::CameraControl.GetX();

    return Return;
}

int CUnit::GetAnimPosY()
{
    int Return = fPosY - nHeight - CCamera::CameraControl.GetY();

    return Return;
}

//bool CUnit::Collides(int oX, int oY, int oW, int oH) 
//{
//    int left1, left2;
//    int right1, right2;
//    int top1, top2;
//    int bottom1, bottom2;
//
//    int tX = (int)fPosX + Col_X;
//    int tY = (int)fPosY + Col_Y;
//
//    left1 = tX;
//    left2 = oX;
//
//    right1 = left1 + Width - 1 - Col_Width;
//    right2 = oX + oW - 1;
//
//    top1 = tY;
//    top2 = oY;
//
//    bottom1 = top1 + Height - 1 - Col_Height;
//    bottom2 = oY + oH - 1;
//
//    if (bottom1 < top2) return false;
//    if (top1 > bottom2) return false;
//
//    if (right1 < left2) return false;
//    if (left1 > right2) return false;
//
//    return true;
//}
//
//bool CEntity::PosValid(int NewX, int NewY) 
//{
//    bool Return = true;
//
//    int StartX  = (NewX + Col_X) / TILE_SIZE;
//    int StartY  = (NewY + Col_Y) / TILE_SIZE;
//
//    int EndX    = ((NewX + Col_X) + Width - Col_Width - 1)      / TILE_SIZE;
//    int EndY    = ((NewY + Col_Y) + Height - Col_Height - 1)    / TILE_SIZE;
//
//    for(int iY = StartY;iY <= EndY;iY++) 
//    {
//        for(int iX = StartX;iX <= EndX;iX++) 
//        {
//            CTile* Tile = CArea::AreaControl.GetTile(iX * TILE_SIZE, iY * TILE_SIZE);
//
//            if(PosValidTile(Tile) == false) 
//            {
//                Return = false;
//            }
//        }
//    }
//
//    if(Flags & ENTITY_FLAG_MAPONLY) 
//    {
//    }
//    else
//    {
//        for(int i = 0;i < EntityList.size();i++) 
//        {
//            if(PosValidEntity(EntityList[i], NewX, NewY) == false) 
//            {
//                Return = false;
//            }
//        }
//    }
//
//    return Return;
//}
//
//bool CEntity::PosValidTile(CTile* Tile) 
//{
//    if(Tile == NULL) 
//    {
//        return true;
//    }
//
//    if(Tile->TypeID == TILE_TYPE_BLOCK) 
//    {
//        return false;
//    }
//
//    return true;
//}
//
//bool CEntity::PosValidEntity(CEntity* Entity, int NewX, int NewY)
//{
//    if(this != Entity && Entity != NULL && Entity->Dead == false && Entity->Flags ^ ENTITY_FLAG_MAPONLY && Entity->Collides(NewX + Col_X, NewY + Col_Y, Width - Col_Width - 1, Height - Col_Height - 1) == true) 
//    {
//        CEntityCol EntityCol;
//
//        EntityCol.EntityA = this;
//        EntityCol.EntityB = Entity;
//
//        CEntityCol::EntityColList.push_back(EntityCol);
//
//        return false;
//    }
//
//    return true;
//}
//
