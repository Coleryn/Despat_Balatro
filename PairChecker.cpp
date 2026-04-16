#include "PairChecker.h"
#include <iostream>
#include <map>

HandRank PairChecker::check(const Hand& hand) {
    std::map<int,int> freq;
    for (int i = 0; i < hand.size(); i++) freq[hand.getCard(i).rank]++;
    int pairs = 0;
    for (auto& p : freq) if (p.second == 2) pairs++;
    if (pairs == 1) { std::cout << "Detected PAIR\n"; return HandRank::PAIR; }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::UNKNOWN;
}