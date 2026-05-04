

#pragma once
#include "ChosenHand.h"
#include "PokerHandChecker.h"
#include "HandRank.h"
#include "FiveOfAKindChecker.h"
#include "RoyalFlushChecker.h"
#include "StraightFlushChecker.h"
#include "FlushHouseChecker.h"
#include "FourOfAKindChecker.h"
#include "FullHouseChecker.h"
#include "FlushFiveChecker.h"
#include "ThreeOfAKindChecker.h"
#include "StraightChecker.h"
#include "FlushChecker.h"
#include "TwoPairChecker.h"
#include "PairChecker.h"
#include "HighCardChecker.h"

class ScoringRule {
public:
  int scoreHand(const ChosenHand& ch);
private:
  std::string handRankToString(HandRank rank);
  int getScoreFromRank(HandRank rank);
};

