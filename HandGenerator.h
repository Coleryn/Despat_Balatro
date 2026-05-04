#pragma once
#include "Card.h"
#include "Hand.h"
#include <vector>

class HandGenerator
{
public:
    Hand generateHand();
    void buildDeck();
    void shuffleDeck();
    std::vector<Card> deal(int n);

private:
    std::vector<Card> deck;
};
