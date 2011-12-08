#ifndef _COBJECTUNIT_H_
    #define _COBJECTUNIT_H_

#include "CArea.h"
#include "CAnimation.h"
#include "CCamera.h"
#include "CFrameControler.h"
#include "CSurface.h"

enum UnitMovementFlag
{
    UNIT_MOVEMENT_FLAG_NOTMOVE    = 0,
    UNIT_MOVEMENT_FLAG_RUN        = 1,
    UNIT_MOVEMENT_FLAG_WALK       = 4,
    UNIT_MOVEMENT_FLAG_SNEAK      = 8,
};

class CUnit;

class CObjectUnit
{
    public:
        CObjectUnit();
        ~CObjectUnit() {}

    public:
        virtual bool OnLoad();
        virtual void OnLoop();
        virtual void OnRender(SDL_Surface* Surf_Display);
        virtual void OnCleanup();

        virtual void OnAnimate();
        /*virtual void OnCollision(CUnit* pUnit);*/

    protected:
        CAnimation      Anim_Control;
        SDL_Surface*    Surf_Unit;

    protected: //Movement Information
        float           fPosX;
        float           fPosY;
        int             nWidth;
        int             nHeight;

        float           fRadius;  //radius of colision box
        float           fGoX;   // destination point
        float           fGoY;   
        float           fNewX;  //position where we are going to
        float           fNewY;  
        float           fSpeed; 

        int             nUnitMovementFlag;

        int             CurrentFrameCol;
        int             CurrentFrameRow;

    public:
        float GetPosX() const { return fPosX; }
        float GetPosY() const { return fPosY; }
        int GetWidht() const { return nWidth; }
        int GetHeight() const { return nHeight; }
		void SetNewPosition(float x, float y) { fPosX = x; fPosY = y; }
          
    public: //Movement Methods                                 
        virtual void OnMoveToPoint();                                                   //trigered by MovementGenerator
        virtual void OnMoveToPoint(int nGoPosX, int nGoPosY);                           //trigered by CApp->OnEvent->MouseRClick

        virtual bool IsOnPoint(int goX, int goY);                                       //We check if we are near point
        virtual void StopMove();

        virtual int GetAnimPosX();
        virtual int GetAnimPosY();

        bool    Collides(int oX, int oY, int oW, int oH);
        bool    IsInColision();
        double  GetDistance( float x1, float y1, float x2, float y2 );
        bool    IsInRange(CUnit* pUnit);

        bool    PosValid(int NewX, int NewY);
        bool    PosValidTile(CTile* pTile);
        bool    PosValidEntity(CUnit* pUnit, int NewX, int NewY); 
};

#endif