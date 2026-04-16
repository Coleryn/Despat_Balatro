#pragma once
#include "Hand.h"
#include "HandRank.h"

class PokerHandChecker {
public:
    virtual HandRank check(const Hand& hand) = 0;
    void setNext(PokerHandChecker* next);

protected:
    PokerHandChecker* nextChecker = nullptr;
};