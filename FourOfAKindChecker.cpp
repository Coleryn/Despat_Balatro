#include <iostream>
#include "FourOfAKindChecker.h"

bool FourOfAKindChecker::check(const Hand& hand) {
    std::cout << "Detected FOUR OF A KIND\n";
    if (nextChecker) return nextChecker->check(hand);
    return false;
}