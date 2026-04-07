#include <iostream>
#include "TwoPairChecker.h"

bool TwoPairChecker::check(const Hand& hand) {
    std::cout << "Detected TWO PAIR\n";
    if (nextChecker) return nextChecker->check(hand);
    return false;
}