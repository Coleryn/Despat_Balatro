#include "SmallBlindState.h"

#include "BigBlindState.h"
#include "BonusHandCommand.h"
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

bool SmallBlindState::canSkip() const {
    return true;
}

std::unique_ptr<BlindState> SmallBlindState::nextState(RunPersistentState&) const {
    return std::make_unique<BigBlindState>();
}

PendingCommand SmallBlindState::createSkipRewardCommand() const {
    return {
        RewardTiming::NextBlind,
        false,
        std::make_unique<BonusHandCommand>()
    };
}
