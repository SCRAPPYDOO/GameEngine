#ifndef _CENTITY_H_
    #define _CENTITY_H_

//#include <vector>
//
//#include "CArea.h"
//#include "CAnimation.h"
//#include "CCamera.h"
//#include "CFrameControler.h"
//#include "CSurface.h"
//
//enum EntityType
//{
//    ENTITY_TYPE_GENERIC = 0,
//
//    ENTITY_TYPE_PLAYER
//};
//
//enum EntityFlag
//{
//	ENTITY_FLAG_NONE    = 0x01,
//    ENTITY_FLAG_GRAVITY = 0x02,
//    ENTITY_FLAG_GHOST   = 0x04,
//    ENTITY_FLAG_MAPONLY = 0x08,
//};
//
//enum MovementFlag
//{
//    MOVEMENT_FLAG_NOTMOVE    = 0,
//    MOVEMENT_FLAG_RUN        = 1,
//    MOVEMENT_FLAG_WALK       = 4,
//    MOVEMENT_FLAG_SNEAK      = 8,
//};
//
//struct Surface
//{
//	SDL_Surface* Surf_Colision;
//};
//
//class CEntity 
//{
//    public:
//        static std::vector<CEntity*>    EntityList;
//
//    protected:
//        CAnimation      Anim_Control;
//
//        SDL_Surface*    Surf_Entity;
//
//    public:
//        float           X;
//        float           Y;
//
//        float           r;
//
//        float           nNewX;
//        float           nNewY;
//
//        float           goX;
//        float           goY;
//
//        float           nSpeed;
//
//        int             Width;
//        int             Height;
//
//        MovementFlag    eMovementFlag;
//
//    public:
//        int				Type;
//
//        bool			Dead;
//        int				Flags;
//
//    protected:
//        int             CurrentFrameCol;
//        int             CurrentFrameRow;
//
//    protected: //Colision System Parameters
//        int				Col_X;
//        int				Col_Y;
//        int				Col_Width;
//        int				Col_Height;
//
//    public:
//        CEntity();
//
//        virtual ~CEntity();
//
//    public:
//
//        virtual bool OnLoad(char* File, int Width, int Height, int MaxFrames);
//
//        virtual void OnLoop();
//
//        virtual void OnRender(SDL_Surface* Surf_Display);
//
//        virtual void OnCleanup();
//
//        virtual void OnAnimate();
//
//        virtual void OnCollision(CEntity* Entity);
//
//    public: //Movement                                
//        virtual void OnMoveToPoint();                                                   //trigered by MovementGenerator
//        virtual void OnMoveToPoint(int nGoPosX, int nGoPosY);                           //trigered by CApp->OnEvent->MouseRClick
//
//        virtual bool IsOnPoint(int goX, int goY);                                       //We check if we are near point
//        virtual void StopMove();
//
//        virtual int GetAnimPosX();
//        virtual int GetAnimPosY();
//
//    public:
//        bool    Collides(int oX, int oY, int oW, int oH);
//        bool    IsInColision();
//        double  GetDistance( float x1, float y1, float x2, float y2 );
//        bool    IsInRange(CEntity* pEntity);
//
//        char* GetName() const { return " "; }
//
//    private:
//        bool    PosValid(int NewX, int NewY);
//
//        bool    PosValidTile(CTile* Tile);
//
//        bool    PosValidEntity(CEntity* Entity, int NewX, int NewY); 
//
//        char* charName;
//        
//};
//
//class CEntityCol 
//{
//    public:
//        static std::vector<CEntityCol>  EntityColList;
//
//    public:
//        CEntity* EntityA;
//        CEntity* EntityB;
//
//    public:
//        CEntityCol();
//};

#endif