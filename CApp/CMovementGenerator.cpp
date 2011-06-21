#include "CMovementGenerator.h"

CMovementGenerator CMovementGenerator::MoveGenerator;

void CMovementGenerator::OnLoop()
{
	for(int i = 0;i < CEntity::EntityList.size();i++) 
	{
        if(!CEntity::EntityList[i]) continue;

        CEntity::EntityList[i]->OnMoveToPoint();
    }
}