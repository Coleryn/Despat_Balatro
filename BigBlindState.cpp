#include "BigBlindState.h"

#include "BossBlindState.h"
#include "FreePlayingCardCommand.h"
#include "RunSessionState.h"

std::string BigBlindState::getName() const {
    return "Big Blind";
}

int BigBlindState::getTargetScore(const RunPersistentState& state) const {
    return 600 * state.ante;
}

int BigBlindState::getRewardMoney(const RunPersistentState& state) const {
    return 4 + state.ante;
}

bool BigBlindState::canSkip() const {
    return true;
}

std::unique_ptr<BlindState> BigBlindState::nextState(RunPersistentState&) const {
    return std::make_unique<BossBlindState>();
}

std::unique_ptr<RewardCommand> BigBlindState::createSkipReward() const {
    return std::make_unique<FreePlayingCardCommand>();
}
