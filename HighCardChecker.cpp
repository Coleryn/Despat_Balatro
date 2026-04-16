#include "HighCardChecker.h"
#include <iostream>

HandRank HighCardChecker::check(const Hand& hand) {
    std::cout << "Detected HIGH CARD\n";
    return HandRank::HIGH_CARD;
}