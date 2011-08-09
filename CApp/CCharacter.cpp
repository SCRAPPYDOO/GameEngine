#include "CCharacter.h"

CCharacter::CCharacter()
{
    Surf_Unit = NULL;

    fPosX = 50;
    fPosY = 50;
    nWidth = 50;
    nHeight = 50;

    fRadius = 0;  //radius of colision box
    fGoX = 0;   // destination point
    fGoY = 0;   
    fNewX = 0;  //position where we are going to
    fNewY = 0;  
    fSpeed = 0; 

    nUnitFlag = 0;
    nUnitMovementFlag = 0;

    CurrentFrameCol = 0;
    CurrentFrameRow = 0;

    UnitIsAlive = true;


    cCharacterName = "Marcin";

    nActualHealth = 20;
    nMaxHealth = 100;
}