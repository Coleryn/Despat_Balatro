#include "FourOfAKindChecker.h"
#include <iostream>
#include <map>

HandRank FourOfAKindChecker::check(const Hand& hand) {
    std::map<int,int> freq;
    for (int i = 0; i < hand.size(); i++) freq[hand.getCard(i).rank]++;
    for (auto& p : freq)
        if (p.second == 4) { std::cout << "Detected FOUR OF A KIND\n"; return HandRank::FOUR_OF_A_KIND; }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::UNKNOWN;
}