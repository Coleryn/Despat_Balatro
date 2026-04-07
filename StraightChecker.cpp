#include <iostream>
#include "StraightChecker.h"

bool StraightChecker::check(const Hand& hand) {
    std::cout << "Detected STRAIGHT\n";
    if (nextChecker) return nextChecker->check(hand);
    return false;
}