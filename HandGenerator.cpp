#include "HandGenerator.h"
#include <algorithm>
#include <random>
#include <stdexcept>

void HandGenerator::buildDeck() {
    deck.clear();
    char suits[] = {'H', 'D', 'C', 'S'};
    for (char suit : suits) {
        for (int rank = 2; rank <= 14; rank++) {
            deck.push_back({rank, suit});
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
    std::vector<Card> hand(deck.begin(), deck.begin() + n);
    deck.erase(deck.begin(), deck.begin() + n);
    return hand;
}