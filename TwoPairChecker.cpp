#include "TwoPairChecker.h"
#include <iostream>
#include <map>

HandRank TwoPairChecker::check(const Hand& hand) {
    std::map<int,int> freq;
    for (int i = 0; i < hand.size(); i++) freq[hand.getCard(i).rank]++;
    int pairs = 0;
    for (auto& p : freq) if (p.second == 2) pairs++;
    if (pairs == 2) { std::cout << "Detected TWO PAIR\n"; return HandRank::TWO_PAIR; }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::UNKNOWN;
}