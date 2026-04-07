#pragma once
#include "PokerHandChecker.h"

class FiveOfAKindChecker : public PokerHandChecker {
public:
    bool check(const Hand& hand) override;
};