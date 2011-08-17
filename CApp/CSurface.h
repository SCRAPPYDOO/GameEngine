#ifndef _CSURFACE_H_
    #define _CSURFACE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <sstream>

class CSurface 
{
	public:
		CSurface();

	public:
        static TTF_Font *Font;
        static SDL_Color TextColor;

		static SDL_Surface* OnLoad(char* File);

		static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);
		static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H);

		static bool Transparent(SDL_Surface* Surf_Dest, int R, int G, int B);

        static SDL_Surface* RenderText(std::string strText);
        static SDL_Surface* RenderText(int nValue);
        static SDL_Surface* RenderText(char* cText);
        static SDL_Surface* RenderText(char cText);
};

#endif
