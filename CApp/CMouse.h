#ifndef _CMOUSE_H_
	#define _CMOUSE_H_

#include <SDL.h>

class CMouse 
{
	public:
		CMouse()
		{
			
		}

		~CMouse() {}

		static CMouse Mouse;

		int x;
		int y;


};

#endif

