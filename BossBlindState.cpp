#include "BossBlindState.h"

#include "RunSessionState.h"
#include "SmallBlindState.h"

std::string BossBlindState::getName() const {
    return "Boss Blind";
}

int BossBlindState::getTargetScore(const RunPersistentState& state) const {
    return 1000 * state.ante;
}

int BossBlindState::getRewardMoney(const RunPersistentState& state) const {
    return 5 + state.ante;
}

bool BossBlindState::canSkip() const {
    return false;
}

std::unique_ptr<BlindState> BossBlindState::nextState(RunPersistentState& state) const {
    state.ante++;
    return std::make_unique<SmallBlindState>();
}

PendingCommand BossBlindState::createSkipRewardCommand() const {
    return {
        RewardTiming::Start,
        true,
        nullptr
    };
}
