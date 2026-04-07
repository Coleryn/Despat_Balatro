#include <iostream>
#include "RoyalFlushChecker.h"

bool RoyalFlushChecker::check(const Hand& hand) {
    std::cout << "Detected ROYAL FLUSH\n";
    if (nextChecker) return nextChecker->check(hand);
    return false;
}