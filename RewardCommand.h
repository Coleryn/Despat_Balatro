#pragma once

#include "RewardTiming.h"

#include <string>

struct RunSessionState;

class RewardCommand {
public:
    virtual ~RewardCommand() = default;

    virtual RewardTiming getTiming() const = 0;
    virtual std::string getDescription() const = 0;
    virtual void execute(RunSessionState& state) = 0;
};
