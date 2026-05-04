#pragma once
#include <vector>
#include "Card.h"

class Hand {
public:
    void addCard(Card c);
    int size() const;
    Card getCard(int i) const;
    void clear();

private:
    std::vector<Card> cards;
};
