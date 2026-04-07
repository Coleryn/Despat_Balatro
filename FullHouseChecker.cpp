#include <iostream>
#include "FullHouseChecker.h"

bool FullHouseChecker::check(const Hand& hand) {
    std::cout << "Detected FULL HOUSE\n";
    if (nextChecker) return nextChecker->check(hand);
    return false;
}