#include "CSurface.h"

TTF_Font* CSurface::Font = NULL;
SDL_Color CSurface::TextColor = { 255, 50, 50 };

CSurface::CSurface() 
{

}

SDL_Surface* CSurface::OnLoad(char* File) 
{
	SDL_Surface* Surf_Temp = NULL;
	SDL_Surface* Surf_Return = NULL;

	if((Surf_Temp = IMG_Load(File)) == NULL) 
    {
		return NULL;
	}

	Surf_Return = SDL_DisplayFormatAlpha(Surf_Temp);
	SDL_FreeSurface(Surf_Temp);

	return Surf_Return;
}

bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y)
{
	if(Surf_Dest == NULL || Surf_Src == NULL) 
    {
		return false;
	}

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;

	SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

	return true;
}

bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H) 
{
	if(Surf_Dest == NULL || Surf_Src == NULL) 
    {
		return false;
	}

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;

	SDL_Rect SrcR;

	SrcR.x = X2;
	SrcR.y = Y2;
	SrcR.w = W;
	SrcR.h = H;

	SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);

	return true;
}

bool CSurface::Transparent(SDL_Surface* Surf_Dest, int R, int G, int B) 
{
	if(Surf_Dest == NULL)
    {
		return false;
	}

	SDL_SetColorKey(Surf_Dest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(Surf_Dest->format, R, G, B));

	return true;
}

SDL_Surface* CSurface::RenderText(std::string strText)
{
    SDL_Surface* pSurface = NULL;

    pSurface = TTF_RenderText_Solid(CSurface::Font, strText.c_str(), CSurface::TextColor);
    
    if(!pSurface) return NULL;

    return pSurface;
}

template<typename Typ>
std::string ConvertToString(Typ T)
{
    std::stringstream s;
    s << T;
    return s.str();
}

SDL_Surface* CSurface::RenderText(int nValue)
{
    std::string strText = ConvertToString(nValue);
    return RenderText(strText);
}

SDL_Surface* CSurface::RenderText(char* cText)
{
    std::string strText = ConvertToString(cText);
    return RenderText(strText);
}

SDL_Surface* CSurface::RenderText(char cText)
{
    std::string strText = ConvertToString(cText);
    return RenderText(strText);
}