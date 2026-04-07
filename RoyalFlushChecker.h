#pragma once
#include "PokerHandChecker.h"

class RoyalFlushChecker : public PokerHandChecker {
public:
    bool check(const Hand& hand) override;
};