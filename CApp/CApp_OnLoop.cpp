#include "CApp.h"

void CApp::OnLoop() 
{
    // Entities
    for(int i = 0;i < CEntity::EntityList.size();i++) 
	{
        if(!CEntity::EntityList[i]) continue;

        CEntity::EntityList[i]->OnLoop();
    }

	CMovementGenerator::MoveGenerator.OnLoop();
}

