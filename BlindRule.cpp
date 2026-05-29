#include "BlindRule.h"

bool BlindRule::isCleared(int score, int requiredScore) const {
    return score >= requiredScore;
}
