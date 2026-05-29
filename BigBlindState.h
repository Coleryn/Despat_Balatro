#pragma once

#include "BlindState.h"

class BigBlindState : public BlindState {
public:
    std::string getName() const override;
    int getTargetScore(const RunPersistentState& state) const override;
    int getRewardMoney(const RunPersistentState& state) const override;
    std::unique_ptr<BlindState> nextState(RunPersistentState& state) const override;
    std::unique_ptr<RewardCommand> createSkipReward() const override;
};
