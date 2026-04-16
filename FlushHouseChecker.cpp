#include "FlushHouseChecker.h"
#include <iostream>
#include <map>

HandRank FlushHouseChecker::check(const Hand& hand) {
    std::map<int,int> freq;
    char suit = hand.getCard(0).suit;
    for (int i = 0; i < hand.size(); i++) {
        if (hand.getCard(i).suit != suit) {
            if (nextChecker) return nextChecker->check(hand);
            return HandRank::UNKNOWN;
        }
        freq[hand.getCard(i).rank]++;
    }
    bool hasThree = false, hasTwo = false;
    for (auto& p : freq) {
        if (p.second == 3) hasThree = true;
        if (p.second == 2) hasTwo = true;
    }
    if (hasThree && hasTwo) { std::cout << "Detected FLUSH HOUSE\n"; return HandRank::FLUSH_HOUSE; }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::UNKNOWN;
}