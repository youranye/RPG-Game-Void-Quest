#include "Character.h"
#include "BattleManager.h"
#include "GameManager.h"

int main()
{
    IOManager iomanager(std::cin, std::cout);
    GameManager gm(iomanager);
    gm.startGame();
    return 0;
}