#include "FiveOfAKindChecker.h"
#include <iostream>
#include <map>

HandRank FiveOfAKindChecker::check(const Hand& hand) {
    std::map<int,int> freq;
    for (int i = 0; i < hand.size(); i++) freq[hand.getCard(i).rank]++;
    for (auto& p : freq)
        if (p.second == 5) { std::cout << "Detected FIVE OF A KIND\n"; return HandRank::FIVE_OF_A_KIND; }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::UNKNOWN;
}