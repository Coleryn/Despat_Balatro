#pragma once

#include "PendingCommand.h"

#include <memory>
#include <string>

struct RunPersistentState;

class BlindState {
public:
    virtual ~BlindState() = default;

    virtual std::string getName() const = 0;
    virtual int getTargetScore(const RunPersistentState& state) const = 0;
    virtual int getRewardMoney(const RunPersistentState& state) const = 0;
    virtual bool canSkip() const = 0;
    virtual std::unique_ptr<BlindState> nextState(RunPersistentState& state) const = 0;
    virtual PendingCommand createSkipRewardCommand() const = 0;
};
