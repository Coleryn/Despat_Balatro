#include <iostream>
#include "GameManager.h"

int main() {
    GameManager game;
    game.runSession();
    std::cout << "Press Enter to exit...";
    std::cin.get();
    return 0;
}
