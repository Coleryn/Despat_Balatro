#include "StraightChecker.h"
#include <iostream>
#include <vector>
#include <algorithm>

HandRank StraightChecker::check(const Hand& hand) {
    std::vector<int> ranks;
    for (int i = 0; i < hand.size(); i++) ranks.push_back(hand.getCard(i).rank);
    std::sort(ranks.begin(), ranks.end());
    for (int i = 1; i < ranks.size(); i++)
        if (ranks[i] != ranks[i-1]+1) {
            if (nextChecker) return nextChecker->check(hand);
            return HandRank::UNKNOWN;
        }
    std::cout << "Detected STRAIGHT\n";
    return HandRank::STRAIGHT;
}