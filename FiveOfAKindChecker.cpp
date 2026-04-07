#include <iostream>
#include "FiveOfAKindChecker.h"

bool FiveOfAKindChecker::check(const Hand& hand) {
    std::cout << "Detected FIVE OF A KIND\n";
    if (nextChecker) return nextChecker->check(hand);
    return false;
}