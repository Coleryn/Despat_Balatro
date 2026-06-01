#pragma once

#include <vector>

enum class PlayerAction {
    PLAY,
    DISCARD,
    INVALID
};

struct PlayerActionRequest {
    PlayerAction action;
    std::vector<int> selectedIndices;
};
