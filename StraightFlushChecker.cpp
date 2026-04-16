#include "StraightFlushChecker.h"
#include <iostream>
#include <vector>
#include <algorithm>

HandRank StraightFlushChecker::check(const Hand& hand) {
    char suit = hand.getCard(0).suit;
    std::vector<int> ranks;
    for (int i = 0; i < hand.size(); i++) {
        if (hand.getCard(i).suit != suit) {
            if (nextChecker) return nextChecker->check(hand);
            return HandRank::UNKNOWN;
        }
        ranks.push_back(hand.getCard(i).rank);
    }
    std::sort(ranks.begin(), ranks.end());
    for (int i = 1; i < ranks.size(); i++)
        if (ranks[i] != ranks[i-1]+1) {
            if (nextChecker) return nextChecker->check(hand);
            return HandRank::UNKNOWN;
        }
    std::cout << "Detected STRAIGHT FLUSH\n";
    return HandRank::STRAIGHT_FLUSH;
}