#pragma once

struct RunSessionState;

class RewardCommand {
public:
    virtual ~RewardCommand() = default;

    virtual void execute(RunSessionState& state) = 0;
};
