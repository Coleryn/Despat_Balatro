#include "SmallBlindState.h"

#include "BigBlindState.h"
#include "RunSessionState.h"

std::string SmallBlindState::getName() const {
    return "Small Blind";
}

int SmallBlindState::getTargetScore(const RunPersistentState& state) const {
    return 300 * state.ante;
}

int SmallBlindState::getRewardMoney(const RunPersistentState& state) const {
    return 3 + state.ante;
}

std::unique_ptr<BlindState> SmallBlindState::nextState(RunPersistentState&) const {
    return std::make_unique<BigBlindState>();
}

std::unique_ptr<RewardCommand> SmallBlindState::createSkipReward() const {
    return nullptr;
}
