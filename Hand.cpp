#include "Hand.h"

void Hand::addCard(Card c) { cards.push_back(c); }
int Hand::size() const { return cards.size(); }
Card Hand::getCard(int i) const { return cards[i]; }
void Hand::clear() { cards.clear(); }