#pragma once

#include "Card.h"

#include <vector>

class Deck {
public:
    Deck();

    void initialize();
    void shuffle();
    void addCard(const Card& card);

    Card drawCard();

    bool isEmpty() const;
    int size() const;

private:
    std::vector<Card> cards;
};
