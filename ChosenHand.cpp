#include "ChosenHand.h"

void ChosenHand::addCard(Card card) {
    hand.addCard(card);
}

void ChosenHand::setHand(const Hand& newHand) {
    hand = newHand;
}

const Hand& ChosenHand::getHand() const {
    return hand;
}

int ChosenHand::size() const {
    return hand.size();
}

Card ChosenHand::getCard(int index) const {
    return hand.getCard(index);
}

void ChosenHand::clear() {
    hand.clear();
}
