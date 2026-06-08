#pragma once

#include "RewardCommand.h"

class BonusHandCommand : public RewardCommand {
public:
    explicit BonusHandCommand(int amount = 1);

    std::string getName() const override;
    std::string getDescription() const override;
    void execute(RunSessionState& state) override;

private:
    int amount;
};
