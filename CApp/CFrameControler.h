#ifndef _CFRAMECONTROLER_H_
    #define _CFRAMECONTROLER_H_

#include <SDL.h>

class CFrameControler 
{
    public:
        static CFrameControler FrameControler;

    private:
        int     OldTime;
        int     LastTime;

        float   SpeedFactor;

        int		NumFrames;
        int     Frames;

    public:
        CFrameControler();

        void    OnLoop();

    public:
        int     GetFPS();

        float   GetSpeedFactor();
};

#endif