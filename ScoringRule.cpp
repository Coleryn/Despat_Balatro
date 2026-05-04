#include <iostream>
#include <string>
#include "ScoringRule.h"

std::string ScoringRule::handRankToString(HandRank rank) {
    switch(rank) {
        case HandRank::HIGH_CARD: return "High Card";
        case HandRank::PAIR: return "Pair";
        case HandRank::TWO_PAIR: return "Two Pair";
        case HandRank::THREE_OF_A_KIND: return "Three of a Kind";
        case HandRank::STRAIGHT: return "Straight";
        case HandRank::FLUSH: return "Flush";
        case HandRank::FULL_HOUSE: return "Full House";
        case HandRank::FOUR_OF_A_KIND: return "Four of a Kind";
        case HandRank::STRAIGHT_FLUSH: return "Straight Flush";
        case HandRank::ROYAL_FLUSH: return "Royal Flush";
        case HandRank::FIVE_OF_A_KIND: return "Five of a Kind";
        case HandRank::FLUSH_HOUSE: return "Flush House";
        case HandRank::FLUSH_FIVE: return "Flush Five";
        default: return "Unknown";
    }
}

int ScoringRule::getScoreFromRank(HandRank rank) {
    switch(rank) {
        case HandRank::HIGH_CARD: return 5;
        case HandRank::PAIR: return 10;
        case HandRank::TWO_PAIR: return 25;
        case HandRank::THREE_OF_A_KIND: return 50;
        case HandRank::STRAIGHT: return 100;
        case HandRank::FLUSH: return 150;
        case HandRank::FULL_HOUSE: return 250;
        case HandRank::FOUR_OF_A_KIND: return 500;
        case HandRank::STRAIGHT_FLUSH: return 1000;
        case HandRank::ROYAL_FLUSH: return 2500;
        case HandRank::FIVE_OF_A_KIND: return 5000;
        case HandRank::FLUSH_HOUSE: return 750;
        case HandRank::FLUSH_FIVE: return 300;
        default: return 0;
    }
}

int ScoringRule::scoreHand(const ChosenHand& ch) {
    // Build chain
    HighCardChecker* highCard = new HighCardChecker();
    PairChecker* pair = new PairChecker();
    TwoPairChecker* twoPair = new TwoPairChecker();
    FlushChecker* flush = new FlushChecker();
    StraightChecker* straight = new StraightChecker();
    ThreeOfAKindChecker* three = new ThreeOfAKindChecker();
    FlushFiveChecker* flushFive = new FlushFiveChecker();
    FullHouseChecker* fullHouse = new FullHouseChecker();
    FourOfAKindChecker* four = new FourOfAKindChecker();
    FlushHouseChecker* flushHouse = new FlushHouseChecker();
    StraightFlushChecker* straightFlush = new StraightFlushChecker();
    RoyalFlushChecker* royalFlush = new RoyalFlushChecker();
    FiveOfAKindChecker* fiveOfAKind = new FiveOfAKindChecker();


// Link chain (highest first: Royal Flush > Flush Five > Flush House > Five of a Kind > Straight Flush > Four of a Kind > Full House > Flush > Straight > Three of a Kind > Two Pair > Pair > High Card)
    royalFlush->setNext(flushFive);
    flushFive->setNext(flushHouse);
    flushHouse->setNext(fiveOfAKind);
    fiveOfAKind->setNext(straightFlush);
    straightFlush->setNext(four);
    four->setNext(fullHouse);
    fullHouse->setNext(flush);
    flush->setNext(straight);
    straight->setNext(three);
    three->setNext(twoPair);
    twoPair->setNext(pair);
    pair->setNext(highCard);


    HandRank rank = royalFlush->check(ch.getHand());
    std::cout << "Hand is " << handRankToString(rank) << "\n";
    int score = getScoreFromRank(rank);

    // Cleanup
    delete highCard;
    delete pair;
    delete twoPair;
    delete flush;
    delete straight;
    delete three;
    delete flushFive;
    delete fullHouse;
    delete four;
    delete flushHouse;
    delete straightFlush;
    delete royalFlush;
    delete fiveOfAKind;

    return score;
}

