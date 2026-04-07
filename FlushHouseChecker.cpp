#include <iostream>
#include "FlushHouseChecker.h"

bool FlushHouseChecker::check(const Hand& hand) {
    std::cout << "Detected FLUSH HOUSE\n";
    if (nextChecker) return nextChecker->check(hand);
    return false;
}