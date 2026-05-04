#include <iostream>
#include <random>
#include <algorithm>
#include "HandGenerator.h"

Hand HandGenerator::generateHand()
{
    std::cout << "Generating hand...\n";
    buildDeck();
    shuffleDeck();
    std::vector<Card> cards = deal(8);
    Hand hand;
    for (const auto& c : cards) {
        hand.addCard(c);
    }
    return hand;
}

void HandGenerator::buildDeck() {
    deck.clear();
    char suits[4] = {'H', 'D', 'C', 'S'};
    for (int s = 0; s < 4; s++) {
        for (int rank = 2; rank <= 14; rank++) {
            deck.push_back({rank, suits[s]});
        }
    }
}

void HandGenerator::shuffleDeck() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(deck.begin(), deck.end(), rng);
}

std::vector<Card> HandGenerator::deal(int n) {
    if ((int)deck.size() < n)
        throw std::runtime_error("Not enough cards in deck");
    std::vector<Card> dealt(deck.begin(), deck.begin() + n);
    deck.erase(deck.begin(), deck.begin() + n);
    return dealt;
}
