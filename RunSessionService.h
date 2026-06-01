#pragma once

#include "BlindConfig.h"
#include "RunSessionState.h"
#include "PlayerAction.h"
#include "GameManager.h"

class RunSessionService {
public:
    RunSessionService(GameManager& gameManager, BlindConfig config);
    void runSession();

private:
    GameManager& gameManager;
    BlindConfig config;
    RunSessionState state;

    void initializeSession();
    void enterBlind();
    void runSessionLoop();
    bool isSessionEnded();
    bool isBlindCleared() const;
    void completeCurrentBlind();
    PlayerActionRequest readPlayerActionRequest();
    bool canPerformAction(PlayerAction action);
    void processPlayerAction(const PlayerActionRequest& request);
    void processPlayAction(const std::vector<int>& selectedIndices);
    void processDiscardAction(const std::vector<int>& selectedIndices);
    void printSessionStatus();
    void printSessionResult();
};
