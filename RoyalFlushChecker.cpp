#include "RoyalFlushChecker.h"
#include <iostream>
#include <set>

HandRank RoyalFlushChecker::check(const Hand& hand) {
    char suit = hand.getCard(0).suit;
    std::set<int> ranks;
    for (int i = 0; i < hand.size(); i++) {
        if (hand.getCard(i).suit != suit) {
            if (nextChecker) return nextChecker->check(hand);
            return HandRank::UNKNOWN;
        }
        ranks.insert(hand.getCard(i).rank);
    }
    std::set<int> royal = {10,11,12,13,14};
    if (ranks == royal) { std::cout << "Detected ROYAL FLUSH\n"; return HandRank::ROYAL_FLUSH; }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::UNKNOWN;
}