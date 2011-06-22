#include "CInterface.h"

CInterface CInterface::InterfaceControl;

bool CInterface::OnLoad()
{

    return true;
}

bool CInterface::OnEvent(int x, int y)
{
    //sprawdz czy jestemy na  polu interfacu
    // jezlei nie return true;
    //sprawdz wszytkie buttony  interfacu czy sa  na  x y i wstaw  button do on loop
    return false;
}

void CInterface::OnLoop()
{
    //jezlei mamy jakies uzyte butony w quave wykonaj ich zadania
}

void CInterface::OnRender(SDL_Surface* Surf_Display, int MapX, int MapY)
{


}

void CInterface::OnCleanup()
{

}
