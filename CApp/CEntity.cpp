#include "CEntity.h"

std::vector<CEntity*> CEntity::EntityList;
std::vector<CEntityCol> CEntityCol::EntityColList;

CEntityCol::CEntityCol() 
{
    EntityA = NULL;
    EntityB = NULL;
}

CEntity::CEntity() 
{
    Surf_Entity = NULL;
	//Surf_Colision = NULL;

    //Movement Variables
    X = rand()%500;
    Y = 500;

    r = 0;

    goX = 450;
    goY = 450;

    nNewX = 0; 
    nNewY = Y;

    nSpeed = 0.09f;

    eMovementFlag = MOVEMENT_FLAG_NOTMOVE;

    Width   = 0;
    Height  = 0;

    //Others
    Type =  ENTITY_TYPE_PLAYER;

    Dead = false;
    Flags = ENTITY_FLAG_GRAVITY;

    CurrentFrameCol = 0;
    CurrentFrameRow = 0;

    //Colision System Variables
    Col_X = 0;
    Col_Y = 0;
    Col_Width  = 0;
    Col_Height = 0;
}

CEntity::~CEntity() {}

bool CEntity::OnLoad(char* File, int Width, int Height, int MaxFrames) 
{
	if((Surf_Entity = CSurface::OnLoad(File)) == NULL) 
    {
		return false;
	}
	
	/*
	if((Surf_Colision = CSurface::OnLoad("colisioncircle.png")) == NULL) 
    {
		return false;
	}
	*/

	CSurface::Transparent(Surf_Entity, 255, 0, 255);

	this->Width = Width;
	this->Height = Height;

	r = 0.5 * Width;

	Anim_Control.MaxFrames = MaxFrames;

    return true;
}

void CEntity::OnLoop() 
{
    OnAnimate();
}

void CEntity::OnAnimate() 
{
    if(eMovementFlag == MOVEMENT_FLAG_NOTMOVE)
        return;

    Anim_Control.OnAnimate();
}

void CEntity::OnRender(SDL_Surface* Surf_Display) 
{
    if(Surf_Entity == NULL || Surf_Display == NULL) return;

    CSurface::OnDraw(Surf_Display, Surf_Entity, GetAnimPosX(), GetAnimPosY(), CurrentFrameCol * Width, (CurrentFrameRow + Anim_Control.GetCurrentFrame()) * Height, Width, Height);
}

void CEntity::OnCollision(CEntity* Entity) {}

enum Direction
{
    UpRight,
    UpLeft,
    DownRight,
    DownLeft,
};

void CEntity::OnMoveToPoint(int nGoPosX, int nGoPosY)
{
    eMovementFlag = MOVEMENT_FLAG_WALK;
    goX = static_cast<float>(nGoPosX);
    goY = static_cast<float>(nGoPosY);
}

void CEntity::OnMoveToPoint()
{
    if(eMovementFlag == MOVEMENT_FLAG_NOTMOVE)
        return;

    if(IsOnPoint(goX,goY))
    {
        this->StopMove(); 
        return;
    }

    //float A = (Y-goY) / (X-goX);  
    //float B = Y - X; 

    float vectorX, vectorY;

    Direction eDirect = UpRight;

    if(X < goX && Y < goY)
        eDirect = DownRight;
    if(X > goX && Y < goY)
        eDirect = DownLeft;
    if(X < goX && Y > goY)
        eDirect = UpRight;
    if(X > goX && Y > goY)
        eDirect = UpLeft;

    switch(eDirect)
    {
        case UpRight:   vectorX = 1.0f;     vectorY = -1.0f;    CurrentFrameCol = 1; break;
        case DownRight: vectorX = 1.0f;     vectorY = 1.0f;     CurrentFrameCol = 1; break;
        case DownLeft:  vectorX = -1.0f;    vectorY = 1.0f;     CurrentFrameCol = 0; break;
        case UpLeft:    vectorX = -1.0f;    vectorY = -1.0f;    CurrentFrameCol = 0; break;
    }

    nNewX = X; 
    nNewY = Y;

    if(X != goX)
        nNewX = X + nSpeed*vectorX;

    if(Y != goY)
        nNewY = Y + nSpeed*vectorY; 


    if(!IsInColision())
    {
        X = nNewX; 
        Y = nNewY;
    }
    else
    {
        this->StopMove(); 
        return;
    }
}

double CEntity::GetDistance(float x1, float y1, float x2, float y2 )
{ 
    return sqrt(pow( x2 - x1, 2) + pow( y2 - y1, 2));
}

bool CEntity::IsInRange(CEntity* pEntity)
{
    if(GetDistance(this->X, this->Y, pEntity->X,  pEntity->Y ) < this->r + pEntity->r)
        return true;

    return false;
}

bool CEntity::IsInColision()
{
    for(int i = 0;i < EntityList.size();i++) 
    {
        if(EntityList[i] == this)
            continue;

        if( GetDistance(nNewX,nNewY,EntityList[i]->X,EntityList[i]->Y) <  this->r + EntityList[i]->r)
            return true;
    }

    //ToDo: With Other Objects

    return false;
}

bool CEntity::IsOnPoint(int goX, int goY)
{
    int nA = X - goX;
    int nB = Y - goY;

    if(nA < 0)
        nA *= -1;
    if(nB < 0)
        nB *= -1;

    if( nA< 5 && nB < 5)
        return true;

    return false;
}

void CEntity::StopMove() 
{
    eMovementFlag = MOVEMENT_FLAG_NOTMOVE;
}

int CEntity::GetAnimPosX()
{
    int Return = X - (static_cast<int>(0.5 * Width)) - CCamera::CameraControl.GetX();

    return Return;
}

int CEntity::GetAnimPosY()
{
    int Return = Y - Height - CCamera::CameraControl.GetY();

    return Return;
}

bool CEntity::Collides(int oX, int oY, int oW, int oH) 
{
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

    int tX = (int)X + Col_X;
    int tY = (int)Y + Col_Y;

    left1 = tX;
    left2 = oX;

    right1 = left1 + Width - 1 - Col_Width;
    right2 = oX + oW - 1;

    top1 = tY;
    top2 = oY;

    bottom1 = top1 + Height - 1 - Col_Height;
    bottom2 = oY + oH - 1;

    if (bottom1 < top2) return false;
    if (top1 > bottom2) return false;

    if (right1 < left2) return false;
    if (left1 > right2) return false;

    return true;
}

bool CEntity::PosValid(int NewX, int NewY) 
{
    bool Return = true;

    int StartX  = (NewX + Col_X) / TILE_SIZE;
    int StartY  = (NewY + Col_Y) / TILE_SIZE;

    int EndX    = ((NewX + Col_X) + Width - Col_Width - 1)      / TILE_SIZE;
    int EndY    = ((NewY + Col_Y) + Height - Col_Height - 1)    / TILE_SIZE;

    for(int iY = StartY;iY <= EndY;iY++) 
    {
        for(int iX = StartX;iX <= EndX;iX++) 
        {
            CTile* Tile = CArea::AreaControl.GetTile(iX * TILE_SIZE, iY * TILE_SIZE);

            if(PosValidTile(Tile) == false) 
            {
                Return = false;
            }
        }
    }

    if(Flags & ENTITY_FLAG_MAPONLY) 
    {
    }
    else
    {
        for(int i = 0;i < EntityList.size();i++) 
        {
            if(PosValidEntity(EntityList[i], NewX, NewY) == false) 
            {
                Return = false;
            }
        }
    }

    return Return;
}

bool CEntity::PosValidTile(CTile* Tile) 
{
    if(Tile == NULL) 
    {
        return true;
    }

    if(Tile->TypeID == TILE_TYPE_BLOCK) 
    {
        return false;
    }

    return true;
}

bool CEntity::PosValidEntity(CEntity* Entity, int NewX, int NewY)
{
    if(this != Entity && Entity != NULL && Entity->Dead == false && Entity->Flags ^ ENTITY_FLAG_MAPONLY && Entity->Collides(NewX + Col_X, NewY + Col_Y, Width - Col_Width - 1, Height - Col_Height - 1) == true) 
    {
        CEntityCol EntityCol;

        EntityCol.EntityA = this;
        EntityCol.EntityB = Entity;

        CEntityCol::EntityColList.push_back(EntityCol);

        return false;
    }

    return true;
}

void CEntity::OnCleanup() 
{
    if(Surf_Entity) 
    {
        SDL_FreeSurface(Surf_Entity);
    }

	/*
	if(Surf_Colision) 
    {
        SDL_FreeSurface(Surf_Colision);
    }
	*/

	//Surf_Colision = NULL;
    Surf_Entity = NULL;
}
