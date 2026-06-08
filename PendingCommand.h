#pragma once

#include "RewardCommand.h"
#include "RewardTiming.h"

#include <memory>

struct PendingCommand {
    RewardTiming timing;
    bool executed = false;
    std::unique_ptr<RewardCommand> command;
};
