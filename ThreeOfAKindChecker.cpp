#include "ThreeOfAKindChecker.h"
#include <iostream>
#include <map>

HandRank ThreeOfAKindChecker::check(const Hand& hand) {
    std::map<int,int> freq;
    for (int i = 0; i < hand.size(); i++) freq[hand.getCard(i).rank]++;
    for (auto& p : freq)
        if (p.second == 3) { std::cout << "Detected THREE OF A KIND\n"; return HandRank::THREE_OF_A_KIND; }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::UNKNOWN;
}