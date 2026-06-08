#pragma once

#include <string>

struct RunSessionState;

class RewardCommand {
public:
    virtual ~RewardCommand() = default;

    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual void execute(RunSessionState& state) = 0;
};
