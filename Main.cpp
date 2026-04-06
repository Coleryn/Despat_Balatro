#include "GameManager.h"
#include "Hand.h"
#include "FlushFiveChecker.h"
#include "FlushHouseChecker.h"
#include "FiveOfAKindChecker.h"
#include "RoyalFlushChecker.h"
#include "StraightFlushChecker.h"
#include "FourOfAKindChecker.h"
#include "FullHouseChecker.h"
#include "FlushChecker.h"
#include "StraightChecker.h"
#include "ThreeOfAKindChecker.h"
#include "TwoPairChecker.h"
#include "PairChecker.h"
#include "HighCardChecker.h"

int main() {
    // Build the chain (highest priority first)
    FlushFiveChecker    flushFive;
    FlushHouseChecker   flushHouse;
    FiveOfAKindChecker  fiveOfAKind;
    RoyalFlushChecker   royalFlush;
    StraightFlushChecker straightFlush;
    FourOfAKindChecker  fourOfAKind;
    FullHouseChecker    fullHouse;
    FlushChecker        flush;
    StraightChecker     straight;
    ThreeOfAKindChecker threeOfAKind;
    TwoPairChecker      twoPair;
    PairChecker         pair;
    HighCardChecker     highCard;

    flushFive.setNext(&flushHouse);
    flushHouse.setNext(&fiveOfAKind);
    fiveOfAKind.setNext(&royalFlush);
    royalFlush.setNext(&straightFlush);
    straightFlush.setNext(&fourOfAKind);
    fourOfAKind.setNext(&fullHouse);
    fullHouse.setNext(&flush);
    flush.setNext(&straight);
    straight.setNext(&threeOfAKind);
    threeOfAKind.setNext(&twoPair);
    twoPair.setNext(&pair);
    pair.setNext(&highCard);

    // Start the chain with a dummy hand
    Hand hand;
    flushFive.check(hand);

    // Run the game
    GameManager gameManager;
    gameManager.runSession();

    return 0;
}