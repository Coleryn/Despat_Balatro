#include "FlushChecker.h"
#include <iostream>

HandRank FlushChecker::check(const Hand& hand) {
    char suit = hand.getCard(0).suit;
    for (int i = 1; i < hand.size(); i++)
        if (hand.getCard(i).suit != suit) {
            if (nextChecker) return nextChecker->check(hand);
            return HandRank::UNKNOWN;
        }
    std::cout << "Detected FLUSH\n";
    return HandRank::FLUSH;
}