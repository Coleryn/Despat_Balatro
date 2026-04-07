#include <iostream>
#include "FlushChecker.h"

bool FlushChecker::check(const Hand& hand) {
    std::cout << "Detected FLUSH\n";
    if (nextChecker) return nextChecker->check(hand);
    return false;
}