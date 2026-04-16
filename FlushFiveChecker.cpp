#include "FlushFiveChecker.h"
#include <iostream>

HandRank FlushFiveChecker::check(const Hand& hand) {
    if (hand.size() < 5) { if (nextChecker) return nextChecker->check(hand); return HandRank::UNKNOWN; }
    int rank = hand.getCard(0).rank;
    char suit = hand.getCard(0).suit;
    for (int i = 1; i < hand.size(); i++)
        if (hand.getCard(i).rank != rank || hand.getCard(i).suit != suit) {
            if (nextChecker) return nextChecker->check(hand);
            return HandRank::UNKNOWN;
        }
    std::cout << "Detected FLUSH FIVE\n";
    return HandRank::FLUSH_FIVE;
}