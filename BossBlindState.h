#pragma once

#include "BlindState.h"

class BossBlindState : public BlindState {
public:
    std::string getName() const override;
    int getTargetScore(const RunPersistentState& state) const override;
    int getRewardMoney(const RunPersistentState& state) const override;
    bool canSkip() const override;
    std::unique_ptr<BlindState> nextState(RunPersistentState& state) const override;
    PendingCommand createSkipRewardCommand() const override;
};
