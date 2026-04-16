#include "HandGenerator.h"
#include <cstdlib>
#include <ctime>

Hand HandGenerator::generateHand() {
    srand(time(nullptr));
    int r = rand() % 13; // 0–12, satu per combo
    switch (r) {
        case 0:  return makeFlushFive();
        case 1:  return makeFlushHouse();
        case 2:  return makeFiveOfAKind();
        case 3:  return makeRoyalFlush();
        case 4:  return makeStraightFlush();
        case 5:  return makeFourOfAKind();
        case 6:  return makeFullHouse();
        case 7:  return makeFlush();
        case 8:  return makeStraight();
        case 9:  return makeThreeOfAKind();
        case 10: return makeTwoPair();
        case 11: return makePair();
        default: return makeHighCard();
    }
}

Hand HandGenerator::makeHighCard() {
    Hand h;
    h.addCard({2, 'H'}); h.addCard({5, 'D'});
    h.addCard({8, 'C'}); h.addCard({11, 'S'});
    h.addCard({13, 'H'});
    return h;
}

Hand HandGenerator::makePair() {
    Hand h;
    h.addCard({7, 'H'}); h.addCard({7, 'D'});
    h.addCard({2, 'C'}); h.addCard({5, 'S'});
    h.addCard({9, 'H'});
    return h;
}

Hand HandGenerator::makeTwoPair() {
    Hand h;
    h.addCard({7, 'H'}); h.addCard({7, 'D'});
    h.addCard({9, 'C'}); h.addCard({9, 'S'});
    h.addCard({2, 'H'});
    return h;
}

Hand HandGenerator::makeThreeOfAKind() {
    Hand h;
    h.addCard({7, 'H'}); h.addCard({7, 'D'});
    h.addCard({7, 'C'}); h.addCard({2, 'S'});
    h.addCard({5, 'H'});
    return h;
}

Hand HandGenerator::makeStraight() {
    Hand h;
    h.addCard({5, 'H'}); h.addCard({6, 'D'});
    h.addCard({7, 'C'}); h.addCard({8, 'S'});
    h.addCard({9, 'H'});
    return h;
}

Hand HandGenerator::makeFlush() {
    Hand h;
    h.addCard({2, 'H'}); h.addCard({5, 'H'});
    h.addCard({8, 'H'}); h.addCard({11, 'H'});
    h.addCard({13, 'H'});
    return h;
}

Hand HandGenerator::makeFullHouse() {
    Hand h;
    h.addCard({7, 'H'}); h.addCard({7, 'D'});
    h.addCard({7, 'C'}); h.addCard({9, 'S'});
    h.addCard({9, 'H'});
    return h;
}

Hand HandGenerator::makeFourOfAKind() {
    Hand h;
    h.addCard({7, 'H'}); h.addCard({7, 'D'});
    h.addCard({7, 'C'}); h.addCard({7, 'S'});
    h.addCard({2, 'H'});
    return h;
}

Hand HandGenerator::makeStraightFlush() {
    Hand h;
    h.addCard({5, 'H'}); h.addCard({6, 'H'});
    h.addCard({7, 'H'}); h.addCard({8, 'H'});
    h.addCard({9, 'H'});
    return h;
}

Hand HandGenerator::makeRoyalFlush() {
    Hand h;
    h.addCard({10, 'H'}); h.addCard({11, 'H'});
    h.addCard({12, 'H'}); h.addCard({13, 'H'});
    h.addCard({14, 'H'});
    return h;
}

Hand HandGenerator::makeFiveOfAKind() {
    Hand h;
    h.addCard({7, 'H'}); h.addCard({7, 'D'});
    h.addCard({7, 'C'}); h.addCard({7, 'S'});
    h.addCard({7, 'H'});
    return h;
}

Hand HandGenerator::makeFlushHouse() {
    Hand h;
    h.addCard({7, 'H'}); h.addCard({7, 'H'});
    h.addCard({7, 'H'}); h.addCard({9, 'H'});
    h.addCard({9, 'H'});
    return h;
}

Hand HandGenerator::makeFlushFive() {
    Hand h;
    h.addCard({7, 'H'}); h.addCard({7, 'H'});
    h.addCard({7, 'H'}); h.addCard({7, 'H'});
    h.addCard({7, 'H'});
    return h;
}