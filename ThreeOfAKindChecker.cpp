#include <iostream>
#include "ThreeOfAKindChecker.h"

bool ThreeOfAKindChecker::check(const Hand& hand) {
    std::cout << "Detected THREE OF A KIND\n";
    if (nextChecker) return nextChecker->check(hand);
    return false;
}