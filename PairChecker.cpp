#include <iostream>
#include "PairChecker.h"

bool PairChecker::check(const Hand& hand) {
    std::cout << "Detected PAIR\n";
    return true;
    // if real logic: if fail → if (nextChecker) return nextChecker->check(hand);
}