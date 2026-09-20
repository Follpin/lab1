#include "stack_analyzer.h"
#include "dealer.h"
#include <functional>
#include <numeric>
#include <stdexcept>

StackAnalyzer::StackAnalyzer(int cardsPerSuit, int totalCards)
    : cardsPerSuit(cardsPerSuit), totalCards(totalCards) {
    if (cardsPerSuit <= 0 || totalCards <= 0) {
        throw std::invalid_argument("Parameters must be positive integers.");
    }
}

double StackAnalyzer::calculateMedian(const std::vector<std::size_t>& lenCnt, std::size_t totalStackCnt) const {
    if (totalStackCnt == 0) {
        return 0.0;
    }

    std::size_t targetFirst = (totalStackCnt + 1) / 2;
    std::size_t targetSecond = (totalStackCnt % 2 == 0) ? (totalStackCnt / 2 + 1) : targetFirst;

    std::size_t cumulative = 0;
    double valFirst = 0.0;
    double valSecond = 0.0;
    bool foundFirst = false;
    bool foundSecond = false;

    for (std::size_t len = 1; len < lenCnt.size(); ++len) {
        cumulative += lenCnt[len];
        if (!foundFirst && cumulative >= targetFirst) {
            valFirst = static_cast<double>(len);
            foundFirst = true;
        }
        if (!foundSecond && cumulative >= targetSecond) {
            valSecond = static_cast<double>(len);
            foundSecond = true;
        }
        if (foundFirst && foundSecond) {
            break;
        }
    }

    return (valFirst + valSecond) / 2.0;
}

SimulationResult StackAnalyzer::analyze() const {
    Dealer dealer(cardsPerSuit);
    std::vector<std::size_t> lenCnt(static_cast<std::size_t>(cardsPerSuit + 1), 0);
    std::greater<Card> isStrictlyGreater;

    Card prevCard = dealer();
    std::size_t currLen = 1;

    for (int i = 1; i < totalCards; ++i) {
        Card nextCard = dealer();
        if (isStrictlyGreater(nextCard, prevCard)) {
            ++currLen;
        } else {
            ++lenCnt[currLen];
            currLen = 1;
        }
        prevCard = nextCard;
    }
    ++lenCnt[currLen];

    std::size_t totalStackCnt = std::accumulate(
        lenCnt.begin(),
        lenCnt.end(),
        static_cast<std::size_t>(0),
        std::plus<std::size_t>{}
    );

    auto calcPct = [totalStackCnt](std::size_t cnt) -> double {
        return (static_cast<double>(cnt) / static_cast<double>(totalStackCnt)) * 100.0;
    };

    std::map<std::size_t, double> lenPctMap;
    std::size_t maxCnt = 0;
    std::size_t mostFreqLen = 0;

    for (std::size_t len = 1; len <= static_cast<std::size_t>(cardsPerSuit); ++len) {
        if (lenCnt[len] > 0) {
            lenPctMap[len] = calcPct(lenCnt[len]);
            if (lenCnt[len] > maxCnt) {
                maxCnt = lenCnt[len];
                mostFreqLen = len;
            }
        }
    }

    double avgLen = static_cast<double>(totalCards) / static_cast<double>(totalStackCnt);
    double medLen = calculateMedian(lenCnt, totalStackCnt);

    return SimulationResult{
        totalStackCnt,
        lenPctMap,
        mostFreqLen,
        avgLen,
        medLen
    };
}