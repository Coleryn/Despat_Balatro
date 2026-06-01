#pragma once

#include "RewardTiming.h"

struct RunSessionState;

class RewardCommandExecutor {
public:
    void executeCommandsForTiming(RunSessionState& state, RewardTiming timing) const;
};
