#pragma once
#include "Hand.h"

class HandGenerator {
public:
    Hand generateHand();

private:
    Hand makePair();
    Hand makeTwoPair();
    Hand makeThreeOfAKind();
    Hand makeStraight();
    Hand makeFlush();
    Hand makeFullHouse();
    Hand makeFourOfAKind();
    Hand makeStraightFlush();
    Hand makeRoyalFlush();
    Hand makeFiveOfAKind();
    Hand makeFlushHouse();
    Hand makeFlushFive();
    Hand makeHighCard();
};