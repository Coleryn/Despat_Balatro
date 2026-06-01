#pragma once

#include "BlindSelection.h"
#include "BlindConfig.h"
#include "RunSessionState.h"
#include "PlayerAction.h"
#include "GameManager.h"
#include "RewardCommandExecutor.h"

class RunSessionService {
public:
    RunSessionService(GameManager& gameManager, BlindConfig config);
    void runSession();

private:
    GameManager& gameManager;
    BlindConfig config;
    RunSessionState state;
    RewardCommandExecutor rewardCommandExecutor;
    bool runLost = false;

    void initializeSession();
    void runBlindSelectionLoop();
    void enterBlind();
    void runBlindGameplayLoop();
    bool isSessionEnded();
    bool isBlindCleared() const;
    void completeCurrentBlind();
    void advanceToNextBlind();
    void processBlindSelection(BlindSelection selection);
    PlayerActionRequest readPlayerActionRequest();
    bool canPerformAction(PlayerAction action);
    void processPlayerAction(const PlayerActionRequest& request);
    void processPlayAction(const std::vector<int>& selectedIndices);
    void processDiscardAction(const std::vector<int>& selectedIndices);
    void processSkipAction();
    void printBlindSelectionStatus();
    void printSessionStatus();
    void printSessionResult();
};
