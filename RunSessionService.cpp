#include "RunSessionService.h"

#include "ChosenHand.h"
#include "PlayedHandResult.h"
#include "ScoreContext.h"
#include "SmallBlindState.h"

#include <iostream>
#include <memory>
#include <vector>

RunSessionService::RunSessionService(GameManager& gm, BlindConfig cfg)
    : gameManager(gm), config(cfg) {}

void RunSessionService::runSession() {
    initializeSession();
    runBlindSelectionLoop();
    printSessionResult();
}

void RunSessionService::initializeSession() {
    gameManager.setupJokers();
    state.persistent.currentBlind = std::make_unique<SmallBlindState>();
    rewardCommandExecutor.executeCommandsForTiming(state, RewardTiming::Start);
}

void RunSessionService::enterBlind() {
    state.runtime.blindScore = 0;
    state.runtime.remainingPlays = config.remainingPlays;
    state.runtime.remainingDiscards = config.remainingDiscards;
    state.runtime.deck = gameManager.createShuffledDeck();
    for (const Card& card : state.persistent.extraCards) {
        state.runtime.deck.addCard(card);
    }
    state.runtime.deck.shuffle();
    state.runtime.handState = gameManager.drawInitialHand(state.runtime.deck, 8);
    rewardCommandExecutor.executeCommandsForTiming(state, RewardTiming::NextBlind);
}

void RunSessionService::runBlindSelectionLoop() {
    while (true) {
        printBlindSelectionStatus();
        processBlindSelection(gameManager.readBlindSelection());
        if (isSessionEnded()) {
            return;
        }
    }
}

void RunSessionService::runBlindGameplayLoop() {
    while (!isSessionEnded() && !isBlindCleared()) {
        printSessionStatus();
        PlayerActionRequest request = readPlayerActionRequest();
        if (canPerformAction(request.action)) {
            processPlayerAction(request);
            if (isBlindCleared()) {
                completeCurrentBlind();
                return;
            }
        } else {
            std::cout << "Cannot perform that action.\n";
        }
    }

    if (!isBlindCleared()) {
        runLost = true;
    }
}

bool RunSessionService::isSessionEnded() {
    return runLost;
}

bool RunSessionService::isBlindCleared() const {
    const int targetScore = state.persistent.currentBlind->getTargetScore(state.persistent);
    return state.runtime.blindScore >= targetScore;
}

void RunSessionService::completeCurrentBlind() {
    const int rewardMoney = state.persistent.currentBlind->getRewardMoney(state.persistent);
    const std::string clearedBlindName = state.persistent.currentBlind->getName();

    state.persistent.money += rewardMoney;

    std::cout << "\nBlind cleared: " << clearedBlindName << "\n";
    std::cout << "Money gained: " << rewardMoney << "\n";
    std::cout << "Total money: " << state.persistent.money << "\n";

    advanceToNextBlind();
}

void RunSessionService::advanceToNextBlind() {
    const int previousAnte = state.persistent.ante;
    state.persistent.currentBlind = state.persistent.currentBlind->nextState(state.persistent);

    if (state.persistent.ante != previousAnte) {
        rewardCommandExecutor.executeCommandsForTiming(state, RewardTiming::NextAnte);
    }

    std::cout << "Next ante: " << state.persistent.ante << "\n";
    std::cout << "Next blind: " << state.persistent.currentBlind->getName() << "\n";
}

void RunSessionService::processBlindSelection(BlindSelection selection) {
    if (selection == BlindSelection::Skip) {
        processSkipAction();
        return;
    }

    enterBlind();
    runBlindGameplayLoop();
}

PlayerActionRequest RunSessionService::readPlayerActionRequest() {
    std::string actionStr = gameManager.readPlayerAction();
    PlayerAction action = PlayerAction::INVALID;

    if (actionStr == "PLAY") {
        action = PlayerAction::PLAY;
    } else if (actionStr == "DISCARD") {
        action = PlayerAction::DISCARD;
    } else {
        return {action, {}};
    }

    const std::vector<int> selectedIndices = gameManager.readSelectedIndices(state.runtime.handState.size(), config.maxSelectedCards);
    ChosenHand chosenHand = gameManager.createChosenHand(state.runtime.handState, selectedIndices);
    gameManager.printChosenHand(chosenHand);
    return {action, selectedIndices};
}

bool RunSessionService::canPerformAction(PlayerAction action) {
    if (action == PlayerAction::PLAY) {
        return state.runtime.remainingPlays > 0;
    }
    if (action == PlayerAction::DISCARD) {
        return state.runtime.remainingDiscards > 0;
    }

    return false;
}

void RunSessionService::processPlayerAction(const PlayerActionRequest& request) {
    if (request.action == PlayerAction::PLAY) {
        processPlayAction(request.selectedIndices);
    } else {
        processDiscardAction(request.selectedIndices);
    }
}

void RunSessionService::processPlayAction(const std::vector<int>& selectedIndices) {
    ChosenHand chosenHand = gameManager.createChosenHand(state.runtime.handState, selectedIndices);
    PlayedHandResult result = gameManager.resolveHand(chosenHand);
    ScoreContext context = gameManager.createScoreContext(result);
    gameManager.applyJokers(context);
    gameManager.printResult(result, context);
    state.runtime.blindScore += context.getFinalScore();
    gameManager.discardAndRedraw(state.runtime.handState, state.runtime.deck, selectedIndices, 8);
    std::cout << "\nHand after play and redraw:\n";
    gameManager.printCards(state.runtime.handState.getCards());
    state.runtime.remainingPlays--;
}

void RunSessionService::processDiscardAction(const std::vector<int>& selectedIndices) {
    gameManager.discardAndRedraw(state.runtime.handState, state.runtime.deck, selectedIndices, 8);
    std::cout << "\nHand after discard and redraw:\n";
    gameManager.printCards(state.runtime.handState.getCards());
    state.runtime.remainingDiscards--;
}

void RunSessionService::processSkipAction() {
    if (!state.persistent.currentBlind->canSkip()) {
        std::cout << "\nThis blind cannot be skipped.\n";
        return;
    }

    PendingCommand pendingReward =
        state.persistent.currentBlind->createSkipRewardCommand();

    if (pendingReward.command) {
        std::cout << "\nSkip reward stored: "
                  << pendingReward.command->getDescription() << "\n";
        state.persistent.pendingCommands.push_back(std::move(pendingReward));
    }

    std::cout << "Skipped blind: "
              << state.persistent.currentBlind->getName() << "\n";
    advanceToNextBlind();
}

void RunSessionService::printBlindSelectionStatus() {
    std::cout << "\n=== Blind Selection ===\n";
    std::cout << "Ante: " << state.persistent.ante << "\n";
    std::cout << "Blind: " << state.persistent.currentBlind->getName() << "\n";
    std::cout << "Target score: "
              << state.persistent.currentBlind->getTargetScore(state.persistent)
              << "\n";
    std::cout << "Reward money: "
              << state.persistent.currentBlind->getRewardMoney(state.persistent)
              << "\n";
    std::cout << "Pending rewards: "
              << state.persistent.pendingCommands.size() << "\n";
    for (const PendingCommand& pending : state.persistent.pendingCommands) {
        if (pending.command) {
            std::cout << "- " << pending.command->getDescription() << "\n";
        }
    }
}

void RunSessionService::printSessionStatus() {
    gameManager.printGeneratedHand(state.runtime.handState);
    std::cout << "Ante: " << state.persistent.ante << "\n";
    std::cout << "Blind: " << state.persistent.currentBlind->getName() << "\n";
    std::cout << "Blind requirement: "
              << state.persistent.currentBlind->getTargetScore(state.persistent)
              << "\n";
    std::cout << "Reward money: "
              << state.persistent.currentBlind->getRewardMoney(state.persistent)
              << "\n";
    std::cout << "Remaining plays: " << state.runtime.remainingPlays
              << ", Remaining discards: " << state.runtime.remainingDiscards
              << "\n";
    std::cout << "Current blind score: " << state.runtime.blindScore << "\n";
    std::cout << "Pending rewards: "
              << state.persistent.pendingCommands.size() << "\n";
    for (const PendingCommand& pending : state.persistent.pendingCommands) {
        if (pending.command) {
            std::cout << "- " << pending.command->getDescription() << "\n";
        }
    }
    std::cout << "Extra deck cards: "
              << state.persistent.extraCards.size() << "\n";
}

void RunSessionService::printSessionResult() {
    const int targetScore = state.persistent.currentBlind->getTargetScore(state.persistent);
    const bool clearedBlind = !runLost && isBlindCleared();

    std::cout << "Session ended. Final score: " << state.runtime.blindScore << "\n";
    std::cout << "Blind: " << state.persistent.currentBlind->getName() << "\n";
    std::cout << "Blind requirement: " << targetScore << "\n";
    std::cout << "Result: " << (clearedBlind ? "WIN" : "LOSE") << "\n";
    std::cout << "Ante: " << state.persistent.ante << "\n";
    std::cout << "Money: " << state.persistent.money << "\n";
}
