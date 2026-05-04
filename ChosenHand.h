#pragma once
#include "Hand.h"

class ChosenHand {
public:
    void addCard(Card card);
    void setHand(const Hand& hand);
    const Hand& getHand() const;
    int size() const;
    Card getCard(int index) const;
    void clear();

private:
    Hand hand;
};
