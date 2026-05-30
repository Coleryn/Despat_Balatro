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
    runSessionLoop();
    printSessionResult();
}

void RunSessionService::initializeSession() {
    gameManager.setupJokers();
    state.persistent.currentBlind = std::make_unique<SmallBlindState>();
    enterBlind();
}

void RunSessionService::enterBlind() {
    state.runtime.blindScore = 0;
    state.runtime.remainingPlays = config.remainingPlays;
    state.runtime.remainingDiscards = config.remainingDiscards;
    state.runtime.deck = gameManager.createShuffledDeck();
    state.runtime.handState = gameManager.drawInitialHand(state.runtime.deck, 8);
}

void RunSessionService::runSessionLoop() {
    while (!isSessionEnded()) {
        printSessionStatus();
        PlayerActionRequest request = readPlayerActionRequest();
        if (canPerformAction(request.action)) {
            processPlayerAction(request);
            if (isBlindCleared()) {
                completeCurrentBlind();
            }
        } else {
            std::cout << "Cannot perform that action.\n";
        }
    }
}

bool RunSessionService::isSessionEnded() {
    return !isBlindCleared() && state.runtime.remainingPlays == 0;
}

bool RunSessionService::isBlindCleared() const {
    const int targetScore = state.persistent.currentBlind->getTargetScore(state.persistent);
    return state.runtime.blindScore >= targetScore;
}

void RunSessionService::completeCurrentBlind() {
    const int rewardMoney = state.persistent.currentBlind->getRewardMoney(state.persistent);
    const std::string clearedBlindName = state.persistent.currentBlind->getName();

    state.persistent.money += rewardMoney;
    state.persistent.currentBlind = state.persistent.currentBlind->nextState(state.persistent);

    std::cout << "\nBlind cleared: " << clearedBlindName << "\n";
    std::cout << "Money gained: " << rewardMoney << "\n";
    std::cout << "Total money: " << state.persistent.money << "\n";
    std::cout << "Next ante: " << state.persistent.ante << "\n";
    std::cout << "Next blind: " << state.persistent.currentBlind->getName() << "\n";

    enterBlind();
}

PlayerActionRequest RunSessionService::readPlayerActionRequest() {
    const std::vector<int> selectedIndices = gameManager.readSelectedIndices(state.runtime.handState.size(), config.maxSelectedCards);
    ChosenHand chosenHand = gameManager.createChosenHand(state.runtime.handState, selectedIndices);
    gameManager.printChosenHand(chosenHand);
    std::string actionStr = gameManager.readPlayerAction();
    PlayerAction action = (actionStr == "PLAY") ? PlayerAction::PLAY : PlayerAction::DISCARD;
    return {action, selectedIndices};
}

bool RunSessionService::canPerformAction(PlayerAction action) {
    if (action == PlayerAction::PLAY) {
        return state.runtime.remainingPlays > 0;
    } else {
        return state.runtime.remainingDiscards > 0;
    }
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
}

void RunSessionService::printSessionResult() {
    const int targetScore = state.persistent.currentBlind->getTargetScore(state.persistent);
    const bool clearedBlind = isBlindCleared();

    std::cout << "Session ended. Final score: " << state.runtime.blindScore << "\n";
    std::cout << "Blind: " << state.persistent.currentBlind->getName() << "\n";
    std::cout << "Blind requirement: " << targetScore << "\n";
    std::cout << "Result: " << (clearedBlind ? "WIN" : "LOSE") << "\n";
    std::cout << "Ante: " << state.persistent.ante << "\n";
    std::cout << "Money: " << state.persistent.money << "\n";
}
