#ifndef _CMOVEGENERATOR_H_
    #define _CMOVEGENERATOR_H_

#include <vector>
#include "CEntity.h"

class CMovementGenerator
{
	public:
		static CMovementGenerator MoveGenerator;

        void OnLoop();
};

#endif
