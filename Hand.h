#pragma once
#include <vector>

struct Card {
    int rank;  // 2–14
    char suit; // 'H', 'D', 'C', 'S'
};

class Hand {
public:
    void addCard(Card c);
    int size() const;
    Card getCard(int i) const;
    void clear();

private:
    std::vector<Card> cards;
};