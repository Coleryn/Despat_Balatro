#include <iostream>
#include <vector>
#include <set>
#include "HandGenerator.h"
#include "Hand.h"
#include "PokerHandChecker.h"

void printCard(const Card& c) {
    std::string rankStr;
    if      (c.rank == 11) rankStr = "J";
    else if (c.rank == 12) rankStr = "Q";
    else if (c.rank == 13) rankStr = "K";
    else if (c.rank == 14) rankStr = "A";
    else                   rankStr = std::to_string(c.rank);

    std::string suitStr;
    if      (c.suit == 'H') suitStr = "Hearts";
    else if (c.suit == 'D') suitStr = "Diamonds";
    else if (c.suit == 'C') suitStr = "Clubs";
    else                    suitStr = "Spades";

    std::cout << rankStr << " of " << suitStr;
}

int main() {
    HandGenerator gen;
    gen.buildDeck();
    gen.shuffleDeck();

    std::vector<Card> cards = gen.deal(8);

    std::cout << "=== DESPAT BALATRO ===\n\n";
    std::cout << "Kartu kamu (8 kartu):\n";
    for (int i = 0; i < (int)cards.size(); i++) {
        std::cout << "  " << (i + 1) << ". ";
        printCard(cards[i]);
        std::cout << "\n";
    }

    std::set<int> chosen;
    std::cout << "\nPilih 5 kartu (masukkan nomor 1-8, pisah spasi):\n> ";
    while ((int)chosen.size() < 5) {
        int idx;
        std::cin >> idx;
        if (idx < 1 || idx > 8) {
            std::cout << "Nomor tidak valid, masukkan 1-8\n> ";
            continue;
        }
        if (chosen.count(idx)) {
            std::cout << "Kartu " << idx << " sudah dipilih\n> ";
            continue;
        }
        chosen.insert(idx);
    }

    Hand selectedHand;
    std::cout << "\nKartu yang kamu pilih:\n";
    for (int idx : chosen) {
        std::cout << "  ";
        printCard(cards[idx - 1]);
        std::cout << "\n";
        selectedHand.addCard(cards[idx - 1]);
    }

    PokerHandChecker checker;
    std::string result = checker.check(selectedHand);
    std::cout << "\nHasil hand: " << result << "\n";

    return 0;
}