#include "BonusHandCommand.h"

#include "RunSessionState.h"

BonusHandCommand::BonusHandCommand(int amount)
    : amount(amount) {}

std::string BonusHandCommand::getName() const {
    return "Bonus Hand";
}

std::string BonusHandCommand::getDescription() const {
    return "+1 hand next blind";
}

void BonusHandCommand::execute(RunSessionState& state) {
    state.runtime.remainingPlays += amount;
}
