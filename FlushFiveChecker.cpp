#include <iostream>
#include "FlushFiveChecker.h"

bool FlushFiveChecker::check(const Hand& hand) {
    std::cout << "Detected FLUSH FIVE\n";
    if (nextChecker) return nextChecker->check(hand);
    return false;
}