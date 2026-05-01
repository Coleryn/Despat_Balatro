#include <iostream>
#include <string>
#include "Hand.h"
#include "ChosenHand.h"
#include "HandGenerator.h"
#include "HandRank.h"
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
#include "HandPlayer.h"

std::string rankToStr(int r) {
    if (r == 11) return "J";
    if (r == 12) return "Q";
    if (r == 13) return "K";
    if (r == 14) return "A";
    return std::to_string(r);
}

int main() {
    // build chain
    FlushFiveChecker     flushFive;
    FlushHouseChecker    flushHouse;
    FiveOfAKindChecker   fiveOfAKind;
    RoyalFlushChecker    royalFlush;
    StraightFlushChecker straightFlush;
    FourOfAKindChecker   fourOfAKind;
    FullHouseChecker     fullHouse;
    FlushChecker         flush;
    StraightChecker      straight;
    ThreeOfAKindChecker  threeOfAKind;
    TwoPairChecker       twoPair;
    PairChecker          pair;
    HighCardChecker      highCard;

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

    // generate hand
    HandGenerator generator;
    Hand hand = generator.generateHand();
    HandPlayer handPlayer;
    ChosenHand chosenHand = handPlayer.playHand(hand);

    // print kartu
    std::cout << "Cards dealt: ";
    for (int i = 0; i < chosenHand.size(); i++) {
        Card c = chosenHand.getCard(i);
        std::cout << rankToStr(c.rank) << c.suit;
        if (i < chosenHand.size()-1) std::cout << " ";
    }
    std::cout << "\n";

    // jalankan chain
    flushFive.check(chosenHand.getHand());

    return 0;
}
