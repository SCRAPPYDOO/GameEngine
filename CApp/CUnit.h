#ifndef _CUNIT_H_
    #define _CUNIT_H_

#include "CArea.h"
#include "CAnimation.h"
#include "CCamera.h"
#include "CFrameControler.h"
#include "CSurface.h"

enum UnitType
{
    ENTITY_TYPE_GENERIC = 0,
    ENTITY_TYPE_PLAYER
};

enum UnitFlag
{
	ENTITY_FLAG_NONE    = 0x01,
    ENTITY_FLAG_GRAVITY = 0x02,
    ENTITY_FLAG_GHOST   = 0x04,
    ENTITY_FLAG_MAPONLY = 0x08,

    UNIT_FLAG_GOSSIP    = 0x10,
    UNIT_FLAG_VENDOR    = 0x20,
    UNIT_FLAG_LOOTABLE  = 0x40,
};

enum UnitMovementFlag
{
    UNIT_MOVEMENT_FLAG_NOTMOVE    = 0,
    UNIT_MOVEMENT_FLAG_RUN        = 1,
    UNIT_MOVEMENT_FLAG_WALK       = 4,
    UNIT_MOVEMENT_FLAG_SNEAK      = 8,
};

class CUnit
{
    public:
        CUnit();
        ~CUnit() {}

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

        int             nUnitFlag;
        int             nUnitMovementFlag;

        int             CurrentFrameCol;
        int             CurrentFrameRow;

    public:
        float GetPosX() const { return fPosX; }
        float GetPosY() const { return fPosY; }
        int GetWidht() const { return nWidth; }
        int GetHeight() const { return nHeight; }
          
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

        bool HasFlag(UnitFlag Flag) const
        {
            if(nUnitFlag & Flag)
                return true;
            return false;
        }

        //Character Methods
        virtual std::string GetName() { return " "; }
        virtual int GetActualHealth() const { return NULL; }
        virtual int GetMaxHealth() const { return NULL; }

        virtual void SetHealth(int nValue) { }

        virtual bool IsAlive() const { return true; }

};

#endif