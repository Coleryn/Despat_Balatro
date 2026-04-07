#include <iostream>
#include "StraightFlushChecker.h"

bool StraightFlushChecker::check(const Hand& hand) {
    std::cout << "Detected STRAIGHT FLUSH\n";
    if (nextChecker) return nextChecker->check(hand);
    return false;
}