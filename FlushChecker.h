#pragma once
#include "PokerHandChecker.h"

class FlushChecker : public PokerHandChecker {
public:
    bool check(const Hand& hand) override;
};