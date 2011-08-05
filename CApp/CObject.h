#ifndef _COBJECT_H_
    #define _COBJECT_H_

#include <vector>

#include "CSurface.h"
#include "CCamera.h"

class CObject
{
    public:
        static std::vector<CObject*>    ObjectList;

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