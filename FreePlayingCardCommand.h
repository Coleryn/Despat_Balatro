#pragma once

#include "Card.h"
#include "RewardCommand.h"

class FreePlayingCardCommand : public RewardCommand {
public:
    explicit FreePlayingCardCommand(Card card = {Rank::Ace, Suit::Spades});

    RewardTiming getTiming() const override;
    std::string getDescription() const override;
    void execute(RunSessionState& state) override;

private:
    Card card;
};
