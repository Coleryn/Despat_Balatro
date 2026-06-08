#include "RewardCommandExecutor.h"

#include "RunSessionState.h"

#include <iostream>

void RewardCommandExecutor::executeCommandsForTiming(
    RunSessionState& state,
    RewardTiming timing
) const {
    auto& commands = state.persistent.pendingCommands;

    for (auto it = commands.begin(); it != commands.end();) {
        PendingCommand& pending = *it;
        if (pending.executed || pending.timing != timing || !pending.command) {
            ++it;
            continue;
        }

        std::cout << "Executing reward: "
                  << pending.command->getDescription() << "\n";
        pending.command->execute(state);
        pending.executed = true;
        it = commands.erase(it);
    }
}
