#include "FreePlayingCardCommand.h"

#include "RunSessionState.h"

FreePlayingCardCommand::FreePlayingCardCommand(Card card)
    : card(card) {}

RewardTiming FreePlayingCardCommand::getTiming() const {
    return RewardTiming::NextAnte;
}

std::string FreePlayingCardCommand::getDescription() const {
    return "Add " + card.toString() + " to the deck next ante";
}

void FreePlayingCardCommand::execute(RunSessionState& state) {
    state.persistent.extraCards.push_back(card);
}
