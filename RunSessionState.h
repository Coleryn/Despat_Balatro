#pragma once

#include "BlindState.h"
#include "Deck.h"
#include "HandState.h"
#include "RewardCommand.h"

#include <memory>
#include <vector>

struct RunPersistentState {
    int ante = 1;
    int money = 0;
    std::vector<Card> extraCards;
    std::vector<std::unique_ptr<RewardCommand>> pendingCommands;
    std::unique_ptr<BlindState> currentBlind;
};

struct BlindRuntimeState {
    int blindScore = 0;
    int remainingPlays = 3;
    int remainingDiscards = 3;
    Deck deck;
    HandState handState;
};

struct RunSessionState {
    RunPersistentState persistent;
    BlindRuntimeState runtime;
};
