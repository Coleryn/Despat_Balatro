#include <iostream>
#include <string>
#include <sstream>
#include "HandPlayer.h"

ChosenHand HandPlayer::playHand(const Hand& hand) {
    std::cout << "Your hand (pick up to 5):\n";
    for (int i = 0; i < hand.size(); i++) {
        Card c = hand.getCard(i);
        std::string rank_str = (c.rank == 11 ? "J" : c.rank == 12 ? "Q" : c.rank == 13 ? "K" : c.rank == 14 ? "A" : std::to_string(c.rank));
        std::cout << i << ": " << rank_str << c.suit << " | ";
        if ((i + 1) % 4 == 0) std::cout << "\n";
    }
    std::cout << "\nEnter space-separated indices (0-" << (hand.size()-1) << ") to keep: ";
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    int idx;
    ChosenHand chosenHand;
    while (ss >> idx) {
        if (idx >= 0 && idx < hand.size()) {
            chosenHand.addCard(hand.getCard(idx));
        }
    }
    std::cout << "Selected " << chosenHand.size() << " cards to play.\n";
    return chosenHand;
}
