#include "FreePlayingCardCommand.h"

#include "RunSessionState.h"

FreePlayingCardCommand::FreePlayingCardCommand(Card card)
    : card(card) {}

std::string FreePlayingCardCommand::getName() const {
    return "Free Playing Card";
}

std::string FreePlayingCardCommand::getDescription() const {
    return "Add " + card.toString() + " to the deck next ante";
}

void FreePlayingCardCommand::execute(RunSessionState& state) {
    state.persistent.extraCards.push_back(card);
}
