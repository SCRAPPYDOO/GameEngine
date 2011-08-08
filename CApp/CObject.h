#ifndef _COBJECT_H_
    #define _COBJECT_H_

#include <vector>

#include "CSurface.h"
#include "CCamera.h"

enum ObjectFlag
{
    OBJECT_FLAG_NULL            = 0x0001,
    OBJECT_FLAG_OPENED          = 0x0002,
    OBJECT_FLAG_CLOSED          = 0x0004,

};

enum ObjectType
{
    OBJECT_TYPE_NULL            = 0,
    OBJECT_TYPE_DOOR            = 1,
    OBJECT_TYPE_CHEST           = 2,
};

class CObject
{
    protected:
        SDL_Surface*    Surf_Object;

    public:
        int             X;
        int             Y;

        int             Width;
        int             Height;

    protected:
        int				ColBox_X;
        int				ColBox_Y;
        int				ColBox_W;
        int				ColBox_H;

    public:
        CObject();

        virtual ~CObject();

    public:
        virtual bool OnLoad(char* File);

        virtual void OnRender(SDL_Surface* Surf_Display);

        virtual void OnCleanup();
};

#endif