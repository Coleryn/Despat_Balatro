#include "FullHouseChecker.h"
#include <iostream>
#include <map>

HandRank FullHouseChecker::check(const Hand& hand) {
    std::map<int,int> freq;
    for (int i = 0; i < hand.size(); i++) freq[hand.getCard(i).rank]++;
    bool hasThree = false, hasTwo = false;
    for (auto& p : freq) {
        if (p.second == 3) hasThree = true;
        if (p.second == 2) hasTwo = true;
    }
    if (hasThree && hasTwo) { std::cout << "Detected FULL HOUSE\n"; return HandRank::FULL_HOUSE; }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::UNKNOWN;
}