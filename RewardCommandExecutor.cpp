#include "RewardCommandExecutor.h"

#include "RunSessionState.h"

#include <iostream>

void RewardCommandExecutor::executeCommandsForTiming(
    RunSessionState& state,
    RewardTiming timing
) const {
    auto& commands = state.persistent.pendingCommands;

    for (auto it = commands.begin(); it != commands.end();) {
        RewardCommand& command = **it;
        if (command.getTiming() != timing) {
            ++it;
            continue;
        }

        std::cout << "Executing reward: " << command.getDescription() << "\n";
        command.execute(state);
        it = commands.erase(it);
    }
}
