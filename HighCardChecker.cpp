#include <iostream>
#include "HighCardChecker.h"

bool HighCardChecker::check(const Hand& hand) {
    std::cout << "Detected HIGH CARD\n";
    return true; // always true, last resort fallback
}